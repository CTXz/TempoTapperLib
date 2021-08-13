/*
 * Copyright (C) 2021  Patrick Pedersen

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */

/**
 * @file arduino_tt.cxx
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief An Arduino based tempo tapper that pulses a LED according to the tapped tempo
 * 
 * The following code showcases how an Arduino compatible device
 * can be used to pulse a LED according to a tapped in tempo.
 * This example can act as a base for amature audio-visual lighting.
 * 
 * Necessary hardware:
 *      - A Arduino compatible device
 *      - 2 buttons, one for tapping, one for resetting
 *      - A LED (If available, a built-in LED case be used too)
 * 
 * The pin configuartion can be altered in the define directives below.
 * 
 * This example could also be implemented more efficiently using hardware
 * interrupts, however, at the expense of making it less hardware cross-compatible.
 * 
 * To flash this example, simply import the Tempo Tapper library into your
 * prefered Arduino compatible IDE, compile this file and flash it onto
 * your Arduino compatible device. 
 * 
 */

#include <Arduino.h>
#include <tempo_tapper.h>

// Parameters (ADJUST THESE ACCORDING TO YOUR OWN SETUP)
#define LED 4                   ///< LED pin
#define TAP_BUTTON 5            ///< Tap button pin
#define RESET_BUTTON 6          ///< Reset button pin
#define LED_PULSE_LEN_MS 50     ///< LED pulse duration in ms
#define DEBOUNCE_TIME_MS 200    ///< Debounce time necessary for button

// Button states
#define PRESSED false           ///< Pull-Up, pressed button yields a low state
#define RELEASED !PRESSED

#define CHECK_BTN_PRESSED(prev, cur) (prev == RELEASED && cur == PRESSED) ///< Checks if button has been pressed
#define DEBOUNCE() delay(DEBOUNCE_TIME_MS)

/* 
 * The following code is responsible for asynchronously pulsing 
 * a LED. This is necessary, as synchronous pulsing could potentially 
 * block the device from reading button inputs.
 * */

enum sem
{
        idle,
        proc,
};

typedef struct async_pulse_led {
        uint8_t pin;
        sem led_sem;
        unsigned long pulse_len_ms;
        unsigned long start_time;
} async_pulse_led;

async_pulse_led * new_apl(uint8_t pin) {
        async_pulse_led *ret;
        ret = (async_pulse_led *) malloc(sizeof(async_pulse_led));
        ret->pin = pin;
        ret->led_sem = idle;
        return ret;
}

void start_led_pulse(async_pulse_led *led, unsigned long ms)
{
        led->led_sem = proc;
        led->pulse_len_ms = ms;
        led->start_time = millis();
        digitalWrite(led->pin, HIGH);
}

void cancel_led_pulse(async_pulse_led *led)
{
        digitalWrite(led->pin, LOW);
        led->led_sem = idle;
}

void handle_led(async_pulse_led *led) {
        if (millis() - led->start_time >= led->pulse_len_ms) {
                digitalWrite(led->pin, LOW);
                led->led_sem = idle;
        }
}

// Main

tempo_tapper *tt;
async_pulse_led *led;

bool tap_btn_prev, rst_btn_prev;
unsigned long tstamp;

void setup()
{
        pinMode(LED, OUTPUT);
        pinMode(TAP_BUTTON, INPUT_PULLUP);
        pinMode(RESET_BUTTON, INPUT_PULLUP);

        Serial.begin(9600);

        tt = tt_new();      // Initialize tempo tapper
        led = new_apl(LED); // Initialize struct to asynchronously control internal LED

        tap_btn_prev = digitalRead(TAP_BUTTON);
        rst_btn_prev = digitalRead(RESET_BUTTON);

        
}

void loop()
{
        bool tap_btn = digitalRead(TAP_BUTTON);
        bool rst_btn = digitalRead(RESET_BUTTON);

        // Check for tap
        bool pressed = CHECK_BTN_PRESSED(tap_btn_prev, tap_btn);
        if (pressed) {
                tt_tap(tt);                                 // Register tap
                tstamp = micros();                          // Tempo period starts here
                start_led_pulse(led, LED_PULSE_LEN_MS);     // Start LED pulse
                Serial.println("Tempo: " + String(tt_bpm(tt)) + " BPM");
                DEBOUNCE();                                 // Debounce the button
        }
        
        // Check for reset
        pressed = CHECK_BTN_PRESSED(rst_btn_prev, rst_btn);
        if (pressed) {
                tt_reset(tt);          // Reset tempo tapper
                cancel_led_pulse(led); // Abort any ongoing LED pulse
                Serial.println("Reset!");
                DEBOUNCE();            // Debounce the button
        }

        // Pulse LED at the current tempo
        unsigned long period = tt_period_us(tt);
        if (period > 0 && micros() - tstamp >= period) {
                tstamp = micros();
                start_led_pulse(led, LED_PULSE_LEN_MS); // Start LED pulse
        }

        handle_led(led); // Handle LED pulse
        tap_btn_prev = tap_btn;
        rst_btn_prev = rst_btn;
}