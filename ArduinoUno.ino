/*ARDUINO UNO*/
#include <Servo.h>
#include <Ultrasonic.h>
/*--------------------------------DEFINIÇAO DE VARIAVEIS-----------------------------------------------*/
int portaLDR = A0;
int AA=0;
boolean sensor = 0;
//VAriaveis do Bluetooth
char bluetooth, valor;
//Variaveis do Servo Motor
Servo motorporta;
int i;
boolean porta = 1;
/*---------------------------------------------ULTRASSOM--------------------------------------------------*/
Ultrasonic ultrassom(2,3);//trig(2) e o echo(3)
long distancia;
int frequencia = 0;
const int tempo = 10;
int SOM1 = 12, fim=0;
//Variaveis do teclado matricial
int pinosLinhas = 10;
int pinosColunas[] = {9, 8, 7, 6};
char teclas[4] = {'1', '2', '3', '4'};
int a = 0, senhasim = 0, pass[4] = {51, 52, 50, 49};
int senha[4] = {0, 0, 0, 0};
/*--------------------------------INICIO DO SETUP-----------------------------------------------*/
void setup(){
  //Servo MOTOR
  Serial.begin(9600);
  
  motorporta.attach(13);
  pinMode(4, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  motorporta.write(100);
  //Teclado Matricial
  pinMode(pinosLinhas, OUTPUT);
  digitalWrite(pinosLinhas, HIGH);
  for (int nC = 0; nC <= 3; nC++)
    pinMode(pinosColunas[nC], INPUT_PULLUP);
}
/*---------------------------------INICIO DO LOOP----------------------------------------------*/
void loop(){
    sensor = digitalRead(11);
    Serial.println(sensor);
    ldr();
    if(sensor == 0)
    Teclado();
    if(sensor == 1)
    ultra();
}
/*----------------------------------------LDR---------------------------------------------------*/
void ldr(){
  int estado = analogRead(A0);  //Lê o valor fornecido pelo LDR   
  if (estado > 900){  
    digitalWrite(4, HIGH);  
  }else{  
    digitalWrite(4, LOW);  
  }   
}
/*-------------------------------------ULTRASSOM------------------------------------------------*/
void ultra(){
  distancia = ultrassom.Ranging(CM);
  //Serial.println(distancia);
  if(distancia > 2000 || distancia < 7){
    while(distancia >= 7 && distancia < 300){
      distancia = ultrassom.Ranging(CM);
      //Serial.print("DISTANCIAAAAAAAAA ");
      //Serial.println(distancia);
      if(distancia > 7 && distancia < 300)
        break;
      delay(1);
    }
  }
  if(distancia <= 32){
    for (frequencia = 150; frequencia < 1800; frequencia += 1){
      tone(SOM1, frequencia, tempo); 
      delay(1);
    }
    for (frequencia = 1800; frequencia > 150; frequencia -= 1){
      tone(SOM1, frequencia, tempo); 
      delay(1);
    }
  }
}
/*---------------------------------------TECLADO------------------------------------------------*/
void Teclado(){
  digitalWrite(pinosLinhas, LOW);
  //faz varredura em todas as colunas verificando se tem algum botao apertado
  while(AA < 4){
  
  for (int nC = 0; nC <= 3; nC++) {
    if (digitalRead(pinosColunas[nC]) == LOW) {
      a++;
      if (a == 1)
        senha[0] = teclas[nC];
      if (a == 2)
        senha[1] = teclas[nC];
      if (a == 3)
        senha[2] = teclas[nC];
      if (a == 4)
        senha[3] = teclas[nC];
      if (a == 4){
        AA = a;
        a = 0;
      }
      while (digitalRead(pinosColunas[nC]) == LOW) {
      }
    }
  }
  }
  AA = 0;
  //Verificando se cada digito da senha corresponde a senha legitima
  for (i = 0; i < 4; i++) {
    if (senha[i] == pass[i]) {
      senhasim++;
    }
    else { //Se a senha no for certa ento ele ira zerar a validade da senha
      senhasim = 0;
    }
  }
  if (senhasim == 4) { //Se a senha for certa entao ele ABRE A PORTA
    for(i = 100; i>=30; i--){
      motorporta.write(i);
      delay(100);
    }
    delay(5000);
    for(i = 30; i<=100; i++){
      motorporta.write(i);
      delay(100);     
    }
  }
  senhasim = 0; //Zera a senha pra renovar tudo
  for(i = 0; i <= 3; i++) //Zera todos os valores da senha
    senha[i] = 0; //Zerando os valores
  delay(10);
}
