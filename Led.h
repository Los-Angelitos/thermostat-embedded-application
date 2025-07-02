#ifndef LED_H
#define LED_H
#include "Actuator.h"

class Led : public Actuator {
private:
    bool state; ///< Current state of the LED (true = ON, false = OFF).

public:
    static const int TOGGLE_LED_COMMAND_ID = 0; ///< Unique ID for toggle command.
    static const int TURN_ON_COMMAND_ID = 1; ///< Unique ID for turn-on command.
    static const int TURN_OFF_COMMAND_ID = 2; ///< Unique ID for turn-off command.
    static const Command TOGGLE_LED_COMMAND; ///< Predefined command to toggle the LED.
    static const Command TURN_ON_COMMAND; ///< Predefined command to turn the LED ON.
    static const Command TURN_OFF_COMMAND; ///< Predefined command to turn the LED OFF.
    Led(int pin, bool initialState = false, CommandHandler* commandHandler = nullptr);

    void handle(Command command) override;
    bool getState() const;
    void setState(bool newState);
};

#endif // LED_H