#include <Arduino.h>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>
#include <SPIFFS.h>
#include <User_Setups/Setup47_ST7735.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite paletSprite = TFT_eSprite(&tft);
TFT_eSprite hexSprite = TFT_eSprite(&tft);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  paletSprite.createSprite(TFT_WIDTH, TFT_HEIGHT / 2);
  hexSprite.createSprite(TFT_WIDTH, 20);

  paletSprite.fillSprite(TFT_BLACK);
  paletSprite.fillRoundRect(10, 0, TFT_WIDTH - 20, TFT_HEIGHT / 2, 15, TFT_CYAN);
  paletSprite.pushSprite(0, 10);

  if (!SPIFFS.begin()) {
    Serial.println("Flash memory initialisation failed");
    while (1) yield();
  }

  if (!SPIFFS.exists("/Audiowide20.vlw")) {
    Serial.println("Font missing in flash memory");
    while (1) yield();
  }

  hexSprite.loadFont("Audiowide20");

  hexSprite.drawString("#CD08C0", 5, 0, 0);
  hexSprite.pushSprite(0, TFT_HEIGHT - 40);
}

void loop() {
  // You can update the screen here if needed
  delay(20);
}