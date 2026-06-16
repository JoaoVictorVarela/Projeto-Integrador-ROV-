#include <Servo.h>
#include "AFMotor.h"// biblioteca do controlador do motor de propulsão

AF_DCMotor motor1(1); // associa o motor de propulsão ao pino 1
AF_DCMotor motor2(2); // associa o motor de propulsão ao pino 2
Servo servo1;
Servo servo2;

int xVal, yVal,button0Val, button1Val;  // Valores do joystick e botão
int angle1, angle2, angle3;         // Ângulos para os servos

void setup() {
  Serial.begin(9600);       // Inicia a comunicação serial
  servo1.attach(9);         // Servo 1 no pino 9
  servo2.attach(10);        // Servo 2 no pino 10
  motor1.setSpeed(50);// seta a velocidade do motor de propulsão1
  motor1.run(RELEASE);
  motor2.setSpeed(50);// seta a velocidade do motor de propulsão2
  motor2.run(RELEASE);
  
}

void loop() {
  if (Serial.available() > 0) {
    xVal = Serial.parseInt();      // Valor do eixo X
    yVal = Serial.parseInt();      // Valor do eixo Y
    button0Val = Serial.parseInt();  // Estado do botão 0
    button1Val = Serial.parseInt(); // Estado do botão 1
    
    
    // Limpa o buffer até o fim da linha
    if (Serial.read() == '\n') {

      // Mapeia os valores para ângulos dos servos (Joystick maior)
      angle1 = map(yVal, 0, 255, 0, 180); // Frente e trás
      angle2 = map(xVal, 0, 255, 0, 180); // Esquerda e direita     
     
      // Inverte um dos ângulos, se necessário
      angle3 = 180 - angle1;

      // Move os servos
      servo1.write(angle1);
      servo2.write(angle3);

       // Joystick movido para a esquerda
if (angle2 < 60) {
  servo1.write(0);     // Frente
  servo2.write(0);   // Trás

// Joystick movido para a direita
} else if (angle2 > 120) {
  servo1.write(180);   // Trás
  servo2.write(180);     // Frente

// Joystick na posição central
} else {
  servo1.write(angle1);  // Segue o eixo Y (frente/trás)
  servo2.write(angle3);
}
// Se botão estiver pressionado motor gira Forward
  if (button0Val == 1) {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
      } else if (button1Val == 1) {
        motor1.run(BACKWARD);
        motor2.run(FORWARD);
        } else{
          motor1.run(RELEASE);
          motor2.run(RELEASE);
        }
  
      } else{
        motor1.run(RELEASE);
        motor2.run(RELEASE);
      }

      delay(60);
    }


      delay(60);
    }        
    
  
