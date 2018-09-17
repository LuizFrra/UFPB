int button = 4;
int led = 8;
int x = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode (button, INPUT );
  pinMode (led, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(button) == LOW){
    //Serial.print("1");
    x++;
    while(digitalRead(button) == LOW ){
      Serial.print(x);
    }
  }
  else{
    //Serial.print("0");
  }
  if(x%2 == 0){
    digitalWrite(led,HIGH);
     }
  else{
    digitalWrite(led,LOW);
    }
}
