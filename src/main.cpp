
    #include <main.h>


   
    #define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP 

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
    tamanho += (char)payload[i];
  }
  Serial.println();



    if ( char(payload[0]) == '5') {
        Letras();
  }

  if (strncmp((char*)topic, "key2", length) == 0) {
              
              virtualDisp->clearScreen();
                for ( u_int8_t i = 0; i < 80; i++) {

                  bit = (payload[i] == '1') ? 1 : 0; 
                      ascii += (bit << 7-y);  

                    y++;
                  if(y == 8){
                       count++;
                      if(count == 7){
                        text += "-";
                        count = 0;
                      }
                      text += ascii;
                      Serial.println(ascii);
                      ascii = 0;
                      y = 0;
                      }
                  }
                  Serial.println(text);
                  AscII(text);
                  text.clear();
                  ascii = 0;
                  count = 0;


      }

}

void setup() {

  delay(2000);
  Serial.begin(115200);

  wifi.connect();
  mqtt.connect(TOPIC_1, TOPIC_2, TOPIC_3);

  delay(5000);

  mqtt.publishMessage("Mensagens", "mqtt Iniciou");
  
  mqtt.setCallback(callback);

  HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,   // module width
                PANEL_RES_Y,   // module height
                PANEL_CHAIN
                    // chain length
  );

  mxconfig.driver = HUB75_I2S_CFG::FM6124; 
  mxconfig.i2sspeed = mxconfig.HZ_20M;
  mxconfig.min_refresh_rate = 50;


 
  if (NUM_ROWS <= 1) {
    Serial.println(F("There is no reason to use the VirtualDisplay class for a single horizontal chain and row!"));
  }

  
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);

 
  dma_display->setBrightness8(60);    

 
  if( not dma_display->begin() )
      Serial.println("****** !KABOOM! I2S memory allocation failed ***********");


  virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, VIRTUAL_MATRIX_CHAIN_TYPE);

 
  virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));


   virtualDisp->setFont(&TESTE);
   virtualDisp->setTextColor(virtualDisp->color565(189, 35, 219));

   virtualDisp->setTextSize(1); 
   virtualDisp->setCursor(1,  virtualDisp->height()- ((virtualDisp->height()-45)/2));    
   virtualDisp->print("");


   
}

void loop() {
  mqtt.connect(TOPIC_1, TOPIC_2, TOPIC_3);
  mqtt.loop();
  

}