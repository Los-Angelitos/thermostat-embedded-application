#include "Thermostat.h"

#define ENDPOINT_POST_TEMPERATURE "http://host.wokwi.internal:3000/api/v1/monitoring/thermostats"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define DEVICE_ID "TH-01"
#define API_KEY "thermostat-key"

#define CONTENT_TYPE_HEADER "Content-Type"
#define APPLICATION_JSON "application/json"

#include <Arduino.h>

Thermostat::Thermostat(int switchPin, int potentiometerPin, int redPin, int bluePin, int sdaPin, int sclPin, bool initialLedState, bool change)
  : lcd(sdaPin, sclPin, this), potentiometer(potentiometerPin, this), 
    blueLed(bluePin, initialLedState, this), redLed(redPin, initialLedState, this),
    toggleSwitch(switchPin, this), initialLedState(initialLedState), change(change) {
} 


void Thermostat::on(Event event) {
}

void Thermostat::handle(Command command) {
}

void Thermostat::init() {
  lastTemperature = 0;
  lastTemperatureAuto = 0;

  Serial.println("Device initialized");
}

void Thermostat::controlLeds(float temperature) {
  // red led (heating) is on when temperature >= 32 C° and blue led (colding) when <= 27
  if(temperature >= 32) {
    redLed.setState(HIGH);
  }else {
    redLed.setState(LOW);
  }

  if(temperature <= 27) {
    blueLed.setState(HIGH);
  }else {
    blueLed.setState(LOW);
  }
}

void Thermostat::detectChange() {
  int state = toggleSwitch.getState();
  float currentTemperature = potentiometer.getCurrentTemperature();

  if(state != lastState) {
    change = !change;
    lastState = state;
  }

  if(change) {
    lcd.clear(); 
    lcd.setCursor(0, 0);
    if(state) {
      lcd.write("MODE: MANUAL");
    }else {
      lcd.write("MODE: AUTO");
    }

    lcd.setCursor(0, 1);
    lcd.write("Temp = ");
    lcd.writeFloat(currentTemperature);
    lcd.write("C");

    change = !change;
  }

  controlLeds(currentTemperature);

  if(state) controlInputManual();
}

void Thermostat::controlInputManual() {
  float currentTemperature = potentiometer.getCurrentTemperature();
  if(currentTemperature != lastTemperature) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("MODE: MANUAL");

    lcd.setCursor(0, 1);
    lcd.write("Temp = ");
    lcd.writeFloat(currentTemperature);
    lcd.write("C");
    lastTemperature = currentTemperature;
    delay(2000);
  }
}
