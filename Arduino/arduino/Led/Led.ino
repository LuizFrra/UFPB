int led = 8;
int button = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode ( led,OUTPUT );
  pinMode (button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
  */
  if(digitalRead(button) == HIGH ){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
   
}
