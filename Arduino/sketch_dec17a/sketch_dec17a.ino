#include "teclado.h"
#include "tranca.h" 
#include "lcd.h"

Tranca *tranca1;  //Cria ponteiro para a tranca
Teclado *teclado;  //Cria ponteiro para a tranca
Lcd *lcd;  //Cria ponteiro para a tranca

long comeco = 0;
long intervalo = 500;

//Definição de portas do siatema
int  portaTranca = A2; // tranca
byte portaLinhas[4] = {A3, 8, 7, 6}; // linha do teclado
byte portaColunas[4] = {5, 4, 3, 2}; // coluna do teclaso
byte portaLcd = 0x27; // porta do módulo i2c

void setup() {  
  tranca1 = new Tranca(portaTranca);                  //cria o objeto traca
  teclado = new Teclado(portaLinhas, portaColunas);   //cria o objeto teclado
  lcd = new Lcd(portaLcd);                            //cria o objeto lcd
  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();
  char letra = teclado->leTeclado();
  Serial.print(letra);
  lcd->escreveTela("texto", 0);
  if((agora - comeco) > intervalo) {
    comeco = agora;
    if(tranca1->Estado()) {
      tranca1->Fecha();
    } else {
      tranca1->Abre();
    }
  }
}
