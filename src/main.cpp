#include <Arduino.h>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>
#include <SPIFFS.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <User_Setups/Setup47_ST7735.h>

// Define custom I2C pins for TCS34725
#define TCS_SDA_PIN 15 
#define TCS_SCL_PIN 13
#define TCS_INT_PIN 4

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite paletSprite = TFT_eSprite(&tft);
TFT_eSprite hexSprite = TFT_eSprite(&tft);

// Initialize TCS34725 color sensor with default integration time and gain
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  // Initialize custom I2C for TCS34725
  Wire.begin(TCS_SDA_PIN, TCS_SCL_PIN);

  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  paletSprite.createSprite(TFT_WIDTH, TFT_HEIGHT / 2);
  hexSprite.createSprite(TFT_WIDTH, 20);

  if (!SPIFFS.begin()) {
    Serial.println("Flash memory initialisation failed");
    while (1) yield();
  }

  if (!SPIFFS.exists("/Audiowide18.vlw")) {
    Serial.println("Font missing in flash memory");
    while (1) yield();
  }

  // Initialize the TCS34725 sensor
  if (tcs.begin()) {
    Serial.println("Found TCS34725 color sensor");
    tft.drawString("Color sensor found", 10, 30, 2);
  } else {
    Serial.println("No TCS34725 found... check connections");
    tft.drawString("Color sensor not found", 10, 30, 2);
    while (1) delay(100);
  }

  hexSprite.loadFont("Audiowide18");

  hexSprite.setTextColor(TFT_CYAN);
}

// Function to convert uint16_t value to two-digit hex string
String toHexString(uint16_t value) {
  String hexString = "";
  // Convert to 8-bit value for standard CSS hex format
  uint8_t byteVal = value > 255 ? 255 : (uint8_t)value;
  
  if (byteVal < 16) {
    hexString += "0";
  }

  hexString += String(byteVal, HEX);

  hexString.toUpperCase();
  
  return hexString;
}

void render() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Calculate color temperature and lux
  uint16_t colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  uint16_t lux = tcs.calculateLux(r, g, b);

  // Show color sample
  uint16_t rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);


  paletSprite.fillSprite(TFT_BLACK);
  paletSprite.fillRoundRect(10, 0, TFT_WIDTH - 20, TFT_HEIGHT / 2, 15, rgb565);
  paletSprite.pushSprite(0, 10);

    // Scale the values to 0-255 range for standard CSS hex formatting
  // The scaling might need adjustment based on your sensor readings
  const long rx = map(r, 0, 1024, 0, 255);  // Adjust max value based on your sensor's readings
  const long gx = map(g, 0, 1024, 0, 255);  // These max values are approximations
  const long bx = map(b, 0, 1024, 0, 255);  // You may need to calibrate them

  // Create CSS hex color string
  String hexColor = "#" + toHexString(r) + toHexString(g) + toHexString(b);

  hexSprite.fillSprite(TFT_BLACK);
  hexSprite.drawString(hexColor, 13, 0, 0);
  hexSprite.pushSprite(0, TFT_HEIGHT - 40);
}

void loop() {
  render();

  delay(200);
}