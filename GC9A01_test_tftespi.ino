#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "SerpentineBoldItalic.h"
#include "pin_config.h"
#include "OneButton.h"

//#include "CST816D.h"

//#define I2C_SDA 4
//#define I2C_SCL 5
//#define TP_INT 0
//#define TP_RST 1

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite testSprite = TFT_eSprite(&tft);

int value = 0;
bool incrementing = true;

void setup() {
  //tft.init();
  tft.begin();
  tft.setRotation(4);
  testSprite.setColorDepth(8);
  testSprite.createSprite(240, 240);

  ledcSetup(0, 2000, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 30);
}

int incrementDecrementValue() {
  if (incrementing) {
    value++;
    if (value >= 360) {
      incrementing = false;
    }
  } else {
    value--;
    if (value <= 0) {
      incrementing = true;
    }
  }
  return value;
}

void draw(int speed, uint32_t volt) {
  uint16_t fontColor;

  if (speed <= 60) {
    fontColor = TFT_GREEN;
  } else if (speed <= 120) {
    fontColor = TFT_YELLOW;
  } else {
    fontColor = TFT_RED;
  }

  testSprite.fillSprite(TFT_DARKGREY);
  testSprite.setTextColor(fontColor);
  testSprite.loadFont(SerpentineBoldItalic72pt);  // FONT
  testSprite.setCursor(50, 100);
  testSprite.printf("%02d", speed);

  testSprite.setTextColor(TFT_GOLD);
  testSprite.loadFont(SerpentineBoldItalic16pt);  // FONT
  testSprite.setCursor(80,200);
  testSprite.printf("%.2d mV", volt);

  testSprite.pushSprite(0, 0);
}

void loop() {
  // board battery voltage
  //uint32_t voltage = (analogRead(PIN_BAT_VOLT) * 2 * 3.3 * 1000) / 4096;
  int speed = incrementDecrementValue();
  draw(speed, 4);
  delay(50);
}
