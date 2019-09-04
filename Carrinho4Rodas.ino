#include <Ultrasonic.h>
#include <AFMotor.h>
#include "Servo.h"

Servo servo1;

Ultrasonic ultrasonic(A1, A0); // T / E

AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4);

void frente(){
  motor1.setSpeed(255); 
  motor1.run(FORWARD);
  
  motor2.setSpeed(255); 
  motor2.run(FORWARD);
  
  motor3.setSpeed(255); 
  motor3.run(FORWARD);
  
  motor4.setSpeed(255); 
  motor4.run(FORWARD);
}

void tras(){
  motor1.setSpeed(255); 
  motor1.run(BACKWARD);
  
  motor2.setSpeed(255); 
  motor2.run(BACKWARD);
  
  motor3.setSpeed(255); 
  motor3.run(BACKWARD);
  
  motor4.setSpeed(255); 
  motor4.run(BACKWARD);

  delay(2000);

  vira360();
}

void esquerda(){
  motor1.setSpeed(255); 
  motor1.run(FORWARD);
  
  motor2.setSpeed(255); 
  motor2.run(FORWARD);
  
  motor3.setSpeed(255); 
  motor3.run(BACKWARD);
  
  motor4.setSpeed(255); 
  motor4.run(BACKWARD);

  delay(2000);
}

void direita(){
  motor1.setSpeed(255); 
  motor1.run(BACKWARD);
  
  motor2.setSpeed(255); 
  motor2.run(BACKWARD);
  
  motor3.setSpeed(255); 
  motor3.run(FORWARD);
  
  motor4.setSpeed(255); 
  motor4.run(FORWARD);

  delay(2000);
}

void para(){ 
  motor1.run(RELEASE);
  
  motor2.run(RELEASE);
   
  motor3.run(RELEASE);
   
  motor4.run(RELEASE);
}

void meio(){
  servo1.write(100);
  delay(500);
}

float disFrente(){
  float dis = 0;
  long microsec;
  microsec = ultrasonic.timing();
  dis = ultrasonic.convert(microsec, Ultrasonic::CM);
  return dis;  
}

int distanciaLados(){
  para();
  meio();
  float disDir = 0, disEsq = 0;
  long microsec;
  
  servo1.write(0); // Direita
  delay(1000);
  microsec = ultrasonic.timing();
  disDir = ultrasonic.convert(microsec, Ultrasonic::CM);


  delay(3000);
  
  servo1.write(180); // Esquerda
  delay(1000);
  microsec = ultrasonic.timing();
  disEsq = ultrasonic.convert(microsec, Ultrasonic::CM);


  delay(3000);
  meio();

  if(disDir < 30 && disEsq < 30){
    tras();
  } else if(disDir < disEsq){
    esquerda(); // Esquerda livre
  }else if(disDir > disEsq){
    direita(); // Direita livre
  }
  
}

void vira360(){
  motor1.setSpeed(255); 
  motor1.run(FORWARD);
  
  motor2.setSpeed(255); 
  motor2.run(FORWARD);
  
  motor3.setSpeed(255); 
  motor3.run(BACKWARD);
  
  motor4.setSpeed(255); 
  motor4.run(BACKWARD);

  delay(4000);
}

//========================================================================// 

void setup(){
  
  servo1.attach(9);
  meio();
  
}

//========================================================================// 

void loop(){
 
  if(disFrente() < 30){
    distanciaLados();
  }else{
    frente();
  }

}
