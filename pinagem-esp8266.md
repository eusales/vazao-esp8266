# Pinagem ESP8266 (NodeMCU)

| Pino no ESP8266 | GPIO   | Pino Físico | Função/Descrição                                      |
|-----------------|--------|-------------|-------------------------------------------------------|
| D0              | GPIO16 | 16          | Entrada/Saída (também usado para Deep Sleep)          |
| D1              | GPIO5  | 5           | I2C SDA (pode ser usado para outros fins)             |
| D2              | GPIO4  | 4           | I2C SCL (pode ser usado para outros fins)             |
| D3              | GPIO0  | 0           | Entrada/Saída (pode ser usado para Bootmode)          |
| D4              | GPIO2  | 2           | Entrada/Saída (pino de boot de inicialização)         |
| D5              | GPIO14 | 14          | HSPI SCK (pode ser usado para outros fins)            |
| D6              | GPIO12 | 12          | HSPI MISO (pode ser usado para outros fins)           |
| D7              | GPIO13 | 13          | HSPI MOSI (pode ser usado para outros fins)           |
| D8              | GPIO15 | 15          | HSPI CS (pode ser usado para outros fins)             |
| D9              | GPIO3  | 3           | RX (UART)                                             |
| D10             | GPIO1  | 1           | TX (UART)                                             |
| VCC             | -      | 3.3V        | Alimentação do dispositivo                            |
| GND             | -      | GND         | Terra                                                 |
| ADC (A0)        | GPIO17 | 17          | Entrada analógica (0-1V)                              |

## Pinos utilizados neste projeto

| Função              | Pino  |
|---------------------|-------|
| Sensor Vazão Entrada| D3 (GPIO0) |
| Sensor Vazão Saída  | D4 (GPIO2) |
| I2C SDA (Display)   | D6 (GPIO12) |
| I2C SCL (Display)   | D5 (GPIO14) |

## Observações

- **GPIO0 (D3)** e **GPIO2 (D4)** são pinos de boot - cuidado ao usar como entrada
- **GPIO16 (D0)** não suporta interrupções
- Pinos **D9** e **D10** são usados para comunicação serial (não usar se precisar de Serial)
- **ADC (A0)** aceita apenas 0-3.3V - usar divisor de tensão para 5V
