#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definindo os pinos SDA e SCL
#define SDA_PIN 12  // GPIO12
#define SCL_PIN 14  // GPIO14

// Endereço do display I2C (pode ser 0x27 ou 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16 colunas e 2 linhas

void setup() {
  // Inicia a comunicação I2C nos pinos definidos
  Wire.begin(SDA_PIN, SCL_PIN);  
  
  lcd.begin(16, 2);   // Inicializa o display com 16 colunas e 2 linhas
  lcd.backlight();    // Liga o retroiluminação
  
  // Exibe uma mensagem no display
  lcd.setCursor(0, 0);  // Coloca o cursor na primeira linha e coluna
  lcd.print("Athirson ");

  lcd.setCursor(0, 1);  // Coloca o cursor na segunda linha
  lcd.print("Baitola");
}

void loop() {
  // Nada a fazer no loop
}