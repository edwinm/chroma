#include <Arduino.h>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>
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
  hexSprite.createSprite(TFT_WIDTH, 40);

  paletSprite.fillSprite(TFT_BLACK);
  paletSprite.fillRoundRect(20, 20, TFT_WIDTH - 40, TFT_HEIGHT / 2 - 40, 10, TFT_CYAN);
  paletSprite.pushSprite(0, 0);

  hexSprite.drawString("#CD08C0", 0, 0, 2);
  hexSprite.pushSprite(0, TFT_HEIGHT / 2);
}

void loop() {
  // You can update the screen here if needed
  delay(20);
}