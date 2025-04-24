// Biblioteca: SevenSegmentILI9341
// Autor: Ismael Oliveira
// Descrição: Biblioteca para simular dígitos de display de sete segmentos em um display ILI9341

#ifndef SEVEN_SEGMENT_ILI9341_H
#define SEVEN_SEGMENT_ILI9341_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class SevenSegmentDisplay {
public:
    SevenSegmentDisplay(Adafruit_ILI9341* display)
        : tft(display) {}

    void drawDigit(int x, int y, uint8_t numero, uint16_t cor, uint16_t bg);
    void drawValue(float valor, int x, int y, const char* unidade, uint16_t cor);

private:
    Adafruit_ILI9341* tft;

    void drawHorizontalSegment(int x, int y, int largura, int espessura, uint16_t cor);
    void drawVerticalSegment(int x, int y, int espessura, int altura, uint16_t cor);
};

#endif // SEVEN_SEGMENT_ILI9341_H
