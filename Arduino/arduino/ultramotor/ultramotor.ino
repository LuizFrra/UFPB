#include <Servo.h>
#include <Ultrasonic.h>
#define pin_echo 5
#define pin_trigger 4
#define pin_servo 8
Servo motor1;
Ultrasonic welle(pin_trigger,pin_echo);

int dist = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600) ;
  motor1.attach(pin_servo);
  motor1.write(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  dist = welle.Ranging(CM);
  if(dist > 0 && dist < 180){
    motor1.write(dist);
  }

}
