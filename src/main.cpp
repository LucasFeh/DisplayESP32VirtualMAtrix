
    #include <main.h>

   
    #define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP 
    BitToAscii asc;

    uint8_t value[80];
    char ascii;
    uint8_t bit;
    uint8_t pay;
    uint8_t count = 0;
    String tamanho = "";
    uint8_t y = 0;
    String text;
    String textN;
    bool firstRun = true;


void setup() {
  
  Serial.begin(115200);


  HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,   // module width
                PANEL_RES_Y,   // module height
                PANEL_CHAIN
                    // chain length
  );

  mxconfig.driver = HUB75_I2S_CFG::FM6124; 
  mxconfig.i2sspeed = mxconfig.HZ_10M;
  mxconfig.min_refresh_rate = 60;
  mxconfig.clkphase = false;  //  importante, caso não desative pode apresentar ghost 
  mxconfig.latch_blanking = 4; // importante, caso mude pode apresentar ghost n


  if (NUM_ROWS <= 1) {
    Serial.println(F("There is no reason to use the VirtualDisplay class for a single horizontal chain and row!"));
  }

  
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);

 
  dma_display->setBrightness8(128);    

 
  if( not dma_display->begin() )
      Serial.println("****** !KABOOM! I2S memory allocation failed ***********");


  virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, VIRTUAL_MATRIX_CHAIN_TYPE);

 
  virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));


   virtualDisp->setFont(&Font_64x192);
   virtualDisp->setTextColor(virtualDisp->color565( 255, 0, 0));

   virtualDisp->setTextSize(1); 
   virtualDisp->setCursor(1,  virtualDisp->height()- ((virtualDisp->height()-42)/2));    
   virtualDisp->print("888888-8888");
   


  // asc.readDsPin();
  
        pinMode(18, INPUT);
        pinMode(33, OUTPUT);
        pinMode(22, OUTPUT);
        pinMode(21, OUTPUT);
}

void loop() {

    digitalWrite(22, LOW); // CE HABILITADO

    digitalWrite(33, HIGH); // PL DESATIVADO
    delayMicroseconds(100);  // Breve espera 1 MICROSEGUNDOS 
    digitalWrite(33, LOW); // PL HABILITADO
    delayMicroseconds(100);  // Breve espera 1 MICROSEGUNDOS 
    digitalWrite(33, HIGH); // PL DESATIVADO

        Serial.println("iniciou");

    for(uint8_t i = 0; i < 10*8; i++){
        value[i] = digitalRead(18); // lê o bit do Q7 e armazena no vetor value[i]
        digitalWrite(21, HIGH); // PULSO CLK PARA LER OS DADOS
        delay(10);
        digitalWrite(21, LOW);// pulso de CLK PARA LOW
        Serial.print(value[i]);
        delay(10);

    }
        Serial.println(" ");
        Serial.println("Acabou");

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
        if(textN != text){
           AscII(text);
        }
        count = 0;
        textN= text;
        text.clear();
        delay(5000);
}