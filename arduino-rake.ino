int PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
}

void loop() {
  digitalWrite(PIN, HIGH); 
  Serial.print("HIGH\n");
  delay(1000);
  digitalWrite(PIN, LOW);
  Serial.print("LOW\n");
  delay(1000);
}
