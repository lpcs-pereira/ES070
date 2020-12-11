#ifndef maquinaInput_h
#define maquinaInput_h

#include "TecladoInput.h"
#include "LCDInput.h"
#include "rfidInput.h"
#include "Rele.h"

class MaquinaEstados{
  private:
    char estado;
    char senhaAtual[4];
    Teclado  teclado;
    LCD lcd;
    RFID rfid;
    Rele rele;
    
  public:
    void init(){
      teclado.init();
      lcd.init();
      rfid.inicia();
      rele.inicia();
    };

    void maquina();
};

void MaquinaEstados::maquina()
{
  rele.abre();
}

#endif
