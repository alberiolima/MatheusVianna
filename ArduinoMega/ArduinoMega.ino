#include <Servo.h>
/*---------------------------------------------ServoMotor-------------------------------------------------*/
Servo motorportao;

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

ambiente meusAmbientes[qAmbientes];


/*-----------------------------------------------SETUP----------------------------------------------------*/
void setup() {  
  
  Serial.begin(9600);  //Taxa de comunicaço em Bounds
  
  //Portas
  meusAmbientes[ambSala].porta = 45;
  meusAmbientes[ambCozinha].porta = 46;
  meusAmbientes[ambGaragem].porta = 6;
  meusAmbientes[ambQuarto].porta = 49;
  meusAmbientes[ambSuite].porta = 50;
  meusAmbientes[ambBanheiro].porta = 51;
  meusAmbientes[ambArea].porta = 52;
  meusAmbientes[ambCorredor].porta = 47;
  meusAmbientes[ambPortaob].porta = 28; //servo

  for ( byte j = 0; j < qAmbientes;j ++) {
    meusAmbientes[j].ligado = true;
    pinMode( meusAmbientes[j].porta, OUTPUT ); 
  }
  motorportao.attach(meusAmbientes[ambPortaob].porta);

  //Comandos do bluetooth
  meusAmbientes[ambSala].comando = 'S';
  meusAmbientes[ambCozinha].comando = 'c';
  meusAmbientes[ambGaragem].comando = 'g';
  meusAmbientes[ambQuarto].comando = '1';
  meusAmbientes[ambSuite].comando = '2';
  meusAmbientes[ambBanheiro].comando = 'B';
  meusAmbientes[ambArea].comando = 'A';
  meusAmbientes[ambCorredor].comando = 'C';
  meusAmbientes[ambPortaob].comando = 'Y';
}

/*---------------------------------------------LOOP-------------------------------------------------------*/
void loop(){
  if ( Serial.available() > 0 ) {
    byte bluetooth = Serial.read();  
    if ( bluetooth == '0' ) {
      for ( byte j = 1; j < qAmbientes;j ++) {
        meusAmbientes[j].ligado = false;
        digitalWrite( meusAmbientes[j].porta, HIGH );       
      }
    } else if ( bluetooth == 'F' ) {
      for ( byte j = 1; j < qAmbientes;j ++) {
        meusAmbientes[j].ligado = true;
        digitalWrite( meusAmbientes[j].porta, LOW );       
      }      
    } else if (bluetooth == meusAmbientes[ambPortaob].comando ) { //servo (portão)
      meusAmbientes[ambPortaob].ligado = !(meusAmbientes[ambPortaob].ligado);
      if ( meusAmbientes[ambPortaob].ligado ) {        
        for(byte i = 10; i <= 100; i++){
          motorportao.write(i);
          delay(50);
        }
      } else {
        for(byte i = 100; i >= 10; i--){
          motorportao.write(i);
          delay(50);
        }
      }      
    } else {
      for ( byte j = 1; j < qAmbientes;j ++) {
        if (bluetooth == meusAmbientes[j].comando ) { 
          if ( meusAmbientes[j].ligado ) {
            digitalWrite( meusAmbientes[j].porta, HIGH ); 
          } else {
            digitalWrite( meusAmbientes[j].porta, LOW ); 
          }
          meusAmbientes[j].ligado = !(meusAmbientes[j].ligado);          
        }
      } 
    }    
  }
}
