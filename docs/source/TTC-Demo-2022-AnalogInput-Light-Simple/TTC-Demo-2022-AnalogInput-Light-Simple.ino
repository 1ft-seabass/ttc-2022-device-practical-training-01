int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Analog Read");
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("light = ");
  Serial.println(sensorValue);
  delay(1000);
}
