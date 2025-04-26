#include <Arduino.h>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  tft.init();
  tft.fillScreen(TFT_BLUE);

}

void loop() {
  // You can update the screen here if needed
}