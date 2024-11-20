#ifndef BIT_TO_ASCII_H
#define BIT_TO_ASCII_H

#include <Arduino.h>

#define DS 18 //35
#define PL 33 // 1
#define CE 22 // rx0
#define CLK 21
#define NUM_CHIPS 10


// Caso os bits cheguem todos de uma vez, é necessario estabelecer 8 pinos de leitura pra cada bit
// Porém se os bits vierem um a um, é necessario apenas 1 pino de leitura para fazer a cosntrução do caracter ASCII

class BitToAscii {
  public:
    // Construtor que recebe o array de pinos GPIO e o número de pinos (bits)
     BitToAscii(uint8_t DSIN = DS, uint8_t PLOUT = PL, uint8_t CEOUT = CE, uint8_t CLKOUT = CLK, uint8_t NUM_CHIPS_ = NUM_CHIPS){

        _dsin = DSIN;
        _plin = PLOUT;
        _cein = CEOUT;
        _clkin = CLKOUT;
        _num_chips = NUM_CHIPS_;
        
            pinMode(_dsin, INPUT);
            pinMode(_plin, OUTPUT);
            pinMode(_cein, OUTPUT);
            pinMode(_clkin, OUTPUT);

    };

    // Função para ler os bits e printar
    String readBits(uint8_t* value);
    void buildDelay();
    String readDsPin();
    
  private:
     uint8_t _dsin;
     uint8_t _plin;
     uint8_t _cein;
     uint8_t _clkin;
     uint8_t _num_chips;
    
};

#endif