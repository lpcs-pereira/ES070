/* ***************************************************** */
/* File name:          sketch_dec17a               
/* File description:   Main do projeto                        
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:      24Apr2020                         
/* Revision date:      24Apr2020                         
/* ***************************************************** */

#include "maquina.h"
#include <avr/sleep.h>

Maquina *maq;
Tranca *tranca1;    //Cria ponteiro para a tranca
Teclado *teclado;   //Cria ponteiro para a tranca
Lcd *lcd;           //Cria ponteiro para a tranca
RFID *rfid;         //Cria ponteiro para a tranca
SensorPIR *sensorpir;

/* ************************************************ */
/* Method name:        setup                     
/* Method description: Inicialização de todos os hardware 
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************ */
void setup() {
  Serial.begin(9600);
  // declaracao de variaveis
  int  portaTranca = A2; // pino ligado ao relé que libera a tranca, A2 = pino 16
  byte portaLinhas[4] = {A3, 8, 7, 6}; // linha do teclado
  byte portaColunas[4] = {5, 4, 3, A1}; // coluna do teclaso
  byte portaLcd = 0x27; // endereço do módulo i2c
  int portaSensorPIR = 2; // pino em que quando o sensor de presença detecta alguém envia sinal HIGH
  int tx = 0;
  int rx = 1;

  tranca1 = new Tranca(portaTranca);                  //cria o objeto traca
  teclado = new Teclado(portaLinhas, portaColunas, tx, rx);   //cria o objeto teclado
  lcd = new Lcd(portaLcd);                            //cria o objeto lcd
  rfid = new RFID();                                  //cria o objeto rfid
  sensorpir = new SensorPIR(portaSensorPIR);          //cria o objeto do sensor de presenca
  maq = new Maquina(tranca1, teclado, lcd, rfid, sensorpir);     //cria o objeto maquina de estados

}

/* ************************************************ */
/* Method name:        loop                     
/* Method description: Função de loop que chama as funções de acordo com estado 
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************ */
void loop() {
  int sensorPIRteste;
  sensorPIRteste = sensorpir->leSensorPIR();
  if(sensorPIRteste == HIGH){
    modoOcioso();
  }
  int est = maq->getEstado();
  switch (est) {
    case ESPERA:
      maq->Espera();
      break;
    case ESCOLHER:
      maq->Escolher();
      break;
    case LECARTAO:
      maq->LeCartao();
      break;
    case ABRESENHA:
      maq->AbreSenha();
      break;
    case NOVASENHA:
      maq->NovaSenha();
      break;
    case TROCASENHA:
      maq->TrocaSenha();
      break;
    case MENUMESTRE:
      maq->MenuMestre();
      break;
    case EDITASENHA:
      maq->EditaSenha();
      break;
    case REMOVER:
      maq->Remove();
      break;
    default:
      break;
  }
}

void modoOcioso(){
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    int interrupcao = sensorpir->returnPorta();
    attachInterrupt(digitalPinToInterrupt(interrupcao), acordar, CHANGE);
    sleep_cpu();
}

void acordar(){
    sleep_disable();   // Desabilita o sleep
    detachInterrupt(0);// Desabilita a interrupção
}
