int x = 1010;
int y = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  y = map(x, 0, 1023, 0, 100);// função map (valor ligo, valor minimo, valor maximo, valor minimo que eu quero, valor em porcentagem do valor maximo que eu quero trabalhar)
  Serial.print(y);
  delay(10000);
}
