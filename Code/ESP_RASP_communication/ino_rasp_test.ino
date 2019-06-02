void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13, OUTPUT);
Serial.println("Olar. Aqui eh o Arduino"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Olar. Aqui eh o Arduino");
  if(Serial. available());{
  flash(Serial.parseInt()); 
  Serial.flush(); //espera a transmissão serial de dados completar
  }
  delay(1000);
}

void flash(int n){
Serial.print("Numeros de flashes:");
Serial.println(n);
for (int i=0; i<n; i++){
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  Serial.println(i+1);
}
Serial.println("Flash completo");
}


