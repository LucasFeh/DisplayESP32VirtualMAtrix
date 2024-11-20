#include "BitToAscII.h"

#define DELAY 100
// uint8_t value;

void BitToAscii::buildDelay(){
    uint8_t delayTime = micros();
    while ((micros() - delayTime) < DELAY)
    {
    }

}

String BitToAscii::readDsPin() { // essa função vai receber o valor de DS, de acordo com o datasheet do mux e passar para a função que varre os bits e retorna o valor em ASCII

//     digitalWrite(_plin, HIGH); // PL DESATIVADO
//     digitalWrite(_cein, HIGH); // CE DESATIVADO

    
//     digitalWrite(_cein, LOW); // CE HABILITADO
    
//     // Carregar dados
//     digitalWrite(_plin, LOW); // PL HABILITADO
//     delayMicroseconds(1);  // Breve espera 1 MICROSEGUNDOS 
//     digitalWrite(_plin, HIGH); // PL DESATIVADO



// for(uint8_t i = 0; i < _num_chips*8; i++){

//      digitalWrite(_clkin, HIGH); // PULSO CLK PARA LER OS DADOS
//      value = digitalRead(_dsin); // lê o bit do Q7 e armazena no vetor value[i]
//      delay(10);
//      digitalWrite(_clkin, LOW);// pulso de CLK PARA LOW
//      Serial.println(value);
//      delay(500);

// }

//  digitalWrite(_cein, HIGH); // Desativar CE

// futuramente derá uma codição para ser feita a proxima leitura, por enquanto só vamos esperar 10 segundos antés de realizar outra.
// return readBits(value);

}

// Função para ler o valor dos bits dos pinos e formar o valor ASCII, depois concatenar tudo e formar o texto em string para printar no display
String BitToAscii::readBits(uint8_t* value) {
    
char ascii;
uint8_t bit;
uint8_t pay;
uint8_t count = 0;
String tamanho = "";
uint8_t y = 0;
String text;
text.clear();

    digitalWrite(22, LOW); // CE HABILITADO

    digitalWrite(33, HIGH); // PL DESATIVADO
    delayMicroseconds(100);  // Breve espera 1 MICROSEGUNDOS 
    digitalWrite(33, LOW); // PL HABILITADO
    delayMicroseconds(100);  // Breve espera 1 MICROSEGUNDOS 
    digitalWrite(33, HIGH); // PL DESATIVADO

    for(uint8_t i = 0; i < 10*8; i++){
        value[i] = digitalRead(18); // lê o bit do Q7 e armazena no vetor value[i]
        digitalWrite(21, HIGH); // PULSO CLK PARA LER OS DADOS
        delay(1);
        digitalWrite(21, LOW);// pulso de CLK PARA LOW
        // Serial.print(value[i]);
        delay(1);

    }

              for ( u_int8_t i = 0; i < 80; i++) {

                  bit = value[i];             
                    ascii += (bit << 7-y);  

                    y++;
                  if(y == 8){
                       count++;
                        if(count == 7){ // logica para aplicação do "-"
                          text += "-";
                          count = 0;
                        }
                        if(ascii < 0x21 || ascii > 0x7d){
                          text += " ";
                        }else{
                          text += ascii;
                        }
                          ascii = 0;
                          y = 0;
                  }
           }
     
        // Serial.println(text);
        count = 0;
        delay(100);

    return text;  // Retorna a string construída. 
}
