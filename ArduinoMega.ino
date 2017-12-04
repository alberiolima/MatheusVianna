#include <Servo.h>
/*---------------------------------------------ServoMotor-------------------------------------------------*/
Servo motorportao;
int i;
/*---------------------------------------------bluetooth--------------------------------------------------*/
char bluetooth, valor;
boolean sala = 1, cozinha = 1, garagem = 1, quarto = 1, suite = 1, banheiro = 1, area = 1, corredor = 1, portaob = 1;
/*-----------------------------------------------SETUP----------------------------------------------------*/
void setup() {
  Serial.begin(9600);  //Taxa de comunicaço em Bounds
  motorportao.attach(28);
  pinMode(52, OUTPUT); //Led Area
  pinMode(51, OUTPUT); //Led Banheiro
  pinMode(50, OUTPUT); //Led Suite
  pinMode(49, OUTPUT); //Led Quarto
  pinMode(6, OUTPUT); //Led Garagem
  pinMode(47, OUTPUT); //Led Corredor
  pinMode(46, OUTPUT); //Led Cozinha
  pinMode(45, OUTPUT); //Led Sala
}
/*---------------------------------------------LOOP-------------------------------------------------------*/
void loop(){
  bluetooth = Serial.read();
  //Sala = S | Corredor = C | Cozinha = c | Suite = 1 | Quarto = 2 | Banheiro = B | Area = A | Garagemb = y |
  if(bluetooth == 'S' || bluetooth == 'C' || bluetooth == 'c' || bluetooth == '1' || bluetooth == '2' || bluetooth == 'B' || bluetooth == 'A' || bluetooth == 'g' || bluetooth == 'O' || bluetooth == 'F' || bluetooth == 'Y'){
    valor = bluetooth;
    if(valor == 'Y'){
      if(portaob == 1){
        for(i = 10; i <= 100; i++){
          motorportao.write(i);
          delay(50);
        }
        portaob = 0;
      }
      else{
        for(i = 100; i >= 10; i--){
          motorportao.write(i);
          delay(50);
        }
        portaob = 1;
      }
    }
      if(valor == 'S'){ //Sala
        if(sala == 1){
          sala = 0;
          digitalWrite(45, HIGH);
        }else{
          sala = 1;
          digitalWrite(45, LOW);
        }
    }
    if(valor == 'C'){ //Corredor
      if(cozinha == 1){
        cozinha = 0;
        digitalWrite(47, HIGH);
      }else{
        cozinha = 1;
        digitalWrite(47, LOW);
      }
    }
    if(valor == 'c'){ //Cozinha
      if(corredor == 1){
        corredor = 0;
        digitalWrite(46, HIGH);
      }else{
        corredor = 1;
        digitalWrite(46, LOW);
      }
    }
    if(valor == '1'){ //Quarto 1
      if(quarto == 1){
        quarto = 0;
        digitalWrite(49, HIGH);
      }else{
        quarto = 1;
        digitalWrite(49, LOW);
      }
    }
    if(valor == '2'){ //Suite
      if(suite == 1){
        suite = 0;
        digitalWrite(50, HIGH);
      }else{
        suite = 1;
        digitalWrite(50, LOW);
      }
    }
    if(valor == 'B'){ //Banheiro
      if(banheiro == 1){
        banheiro = 0;
        digitalWrite(51, HIGH);
      }else{
        banheiro = 1;
        digitalWrite(51, LOW);
      }
    }
    if(valor == 'A'){ //Area de Serviço
      if(area == 1){
        area = 0;
        digitalWrite(52, HIGH);
      }else{
        area = 1;
        digitalWrite(52, LOW);
      }
    }
    if(valor == 'g'){ //Garagem
      if(garagem == 1){
        garagem = 0;
        digitalWrite(6, HIGH);
      }else{
        garagem = 1;
        digitalWrite(6, LOW);
      }
    }
    if(valor == 'O'){
      digitalWrite(6, HIGH);
      digitalWrite(45, HIGH);
      digitalWrite(46, HIGH);
      digitalWrite(47, HIGH);
      digitalWrite(49, HIGH);
      digitalWrite(50, HIGH);
      digitalWrite(51, HIGH);
      digitalWrite(52, HIGH);
        sala = 0, cozinha = 0, garagem = 0, quarto = 0, suite = 0, banheiro = 0, area = 0, corredor = 0, portaob = 0;
  }
    if(valor == 'F'){
      digitalWrite(6, LOW);
      digitalWrite(45, LOW);
      digitalWrite(46, LOW);
      digitalWrite(47, LOW);
      digitalWrite(49, LOW);
      digitalWrite(50, LOW);
      digitalWrite(51, LOW);
      digitalWrite(52, LOW);
       sala = 1, cozinha = 1, garagem = 1, quarto = 1, suite = 1, banheiro = 1, area = 1, corredor = 1, portaob = 1;
    }
    valor = 'M';
  }  
delay(50);
}
