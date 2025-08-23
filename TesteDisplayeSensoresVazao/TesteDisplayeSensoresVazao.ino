#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_INPUT_PIN 0   // Pino digital para sensor de entrada de água (GPIO19)
#define SENSOR_OUTPUT_PIN 2  // Pino digital para sensor de saída de água (GPIO18)

volatile int inputFlowCount = 0;  // Contador de pulsos do sensor de entrada
volatile int outputFlowCount = 0; // Contador de pulsos do sensor de saída

float inputFlowRate = 0.0;        // Vazão de entrada em litros por minuto
float outputFlowRate = 0.0;       // Vazão de saída em litros por minuto
float totalWater = 0.0;           // Total de água (em litros) armazenada

unsigned long lastTime = 0;

// Definindo os pinos SDA e SCL no ESP8266
#define SDA_PIN 12
#define SCL_PIN 14

// Definindo o display LCD com o endereço 0x27 e 16 colunas por 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

void IRAM_ATTR sensorInputInterrupt() {
  inputFlowCount++;  // Incrementa quando o sensor de entrada detecta um pulso
}

void IRAM_ATTR sensorOutputInterrupt() {
  outputFlowCount++;  // Incrementa quando o sensor de saída detecta um pulso
}

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial

  // Configura os pinos I2C com o SDA e SCL definidos
  Wire.begin(SDA_PIN, SCL_PIN); // Configura os pinos I2C

  // Inicializando o LCD 

  lcd.backlight();  // Liga o backlight

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bem-vindo ao");
  lcd.setCursor(0, 1);
  lcd.print("Sistema de Vazao");

  delay(10000);  // Espera 2 segundos para exibir a saudação

  // Calibrando display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrando");
  lcd.setCursor(0, 1);
  lcd.print("Display...");
  delay(15000);  // Espera 1.5 segundos

  // Calibrando sensores de vazão
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrando");
  lcd.setCursor(0, 1);
  lcd.print("Sensores...");
  delay(20000);  // Espera 1.5 segundos

  // Define os pinos dos sensores como entrada com resistor pull-up
  pinMode(SENSOR_INPUT_PIN, INPUT_PULLUP);
  pinMode(SENSOR_OUTPUT_PIN, INPUT_PULLUP);

  // Configura as interrupções para os sensores
  attachInterrupt(digitalPinToInterrupt(SENSOR_INPUT_PIN), sensorInputInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_OUTPUT_PIN), sensorOutputInterrupt, FALLING);

  // Inicializa a comunicação serial
  Serial.println("Iniciando monitoramento de vazão...");
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

    // Exibe as informações no display LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Entrada: ");
    lcd.print(inputFlowRate, 1);
    lcd.print(" L/min");

    lcd.setCursor(0, 1);
    lcd.print("Saida: ");
    lcd.print(outputFlowRate, 1);
    lcd.print(" L/min");

    // Imprime as informações no monitor serial de forma estruturada
    Serial.println("\n===============================");
    Serial.println("Monitoramento de Vazão:");
    Serial.print("Vazão de Entrada: ");
    Serial.print(inputFlowRate, 1);
    Serial.println(" L/min");

    Serial.print("Vazão de Saída: ");
    Serial.print(outputFlowRate, 1);
    Serial.println(" L/min");

    Serial.print("Total de Água: ");
    Serial.print(totalWater, 1);
    Serial.println(" L");

    Serial.println("===============================");
  }
}


