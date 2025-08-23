const int trigPin = 9;
const int echoPin = 10;
const int numReadings = 10; // Número de leituras para tirar a média

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long totalDistance = 0;
  
  // Faz várias leituras para tirar a média
  for (int i = 0; i < numReadings; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.0344 / 2;
    
    totalDistance += distance;
    delay(50); // Pequeno atraso entre as leituras
  }

  // Calcula a média das leituras
  float averageDistance = totalDistance / numReadings;
  
  Serial.print("Distância média: ");
  Serial.print(averageDistance);
  Serial.println(" cm");
  
  delay(500); // Atraso entre as medições
}



