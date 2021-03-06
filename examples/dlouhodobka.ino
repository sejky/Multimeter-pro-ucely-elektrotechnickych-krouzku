/*
voltmetr funkcni- max 15V 

*/


#include "U8glib.h"
U8GLIB_SSD1306_128X64 OLED(U8G_I2C_OPT_NONE);

//Voltmetr
float vstupni_napeti0 = 0.0;
float r1=10000.0;    //r1 value
float r2=5100.0;      //r2 value
const int ap0 = A0;

//Ampermetr
const int ap1 = A1;
float proud0 = 0.0;
float rA = 10.0;

//Wattmetr
float vykon=0.0;
float vstupni_napeti1 = 0.0;

//Osciloskop
const int WIDTH=128;
const int HEIGHT=64;
const int LENGTH=WIDTH; 
int x;
int y[LENGTH];

//meřeni frekvence
const int pulsePin = 8; // Input signal connected to Pin 8 of Arduino
float frequency; // Calculated Frequency

//omhmetr
const int ap2 = A2;
const int ap3 = A3;
int Vin= 5;
float Vout= 0;

float Rx= 0;
float buffer= 0;

int R = 0;





bool kilo=false;
int frame = 0;


const unsigned char PROGMEM SPSE [] = 
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xC4, 0x31, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7E, 0x04, 0x30, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xF0, 0x04, 0x30, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xE0, 0x04, 0x30, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00,
0x00, 0x07, 0x80, 0x04, 0x30, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00,
0x00, 0x0F, 0x00, 0x04, 0x30, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1E, 0x00, 0x04, 0x30, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3C, 0x00, 0x04, 0x30, 0x00, 0x1E, 0x00, 0x00, 0xF8, 0x7E, 0x07, 0xE3, 0xF8, 0x00, 0x00,
0x00, 0x3F, 0xFF, 0xFC, 0x3F, 0xFF, 0xFE, 0x00, 0x01, 0x80, 0x63, 0x8E, 0x23, 0x00, 0x00, 0x00,
0x00, 0x77, 0xFF, 0xFC, 0x3F, 0xFF, 0xF7, 0x00, 0x01, 0x00, 0x61, 0x8C, 0x03, 0x00, 0x00, 0x00,
0x00, 0xE4, 0x00, 0x00, 0x00, 0x00, 0x13, 0x80, 0x03, 0x00, 0x61, 0x8C, 0x03, 0x00, 0x00, 0x00,
0x01, 0xC4, 0x00, 0x00, 0x00, 0x00, 0x11, 0xC0, 0x01, 0x80, 0x61, 0x8E, 0x03, 0x00, 0x00, 0x00,
0x01, 0xC4, 0x00, 0x00, 0x00, 0x00, 0x11, 0xC0, 0x01, 0xE0, 0x61, 0x87, 0x83, 0xF8, 0x00, 0x00,
0x03, 0x84, 0x00, 0x00, 0x00, 0x00, 0x10, 0xE0, 0x00, 0x78, 0x63, 0x03, 0xC3, 0xF8, 0x00, 0x00,
0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10, 0x60, 0x00, 0x1C, 0x7E, 0x00, 0xE3, 0x00, 0x00, 0x00,
0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x70, 0x00, 0x0C, 0x60, 0x00, 0x63, 0x00, 0x00, 0x00,
0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x0C, 0x60, 0x00, 0x23, 0x00, 0x00, 0x00,
0x06, 0x00, 0x03, 0xFC, 0x07, 0xC3, 0xFF, 0x30, 0x00, 0x0C, 0x60, 0x00, 0x63, 0x00, 0x00, 0x00,
0x0E, 0x1F, 0x87, 0xFF, 0x0F, 0x83, 0xFF, 0x38, 0x03, 0xF8, 0x60, 0x0F, 0xC3, 0xF8, 0x00, 0x00,
0x0E, 0x3F, 0xC3, 0xFF, 0x9F, 0xC7, 0xFF, 0x38, 0x00, 0xE0, 0x60, 0x07, 0x81, 0xF8, 0x00, 0x00,
0x0C, 0x7F, 0xF3, 0xFF, 0x9F, 0xE7, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0C, 0x7F, 0xE3, 0xC7, 0x9C, 0xC7, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0xF1, 0xE3, 0xC7, 0xDE, 0x07, 0x80, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0xF0, 0x43, 0xE7, 0x8E, 0x07, 0x80, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0xFC, 0x01, 0xFF, 0x8F, 0x07, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0x7E, 0x01, 0xFF, 0x07, 0x8F, 0xC0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x7F, 0x81, 0xFF, 0x07, 0x8F, 0xFE, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x3F, 0xE1, 0xFC, 0x03, 0xCF, 0xFC, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0x0F, 0xF0, 0xF0, 0x19, 0xCF, 0xFC, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0x03, 0xF8, 0xF0, 0x3D, 0xEF, 0x0C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0x00, 0xFC, 0xF0, 0x1F, 0xCF, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1C, 0x00, 0x7C, 0xF0, 0x0F, 0xDE, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0C, 0x0C, 0x3C, 0xF0, 0x07, 0x9E, 0x00, 0x18, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x40, 0x00,
0x0C, 0x1F, 0xFC, 0x1F, 0xFC, 0x1E, 0x00, 0x18, 0x00, 0xC0, 0x00, 0x18, 0x00, 0x00, 0xC0, 0x00,
0x0E, 0x1F, 0xF8, 0xE0, 0x03, 0x9F, 0x00, 0x38, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0E, 0x1F, 0xF3, 0x00, 0x80, 0x67, 0xC0, 0x38, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x06, 0x03, 0xCC, 0x20, 0x00, 0x1B, 0xE0, 0x30, 0x00, 0xC0, 0xE0, 0x1C, 0x23, 0x01, 0xC0, 0x00,
0x07, 0x00, 0x10, 0xA0, 0x80, 0x0D, 0xF0, 0x70, 0x00, 0xC1, 0x18, 0x7E, 0x2F, 0x87, 0xE0, 0x00,
0x07, 0x00, 0x22, 0x29, 0x80, 0x82, 0x70, 0x70, 0x00, 0xC2, 0x08, 0x40, 0x31, 0x80, 0x30, 0x00,
0x03, 0x00, 0x40, 0x60, 0x06, 0x45, 0x30, 0x60, 0x00, 0xC2, 0x08, 0xC0, 0x20, 0x80, 0x30, 0x00,
0x03, 0x80, 0x85, 0x07, 0xF0, 0x20, 0x80, 0xE0, 0x00, 0xC7, 0xF8, 0xC0, 0x20, 0x80, 0x70, 0x00,
0x01, 0xC1, 0x0C, 0x38, 0x0E, 0x00, 0x41, 0xC0, 0x00, 0xC6, 0x00, 0xC0, 0x20, 0x86, 0x30, 0x00,
0x01, 0xC2, 0x40, 0x60, 0x03, 0x24, 0x21, 0xC0, 0x00, 0xC2, 0x00, 0xC0, 0x20, 0x84, 0x30, 0x00,
0x00, 0xE2, 0x59, 0x80, 0x00, 0xC9, 0x23, 0x80, 0x00, 0xC2, 0x00, 0xC0, 0x20, 0x8C, 0x30, 0x00,
0x00, 0x74, 0x83, 0x00, 0x00, 0x66, 0x17, 0x00, 0x03, 0xC3, 0x88, 0x7E, 0x20, 0x87, 0xF0, 0x00,
0x00, 0x3C, 0x06, 0x00, 0x00, 0x20, 0x9E, 0x00, 0x03, 0x80, 0xF0, 0x1C, 0x60, 0x83, 0x10, 0x00,
0x00, 0x3D, 0x04, 0x00, 0x00, 0x10, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1E, 0x48, 0x00, 0x00, 0x09, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0F, 0x08, 0x00, 0x00, 0x08, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0x90, 0x00, 0x00, 0x04, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xF0, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xF0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7E, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xC0, 0x01, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM by_sejky [] = 
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x03, 0xFE, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x07, 0x02, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x80, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x77, 0xE0, 0xC0, 0x60, 0x07, 0x00, 0x07, 0xF0, 0x38, 0x30, 0x63, 0x80, 0xC0, 0x00,
0x00, 0x00, 0x7F, 0xF0, 0xE0, 0x60, 0x07, 0x80, 0x0E, 0x38, 0x38, 0x30, 0xE1, 0xC1, 0xC0, 0x00,
0x00, 0x00, 0x78, 0x78, 0xE0, 0xE0, 0x03, 0xE0, 0x1C, 0x1C, 0x38, 0x31, 0xC1, 0xC1, 0xC0, 0x00,
0x00, 0x00, 0x70, 0x38, 0x60, 0xC0, 0x01, 0xF8, 0x18, 0x1C, 0x38, 0x33, 0x81, 0xC1, 0x80, 0x00,
0x00, 0x00, 0x70, 0x38, 0x70, 0xC0, 0x00, 0x7E, 0x18, 0x1C, 0x38, 0x37, 0x00, 0xE3, 0x80, 0x00,
0x00, 0x00, 0x70, 0x38, 0x71, 0xC0, 0x00, 0x1E, 0x1F, 0xFC, 0x38, 0x3F, 0x00, 0xE3, 0x80, 0x00,
0x00, 0x00, 0x70, 0x38, 0x39, 0x80, 0x00, 0x0E, 0x1F, 0xFC, 0x38, 0x37, 0x80, 0x63, 0x00, 0x00,
0x00, 0x00, 0x70, 0x38, 0x39, 0x80, 0x00, 0x07, 0x18, 0x00, 0x38, 0x33, 0x80, 0x77, 0x00, 0x00,
0x00, 0x00, 0x70, 0x38, 0x1B, 0x80, 0x00, 0x06, 0x18, 0x00, 0x38, 0x31, 0xC0, 0x77, 0x00, 0x00,
0x00, 0x00, 0x78, 0x38, 0x1F, 0x00, 0x00, 0x0E, 0x1C, 0x00, 0x38, 0x31, 0xE0, 0x3E, 0x00, 0x00,
0x00, 0x00, 0x7E, 0xF0, 0x1F, 0x00, 0x06, 0x1E, 0x0E, 0x00, 0x38, 0x30, 0xE0, 0x3E, 0x00, 0x00,
0x00, 0x00, 0x77, 0xE0, 0x0F, 0x00, 0x07, 0xFC, 0x0F, 0xF8, 0x38, 0x30, 0x70, 0x3E, 0x00, 0x00,
0x00, 0x00, 0x23, 0xC0, 0x0E, 0x00, 0x01, 0xE0, 0x01, 0xF0, 0x38, 0x30, 0x30, 0x1C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x38, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x38, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void draw()//výpis na displey
{
 if(frame==0)
 OLED.drawBitmapP( 0, 0, 16, 64, by_sejky);
  
 if(frame==1)
 OLED.drawBitmapP( 0, 0, 16, 64, SPSE);
  
 if(frame==2)
 {
  OLED.setFont(u8g_font_unifont);
  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  OLED.setPrintPos(0, 10);
  // výpis textu na zadanou souřadnici
  OLED.print("Pavel Sykora");
  OLED.setPrintPos(0, 25);
  OLED.print("p.sykora102");
  OLED.setPrintPos(0, 40);
  OLED.print("@gmail.com");
  OLED.setPrintPos(0, 55);
  OLED.print("2018");
 }
 if(frame==3)//Voltmetr funguje
 {
    //OLED.setPrintPos(0, 25);
    //OLED.print("8.88");


    OLED.setFont(u8g_font_unifont);    
    OLED.setPrintPos(0, 10);
    OLED.print("Napeti:");
    OLED.setFont(u8g_font_fub25r);
    OLED.setPrintPos(0, 40);
    OLED.print(vstupni_napeti0);
    //OLED.setFont(u8g_font_unifont);
    OLED.setPrintPos(80, 40);
    OLED.print("V");
   
    //delay(100);
 }
 if(frame==4)// ampermetr
 {
    OLED.setFont(u8g_font_unifont);    
    OLED.setPrintPos(0, 10);
    OLED.print("Proud:");
    OLED.setFont(u8g_font_fub25r);
    OLED.setPrintPos(0, 40);
    OLED.print(proud0);
    OLED.setPrintPos(80, 40);
    OLED.print("A");
    OLED.setFont(u8g_font_unifont);
       
 }
 if(frame==5)//wattmetr
 {
    OLED.setFont(u8g_font_unifont);    
    OLED.setPrintPos(0, 10);
    OLED.print("Vykon:");
    OLED.setFont(u8g_font_fub25r);
    OLED.setPrintPos(0, 40);
    OLED.print(vykon);
    OLED.setPrintPos(80, 40);
    OLED.print("W");
    OLED.setFont(u8g_font_unifont);
    OLED.setPrintPos(0, 55);
    OLED.print("U=");
    OLED.setPrintPos(17, 55);
    OLED.print(vstupni_napeti1);
    OLED.setPrintPos(51, 55);
    OLED.print("V,I=");
    OLED.setPrintPos(84, 55);
    OLED.print(proud0);
    OLED.setPrintPos(120, 55);
    OLED.print("A");
       
 }
 if(frame==6)//Osciloskop funkcni
 {
  OLED.drawPixel(0, y[0]);
  for(int i=1; i<LENGTH; i++)
  {
    if(y[i]!=-1)
    {
      //u8g.drawPixel(i, y[i]);
      OLED.drawLine(i-1, y[i-1], i, y[i]);
    }
    else
    {
      break;
    }
  }
  
 }
  if(frame==7)//Měření frekvence
 {
    OLED.setFont(u8g_font_unifont);    
    OLED.setPrintPos(0, 10);
    OLED.print("Frekvence");
    OLED.setFont(u8g_font_fub25r);
    if(kilo==true)
    {
   
      OLED.setPrintPos(0, 40);
      OLED.print(frequency/1000);
      OLED.setFont(u8g_font_unifont);
      OLED.setPrintPos(0, 55);
      OLED.print("kHz");
    }
    else
    {
      OLED.setPrintPos(0, 40);
      OLED.print(frequency);
      OLED.setFont(u8g_font_unifont);
      OLED.setPrintPos(0, 55);
      OLED.print("Hz");
    }    
 }
  if(frame==8)//Ohmmetr
 {
    OLED.setFont(u8g_font_unifont);    
    OLED.setPrintPos(0, 10);
    OLED.print("Ohmmetr:");
    OLED.setFont(u8g_font_fub25r);
    OLED.setPrintPos(0, 40);
    
    if(kilo==true)
    {
      OLED.print(Rx/1000);
      //OLED.setPrintPos(80, 40);
      //OLED.print("");
      OLED.setFont(u8g_font_unifont);
      OLED.setPrintPos(0, 55);
      OLED.print("kOhm");
    }
    else
    {
      OLED.print(Rx);
      //OLED.setPrintPos(80, 40);
      //OLED.print("");
      OLED.setFont(u8g_font_unifont);
      OLED.setPrintPos(0, 55);
      OLED.print("Ohm"); 
    }
    OLED.setPrintPos(35, 55);
    OLED.print("Rosah");
    OLED.setPrintPos(85, 55);
    OLED.print(R);
//    OLED.setPrintPos(84, 55);
//    OLED.print(proud0);
    OLED.setPrintPos(120, 55);
    OLED.print("k");
       
 }
}

void setup(void) 
{
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), zmenafunkce, FALLING);//přepnutí modu funkce

  //Osciloskop
  x = 0;
  clearY();

  //měření frekvence
  pinMode(pulsePin,INPUT);

  //ohmmetr
  
}

void loop(void)
{
  kilo=false;
  
    if(frame==3)//Voltmetr
  {
    Serial.println("Voltmetr");  
    vstupni_napeti0=napeti(ap0); 
    Serial.println(vstupni_napeti0);  
  }
  
    if(frame==4)//Ampermetr
  {
    Serial.print("Ampermetr");
    proud();  
     
  }
  
   if(frame==5)//Wattmetr
  {
    Serial.print("Wattmetr");
    proud();  
    vstupni_napeti1=napeti(ap1);
    vykon=vstupni_napeti1*proud0;
     
  }
  
   if(frame==6)//Osciloskop
  {
    Serial.print("osciloskop");
    
    vstupni_napeti0=napeti(ap0);
    Serial.println(vstupni_napeti0);
    y[x] = map(vstupni_napeti0, 0, 15, HEIGHT-1, 0);
     
  }
  
  if(frame==7)//Měření frekvence
  {
    Serial.println("Měření frekvence");
    int pulseHigh; // Integer variable to capture High time of the incoming pulse
    int pulseLow; // Integer variable to capture Low time of the incoming pulse
    float pulseTotal; // Float variable to capture Total time of the incoming pulse
    pulseHigh = pulseIn(pulsePin,HIGH);
    pulseLow = pulseIn(pulsePin,LOW);
    pulseTotal = pulseHigh + pulseLow; // Time period of the pulse in microseconds frequency=1000000/pulseTotal; // Frequency in Hertz (Hz)
    frequency=1000000/pulseTotal; // Frequency in Hertz (Hz)     

    if (1000<frequency)
      kilo=true;
      
    if (1000==frequency)
      kilo=true;
  }
 
  if(frame==8)//Měření odporu
  {
    Serial.print("Měření odporu");
    int rosahA = analogRead(ap2);
    float rosahU = (rosahA * 5.0) / 1024.0;      
     
    //Serial.println(rosahU);  

    if (rosahU < 0.5) 
     {
         R=2;         
     }
     
    if (0.6 <rosahU) 
     {
        if(rosahU< 1.6)
           R=20;  
        if (2.7 <rosahU) 
          {
            if(rosahU < 3.7)
               R=200;  
            if (4.2 <rosahU ) 
             {              
                 R=1000;         
             }          
          }         
     }

    
    int rosahR = analogRead(ap3);
    //Serial.println(rosahR);
    float Ur = (rosahR * 5.0) / 1024.0;
    float pomoc = (Vin/Ur) -1;
    Rx=R* pomoc *1000;

    
    if (1000<Rx)
      kilo=true;
      
    if (1000==Rx)
      kilo=true;
  }


  OLED.firstPage();
  do{
      draw();
    } while(OLED.nextPage());
 
   
   
   if(frame<3)
  {
   delay(3000);
   frame ++;
  }
   
   if(frame>=3)
   delay(100);

    if(frame==6)
    {
        x++;
      if(x >= WIDTH)
      {
        x = 0;
        clearY(); 
      }
    }
  
   
   
  // if(frame>3)//odkomentovat
  // frame = -1;//nastaveni pro testovani
}
void zmenafunkce() //přepínaní tlacitkem na pinu 2
{

   static unsigned long last_interrupt_time = 0;
   unsigned long interrupt_time = millis();
   // If interrupts come faster than 200ms, assume it's a bounce and ignore
   if (interrupt_time - last_interrupt_time > 220) 
   {
     frame++;
    // tone(6,2250,50);
     if(frame>8)
     frame=3;
   }
   last_interrupt_time = interrupt_time;
}

float napeti(const int analogPin)
{  
    //Serial.println("Voltmetr");   
    int analogvalue = analogRead(analogPin);
    float temp = (analogvalue * 5.0) / 1024.0;       // FORMULA USED TO CONVERT THE VOLTAGE
    float input_volt = temp / (r2/(r1+r2));
    if (input_volt < 0.1) 
       {
         input_volt=0.0;
       } 
    //Serial.print("U = ");                 // prints the voltage value in the serial monitor
    //Serial.println(input_volt); 
    return input_volt;
}

void proud() //přepínaní tlacitkem na pinu 2
{
  float napeti0 =napeti(ap0);
  float napeti1 =napeti(ap1);
  float napetiRA = napeti0-napeti1;
  proud0= napetiRA/rA;
  
}

void clearY()//mazaní displeje
{
  for(int i=0; i<LENGTH; i++)
  {
    y[i] = -1;
  }
}
 
