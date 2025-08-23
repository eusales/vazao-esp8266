#define SENSOR_INPUT_PIN 0    // Pino digital para sensor de entrada de água (GPIO19)
#define SENSOR_OUTPUT_PIN 2   // Pino digital para sensor de saída de água (GPIO18)

volatile int inputFlowCount = 0;  // Contador de pulsos do sensor de entrada
volatile int outputFlowCount = 0; // Contador de pulsos do sensor de saída

float inputFlowRate = 0.0;        // Vazão de entrada em litros por minuto
float outputFlowRate = 0.0;       // Vazão de saída em litros por minuto
float totalWater = 0.0;           // Total de água (em litros) armazenada

unsigned long lastTime = 0;

void IRAM_ATTR sensorInputInterrupt() {
  inputFlowCount++;  // Incrementa quando o sensor de entrada detecta um pulso
}

void IRAM_ATTR sensorOutputInterrupt() {
  outputFlowCount++;  // Incrementa quando o sensor de saída detecta um pulso
}

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial

  // Define os pinos dos sensores como entrada com resistor pull-up
  pinMode(SENSOR_INPUT_PIN, INPUT_PULLUP);
  pinMode(SENSOR_OUTPUT_PIN, INPUT_PULLUP);

  // Configura as interrupções para os sensores
  attachInterrupt(digitalPinToInterrupt(SENSOR_INPUT_PIN), sensorInputInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_OUTPUT_PIN), sensorOutputInterrupt, FALLING);
}

void loop() {
  // A cada 1 segundo, calcula e imprime a vazão e atualiza o total de água
  if (millis() - lastTime >= 1000) {
    lastTime = millis();

    // Calcula a vazão de entrada e saída: 7,5 pulsos por litro (ajuste conforme necessário)
    inputFlowRate = inputFlowCount / 7.5;
    outputFlowRate = outputFlowCount / 7.5;

    // Atualiza o total de água armazenada, mas não permite que o total seja negativo
    totalWater += inputFlowRate;  // A cada segundo, adiciona a entrada de água
    totalWater -= outputFlowRate; // Subtrai a saída de água

    // Evita que o total de água seja negativo
    if (totalWater < 0) {
      totalWater = 0.0;  // Zera o total de água caso seja negativo
    }

    // Reseta os contadores de pulsos para o próximo ciclo
    inputFlowCount = 0;
    outputFlowCount = 0;

    // Imprime as informações no monitor serial
    Serial.print("Vazão de entrada: ");
    Serial.print(inputFlowRate);
    Serial.println(" L/min");

    Serial.print("Vazão de saída: ");
    Serial.print(outputFlowRate);
    Serial.println(" L/min");

    Serial.print("Total de água: ");
    Serial.print(totalWater);
    Serial.println(" L");
  }
}
