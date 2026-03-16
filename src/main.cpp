#include "LGFX_JD9165.hpp"
#include <Arduino.h>
#include <TouchLib.h>
#include <Wire.h>

#define LCD_BL 23
#define LCD_RST 27
#define TOUCH_SDA 7
#define TOUCH_SCL 8
#define TOUCH_ADDR 0x5D

LGFX_JD9165 lcd;
TouchLib touch(Wire, TOUCH_SDA, TOUCH_SCL, TOUCH_ADDR);

void setup(void) {
    Serial.begin(115200);
    delay(1000);

    Serial.println("=== JC1060P470 Touch Draw Test Start ===");

    if(!lcd.begin(LCD_RST)) {
        Serial.println("LCD init failed!");
        while(1)
            delay(1000);
    }
    lcd.setSwapBytes(true);

    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);

    touch.init();
    Wire.setClock(400000);

    lcd.fillScreen(TFT_WHITE);

    Serial.printf("LCD initialized: %dx%d\n", lcd.width(), lcd.height());
}

void loop(void) {
    if(touch.read()) {
        TP_Point t = touch.getPoint(0);
        // Touch resolution is 800x480. Mapping to LCD (1024x600).
        int x = map(t.x, 0, 800, 0, lcd.width() - 1);
        int y = map(t.y, 0, 480, 0, lcd.height() - 1);
        lcd.fillCircle(x, y, 4, TFT_BLUE);
    }
}
