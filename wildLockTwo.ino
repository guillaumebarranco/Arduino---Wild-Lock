// IMPORTS ET CREATION DES VARIABLES GLOBALES
#include <Wire.h>
#include "rgb_lcd.h"
#include <Time.h>

rgb_lcd lcd;

#define ROTARY_ANGLE_SENSOR A0
#define LED 3//the Grove - LED is connected to D3 of Arduino
#define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
         //board switches to 3V3, the ADC_REF should be 3.3
#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

#define BUTTON 5

/*************************/
/******* VARIABLES *******/
/*************************/

int a;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

int first = rand_a_b(0,300);
int the_second = rand_a_b(0,300);
int third = rand_a_b(0,300);

int chapter = 1;
int current = first;

int time = 0;

int buttonState = 0;

/*************************/
/******* FONCTIONS *******/
/*************************/

// Fonction d'initialisation
void setup() {

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  pinMode(LED, OUTPUT);
}

// Fonction principale de boucle
void loop() {
  
  buttonState = digitalRead(BUTTON);

  if (buttonState == HIGH) {
    redoGame();
  }

  launchGame();
}

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

      if(chapter == 1) {
        //lcd.print("etape 1");
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

int rand_a_b(int a, int b){
  return rand()%(b-a) +a;
}

// Fonction pour afficher la fin
void setFinishedTime() {
  lcd.print("en ");
  lcd.print(time/2);
  lcd.print("s");
}

/*
* Fonctions pour faire briller les LED
*/

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

// Get the degrees number of the device
int getDegree() {

  int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
  float voltage;
  voltage = (float)sensor_value*ADC_REF/1023;
  float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;

  return degrees;
}




