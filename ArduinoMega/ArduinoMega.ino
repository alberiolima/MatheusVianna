#include "cabec.h"
#include <Servo.h>

Servo motorportao;
ambiente meusAmbientes[qAmbientes];

unsigned long tempoLDR = 0;
unsigned long tempoPIR = 0;
unsigned long tempoLASER = 0;
boolean alternarBuzzer = true;
boolean alarmLASER = false;
int valorLASER_OLD = 1023;

void setup() {  
  
  Serial.begin(9600);  //Taxa de comunicaço em Bounds
  
  //Portas
  meusAmbientes[ambGaragem].porta  = 6;
  meusAmbientes[ambPortaob].porta  = 28; //servo
  meusAmbientes[ambSala].porta     = 45;
  meusAmbientes[ambCozinha].porta  = 46;
  meusAmbientes[ambCorredor].porta = 47;
  meusAmbientes[ambQuarto].porta   = 49;
  meusAmbientes[ambSuite].porta    = 50;
  meusAmbientes[ambBanheiro].porta = 51;
  meusAmbientes[ambArea].porta     = 52;

  //Definir portas como saida
  pinMode( pinSensorPIR, INPUT );
  pinMode( portaLDR, INPUT );
  pinMode( pinLDR_LASER, INPUT );
  pinMode( pinLASER, OUTPUT);
  for ( byte j = 0; j < qAmbientes;j ++) {
    meusAmbientes[j].ligado = true;
    pinMode( meusAmbientes[j].porta, OUTPUT ); 
  }

  //ligar servo
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

void loop(){

  //Leitura do LDR
  if ( millis() > tempoLDR ) {
    tempoLDR = millis() + tempoLeituraLDR;
    digitalWrite( portaSaidaLDR, analogRead(portaLDR) > 900?HIGH:LOW );  
  } 

  //Leitura do PIR
  if ( millis() > tempoPIR ) {
    tempoPIR = millis() + tempoLeituraPIR;
    
    if ((digitalRead( pinSensorPIR ) == HIGH )||(alarmLASER)) { //LASER usa o mesmo alarme do PIR, pelo tempo do bip de tempoLeituraPIR
      tone( pinBuzzer, alternarBuzzer?1440:1880, tempoLeituraPIR );
      alternarBuzzer = !(alternarBuzzer);
    }
    
  }

  //LASER
  if ( millis() > tempoLASER ) {
    tempoLASER = millis() + tempoLeituraLASER;
    digitalWrite( pinLASER, HIGH );
    int valorLASER = analogRead( pinLDR_LASER );    
    digitalWrite(pinLASER, LOW );

    alarmLASER = ( valorLASER - 100 > valorLASER_OLD || valorLASER_OLD + 100 < valorLASER || valorLASER_OLD > 200 || valorLASER > 200 );
    valorLASER_OLD = valorLASER;
  }
  
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
    } else if ( bluetooth == meusAmbientes[ambPortaob].comando ) { //servo (portão)
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
        if ( bluetooth == meusAmbientes[j].comando ) { 
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
