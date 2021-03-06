/* ************************************************************************************************ */
/* File name:          sensor_pir.h               
/* File description:   Arquivo com as funções do sensor de presença                  
/* com senhas salvas
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                               
/* ************************************************************************************************ */
class SensorPIR
{
    // variaveis
  private:
    int _iPorta;
	  int _iDetectaPresenca;
    // metodos
  public:
    SensorPIR(int iPorta);
    int leSensorPIR();
    int returnPorta();
};

/* ************************************************************************************************ */
/* Method name:        SensorPIR                     
/* Method description: Função para inicializar o sensor
/* Input params:       int Porta: recebe pino onde esta ligado o sensor                      
/* Output params:      n/a                         
/* ************************************************************************************************ */
SensorPIR::SensorPIR(int iPorta)
{
  _iPorta = iPorta;
  _iDetectaPresenca = 0;
  pinMode(iPorta, INPUT_PULLUP);
  //pinMode(_iPorta, INPUT);   //Define a porta como saída
  Serial.print("O sensor de presença foi inicializado na porta: ");
  Serial.println(_iPorta);
}

int SensorPIR::returnPorta()
{
  return _iPorta;
}

/* ************************************************************************************************ */
/* Method name:        Abre                     
/* Method description: Função para abrir a tranca
/* Input params:       n/a                    
/* Output params:      n/a                         
/* ************************************************************************************************ */
int SensorPIR::leSensorPIR()
{
  _iDetectaPresenca = digitalRead(_iPorta); // Lê o estado do sensor de presença em que 1 = sensor ativado
  return _iDetectaPresenca;
}
