#define pinLDR A0
#define pinLASER 7
#define SOM1 3
#define pinSensorPIR 8

int valor1 = 1024;
int valor2;
int p = 3;
int valorSensorPIR = 0;


void setup(){
  pinMode(pinLDR, INPUT);
  Serial.begin(9600);
  pinMode(pinLASER, OUTPUT);
}
void loop(){
  
  valorSensorPIR = digitalRead(pinSensorPIR);
  if(valorSensorPIR == 1){
    tone(SOM1, 1440);
    delay(200);
    tone(SOM1, 1880);
    delay(200);
  }
  
  digitalWrite(pinLASER, HIGH);
  valor2 = analogRead(pinLDR);

  Serial.println(valor1);
  digitalWrite(pinLASER, HIGH);

  if(valor2-100 > valor1 || valor1+100 < valor2 || valor1 > 200 || valor2 > 200){
    tone(SOM1, 1440);
    delay(200);
    tone(SOM1, 1880);
    delay(200);
  }
  else{
    noTone(SOM1);
  }
  valor1 = valor2;
  delay(50);
}
