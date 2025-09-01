#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 6
#define DATA_PIN 12
#define CLK_PIN 10
#define CS_PIN 11

MD_Parola parola = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  parola.begin();
  parola.setSpeed(100); // Increase for slower scroll
  parola.setPause(0);
  parola.displayClear();
  parola.displayText("Aadeesh Jain is Ironman", PA_LEFT, parola.getSpeed(), parola.getPause(), PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  if (parola.displayAnimate()) {
    parola.displayReset();
  }
} 
