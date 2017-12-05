enum {
  ambPortaob, 
  ambSala,
  ambCozinha, 
  ambGaragem,  
  ambQuarto,   
  ambSuite,
  ambBanheiro,
  ambArea,
  ambCorredor,
  qAmbientes
};

struct ambiente  {
  boolean ligado = true;
  byte porta = 0;
  byte comando = 0;
};

#define tempoLeituraLDR 333
#define portaLDR      A0
#define portaSaidaLDR  4

#define pinSensorPIR   8
#define tempoLeituraPIR 200

#define pinBuzzer 3
