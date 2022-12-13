#include <Servo.h>

Servo sB;  //Servo Base
Servo sD;  //Servo Direito
Servo sE;  //Servo Esquerdo
Servo sG;  //Servo Garra

static const int servoBPin = 27;  //Servo Base
static const int servoDPin = 14;  //Servo Direito
static const int servoEPin = 12;  //Servo Esquerdo
static const int servoGPin = 13;  //Servo Garra

static const int ledPin = 33;

void setup() {
  Serial.begin(115200);
  
  sB.attach(servoBPin);
  sD.attach(servoDPin);
  sE.attach(servoEPin);
  sG.attach(servoGPin);

  pinMode(ledPin, OUTPUT);

}

void loop() {

  // PEGAR
  //Servo Base
  for(int i=90; i >= 20; i -= 10){
    sB.write(i);
    delay(200);
  }
  //Servo Direito
  for(int i=30; i <= 80; i += 10){
    sD.write(i);
    delay(200);
  }
  //Servo Esquerdo
  for(int i=120; i >= 70; i -= 10){
    sE.write(i);
    delay(200);
  }
  //Servo Direito
  for(int i=80; i <= 120; i += 10){
    sD.write(i);
    delay(200);
  }
  //Servo Garra
  for(int i=50; i <= 150; i += 10){
    sG.write(i);
    delay(200);
  }

  //CENTRO
  //Servo Direito
  for(int i=120; i >= 80; i -= 10){
    sD.write(i);
    delay(200);
  }
  //Servo Esquerdo
  for(int i=70; i <= 120; i += 10){
    sE.write(i);
    delay(200);
  }
  //Servo Direito
  for(int i=80; i >= 30; i -= 10){
    sD.write(i);
    delay(200);
  }
  //Servo Base
  for(int i=20; i <= 90; i += 10){
    sB.write(i);
    delay(200);
  }

  //SOLTAR
  //Servo Esquerdo
  for(int i=120; i <= 140; i += 10){
    sE.write(i);
    delay(200);
  }
  //Servo Base
  for(int i=90; i <= 160; i += 10){
    sB.write(i);
    delay(200);
  }
  //Servo Direito
  for(int i=30; i <= 90; i += 10){
    sD.write(i);
    delay(200);
  }
  //Servo Garra
  for(int i=150; i >= 50; i -= 10){
    sG.write(i);
    delay(200);
  }
  //Servo Direito
  for(int i=90; i >= 30; i -= 10){
    sD.write(i);
    delay(200);
  }

  //CENTRO
  //Servo Base
  for(int i=160; i >= 90; i -= 10){
    sB.write(i);
    delay(200);
  }
  //Servo Esquerdo
  for(int i=140; i >= 120; i -= 10){
    sE.write(i);
    delay(200);
  }

}
