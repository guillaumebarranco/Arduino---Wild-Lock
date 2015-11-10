/*************************/
/******** IMPORTS ********/
/*************************/
#include <Wire.h>
#include "rgb_lcd.h"
#include <Time.h>

/*************************/
/******* CONSTANTS *******/
/*************************/

rgb_lcd lcd; // lcd is screen displaying variable

#define ROTARY_ANGLE_SENSOR A0 // Rotative button is pin A0
#define LED 3 // Led is pin 3
#define BUTTON 5 // Button is pin 5

#define FULL_ANGLE 300 //full value of the rotary angle is 300 degrees
#define ADC_REF 5
#define GROVE_VCC 5

/*************************/
/******* VARIABLES *******/
/*************************/

// For the screen display
int a;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// The numbers to find are random
int first = rand_a_b(0,300);
int the_second = rand_a_b(0,300);
int third = rand_a_b(0,300);

int chapter = 1;
int current = first;

int time = 0;

int buttonState = 0;

/*************************/
/******* FUNCTIONS *******/
/*************************/

// Initialisation function for the LED and the Screen
void setup() {
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    pinMode(LED, OUTPUT);
}

// Batch function that will call the main function continouisly
void loop() {

    buttonState = digitalRead(BUTTON);

    if (buttonState == HIGH) {
        redoGame();
    }

    launchGame();
}

// Restart game function
void redoGame() {
    a=analogRead(0);
    lcd.setCursor(0, 1);
    lcd.print("begin   ");
    chapter = 1;

    first = rand_a_b(0,300);
    the_second = rand_a_b(0,300);
    third = rand_a_b(0,300);

    time = 0;
    current = first;

    delay(2000);
}

void launchGame() {

    if(chapter < 4) {

        int degrees;
        degrees = getDegree();

        a=analogRead(0);
        lcd.setCursor(0, 1);

        if(degrees == current) {

            // STEPS
            if(chapter == 1) {
                brightRedLed();
                current = the_second;

            } else if(chapter == 2) {
                brightBlueLed();
                current = third;

            } else if(chapter == 3) {
                brightGreenLed();
                setFinishedTime();
            }

            if(chapter < 4) {
                chapter = chapter + 1;
            }

        } else {
            getCurrent(degrees);
        }

        lcd.setCursor(0, 1);
        delay(500);
    }
}

// Random function to generate number between min and max
int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

// Ending function to display the final time required to finish the game
void setFinishedTime() {
    lcd.print("en ");
    lcd.print(time/2);
    lcd.print("s");
}

// Function making the LED shining
void brightLed() {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(500);
}

void brightRedLed() {
    brightLed();
}
void brightBlueLed() {
    brightLed();
    brightLed();
}
void brightGreenLed() {
    brightLed();
    brightLed();
    brightLed();
}

// Check if user is near the number to find or not
void getCurrent(int val) {

    if(val > current) {

        if(val - current < 20) {
            lcd.print("chaud   ");
        } else {
            lcd.print("froid   ");
        }

    } else {

        if(current - val < 20) {
            lcd.print("chaud   ");
        } else {
            lcd.print("froid   ");
        }
    }

    time = time + 1;
}

// Get the degrees number of the rotative button
int getDegree() {

    int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
    float voltage;
    voltage = (float)sensor_value*ADC_REF/1023;
    float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;

    return degrees;
}
