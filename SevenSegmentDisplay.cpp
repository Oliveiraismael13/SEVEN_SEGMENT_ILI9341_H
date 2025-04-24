// SevenSegmentDisplay.h
#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class SevenSegmentDisplay {
public:
    SevenSegmentDisplay(Adafruit_ILI9341* display);
    void drawDigit(int x, int y, uint8_t number, uint16_t color, uint16_t bg);
    void drawValue(float value, int x, int y, const char* unit, uint16_t color);

private:
    Adafruit_ILI9341* tft;
    void drawSegmentHorizontal(int x, int y, int width, int thickness, uint16_t color);
    void drawSegmentVertical(int x, int y, int thickness, int height, uint16_t color);
};

#endif // SEVENSEGMENTDISPLAY_H


// SevenSegmentDisplay.cpp
#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(Adafruit_ILI9341* display) : tft(display) {}

void SevenSegmentDisplay::drawSegmentHorizontal(int x, int y, int width, int thickness, uint16_t color) {
    int slope = thickness / 2;
    tft->fillRect(x + slope, y, width - 2 * slope, thickness, color);
    tft->fillTriangle(x, y + slope, x + slope, y, x + slope, y + thickness - 1, color);
    tft->fillTriangle(x + width - 1, y + slope, x + width - slope - 1, y, x + width - slope - 1, y + thickness - 1, color);
}

void SevenSegmentDisplay::drawSegmentVertical(int x, int y, int thickness, int height, uint16_t color) {
    int slope = thickness / 2;
    tft->fillRect(x, y + slope, thickness, height - 2 * slope, color);
    tft->fillTriangle(x, y + slope, x + (thickness / 2), y, x + thickness - 1, y + slope, color);
    tft->fillTriangle(x + 1, y + height - slope - 1, x + (thickness / 2), y + height - 1, x + thickness - 1, y + height - slope - 1, color);
}

void SevenSegmentDisplay::drawDigit(int x, int y, uint8_t number, uint16_t color, uint16_t bg) {
    const uint8_t digits[10] = {
        0b00111111, 0b00000110, 0b01011011, 0b01001111,
        0b01100110, 0b01101101, 0b01111101, 0b00000111,
        0b01111111, 0b01101111
    };

    uint8_t segs = digits[number];

    const int width = 38, height = 39, thickness = 11;

    drawSegmentHorizontal(x + thickness, y + 5, width, thickness, (segs & 0b00000001) ? color : bg);
    drawSegmentVertical(x + width + thickness - 4, y + thickness, thickness, height + 2, (segs & 0b00000010) ? color : bg);
    drawSegmentVertical(x + width + thickness - 4, y + height + 3 + thickness, thickness, height, (segs & 0b00000100) ? color : bg);
    drawSegmentHorizontal(x + thickness, y + 2 * height - 2 + thickness, width, thickness, (segs & 0b00001000) ? color : bg);
    drawSegmentVertical(x + 4, y + height + 3 + thickness, thickness, height, (segs & 0b00010000) ? color : bg);
    drawSegmentVertical(x + 4, y + thickness, thickness, height + 2, (segs & 0b00100000) ? color : bg);
    drawSegmentHorizontal(x + thickness, y + height + 8, width, thickness, (segs & 0b01000000) ? color : bg);
}

void SevenSegmentDisplay::drawValue(float value, int x, int y, const char* unit, uint16_t color) {
    static int lastValue = -1;
    int intValue = static_cast<int>(value);

    if (intValue != lastValue) {
        int u1 = intValue % 10;
        int u2 = (intValue / 10) % 10;
        int u3 = (intValue / 100) % 10;
        int u4 = (intValue / 1000) % 10;

        drawDigit(x, y, u4, color, ILI9341_BLACK);
        drawDigit(x + 72, y, u3, color, ILI9341_BLACK);
        drawDigit(x + 144, y, u2, color, ILI9341_BLACK);
        drawDigit(x + 216, y, u1, color, ILI9341_BLACK);

        tft->setTextSize(2);
        tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
        tft->setCursor(x + 283, y + 85);
        tft->print(unit);

        lastValue = intValue;
    }
}
