
// #include <FastLED.h>
#include <Arduino.h>
#include "BitToAscii.h"
#include <SPIFFS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include "AllFonts.h"
#include <Font_64x192.H>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>



#define PANEL_RES_X 64 
#define PANEL_RES_Y 32 
#define NUM_ROWS 2 
#define NUM_COLS 3 
#define PANEL_CHAIN NUM_ROWS*NUM_COLS
#define PIN_E 32


#define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP 


MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel  *virtualDisp = nullptr;

// char ascii;
// uint8_t bit;
// uint8_t pay;
// uint8_t count = 0;
// String tamanho = "";
// uint8_t y = 0;
// String text;

char alphanumeric[67]; // 26 letras + 10 dígitos = 36 caracteres
int* x = 0;

int num_fonts = sizeof(fonts) / sizeof(fonts[0]);



extern void AscII(String ascii){

  dma_display->clearScreen();


  virtualDisp->setFont(&Font_64x192);
  virtualDisp->setTextColor(virtualDisp->color565(33, 235, 43));

  virtualDisp->setTextSize(1); 
  virtualDisp->setCursor(1,  virtualDisp->height()- ((virtualDisp->height()-45)/2));    
//   virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
  virtualDisp->print(ascii);

  
  virtualDisp->setFont(NULL);

}



extern void Letras(){


    // Adicionando letras de A a Z
    for (int index = 0; index < 57; ++index) {
        alphanumeric[index] = '!' + index;
    }

    // Adicionando dígitos de 0 a 9
    for (int index = 57; index < 67; ++index) {
        alphanumeric[index] = '0' + (index - 26);
    }

    // Exibindo o vetor
    for (int i = 0; i < 67; i++) {
        Serial.print(alphanumeric[i]);
        Serial.print(' ');
        AscII((String)alphanumeric[i]);
        delay(500);
    }
}


