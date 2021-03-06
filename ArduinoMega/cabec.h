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

#define pinLASER  7
#define tempoLeituraLASER 50
#define pinLDR_LASER A1

#define tempoLeituraUS 30
#define pinUS_ECHO   3
#define pinUS_TRIG   2
