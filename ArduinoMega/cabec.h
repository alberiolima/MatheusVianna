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
