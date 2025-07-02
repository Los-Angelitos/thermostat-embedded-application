#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SWITCH_GPIO 34
#define POTENTIOMETER_PIN 35
#define RED_LED 14
#define BLUE_LED 12

#define ENDPOINT_POST_TEMPERATURE "http://host.wokwi.internal:3000/api/v1/monitoring/thermostats"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define DEVICE_ID "TH-01"
#define API_KEY "thermostat-key"

#define CONTENT_TYPE_HEADER "Content-Type"
#define APPLICATION_JSON "application/json"

HTTPClient httpClient;
JsonDocument dataRecord;

int state, lastState;
bool change = false;
float temperature = 0, lastTemperature = 0, lastTemperatureAuto = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);

std::pair<bool, int> handleReadyEvent();

void setup() {
  Serial.begin(115200);
  Serial.println("Starting thermostat...");
  // initializing wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // setting body json for POST
  dataRecord["device_id"] = DEVICE_ID;
  dataRecord["api_key"] = API_KEY;

  // pines I2C personalizados
  Wire.begin(25, 26); // SDA = GPIO25, SCL = GPIO26

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print("Connected!");

  // switch
  pinMode(SWITCH_GPIO, INPUT);
  state = digitalRead(SWITCH_GPIO);
  lastState = state;


  // leds
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // backend
  //lastTemperatureAuto = getTemperatureFromBackend();

  Serial.println("Device initialized");
}

void loop() {
  state = digitalRead(SWITCH_GPIO);
  if(state != lastState) {
    change = !change;
    lastState = state;
  }


  if(change) {
    lcd.clear(); 
    lcd.setCursor(0, 0);
    if(state) {
      lcd.print("MODE: MANUAL");
    }else {
      lcd.print("MODE: AUTO");
    }

    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.print(temperature, 1);
    lcd.print("C");

    change = !change;
  }

  // potentiometer
  int potValue = analogRead(POTENTIOMETER_PIN);
  temperature = map(potValue, 0, 4095, 20, 40); // 20°C a 40°C

  controlLeds();
  if(state) controlInputManual();
  else controlInputAuto();
  delay(2000);
}

void controlLeds() {
  // red led (heating) is on when temperature >= 32 C° and blue led (colding) when <= 27
  digitalWrite(RED_LED, temperature >= 32 ? HIGH : LOW);
  digitalWrite(BLUE_LED, temperature <= 27 ? HIGH : LOW);
}

void controlInputManual() {
  if(temperature != lastTemperature) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MODE: MANUAL");

    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.print(temperature);
    lcd.print("C");
    lastTemperature = temperature;
    delay(2000);
  }
}

void controlInputAuto() {
  delay(3000);
  if(WiFi.status() == WL_CONNECTED) {
    std::pair<bool, int> response = handleReadyEvent();
    if(!response.first) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Device off");
      return;
    }

    lastTemperatureAuto = response.second;
  }

  if(temperature != lastTemperatureAuto) {
    temperature = lastTemperatureAuto;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MODE: AUTO");

    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.print(temperature);
    lcd.print("C");
    delay(2000);
  }
}

float getTemperatureFromBackend() {
  return random(250, 400) / 10.0;
}

// function to know if the device is ready
std::pair<bool, int> handleReadyEvent() {
  Serial.println("Getting if the device is ready...");
  httpClient.begin(ENDPOINT_POST_TEMPERATURE);
  dataRecord["current_temperature"] = temperature;

  String dataRecordResource;
  serializeJson(dataRecord, dataRecordResource);
  Serial.print("Sending JSON: ");
  Serial.println(dataRecordResource);

  httpClient.addHeader(CONTENT_TYPE_HEADER, APPLICATION_JSON);
  int httpCode = httpClient.POST(dataRecordResource);
  Serial.print("HTTP Response Code: ");
  Serial.println(httpCode);

  JsonDocument response;
  String responseResource;
  responseResource = httpClient.getString();
  Serial.print("Raw response: ");
  Serial.println(responseResource);
  deserializeJson(response, responseResource);
  serializeJsonPretty(response, Serial);
  Serial.println();

  std::pair<bool, int> varResponse;
  varResponse.first = response["state"].as<bool>();
  varResponse.second = response["current_temperature"].as<int>();

  httpClient.end();

  return varResponse;
}