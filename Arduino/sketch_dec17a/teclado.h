#include <Keypad.h>

byte nlinha = 4; // n de linhas
byte ncolunas = 4; //n de colunas
char dicionarioTeclado[4][4] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte linhas[] = {9, 8, 7, 6};
byte colunas[] = {5, 4, 3, 2};

class Teclado{
  private:
    Keypad *teclado_personalizado;
  public:
    Teclado();
    char leTeclado();
};

Teclado::Teclado()
{
  teclado_personalizado = new Keypad(makeKeymap(dicionarioTeclado), linhas, colunas, nlinha, ncolunas);
};

char Teclado::leTeclado()
{
  char leitura_teclas = teclado_personalizado->getKey(); // Atribui a variavel a leitura do teclado
  if (leitura_teclas) {                                 // Se alguma tecla foi pressionada
    return leitura_teclas;
    Serial.print(leitura_teclas);
  }
  else {
    return ' ';
  }
};