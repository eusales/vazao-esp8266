# vazao-esp8266

Sistema de monitoramento de vazão de água (entrada/saída) usando ESP8266 + LCD I2C 16x2.

## Funcionalidades

- Medição de vazão de entrada e saída em L/min
- Totalizador de água em litros
- Proteção contra valores negativos
- Exibição em display LCD I2C 16x2

## Componentes

- ESP8266 (NodeMCU ou Wemos D1 Mini)
- Display LCD I2C 16x2 (endereço 0x27)
- 2 sensores de vazão (hall effect)
- Fiação e protoboard

## Estrutura

```
/
├── Teste_Individual/        # Testes isolados de componentes
│   ├── Sensor_Input_Output/
│   ├── SensorHC-SR04/
│   ├── ReleDuplo_Blink/
│   └── DisplayI2C16X2/
├── TesteDisplayeSensoresVazao/  # Código principal integrado
└── Documentação/           # Manuais e diagramas
```

## Pinos (GPIO)

| Componente       | Pino  |
|------------------|-------|
| Sensor Entrada   | GPIO0 |
| Sensor Saída     | GPIO2 |
| SDA (I2C)        | GPIO12|
| SCL (I2C)        | GPIO14|

## Calibração

O fator de calibração padrão é **7.5 pulsos por litro**. Ajuste conforme especificação do seu sensor.

## Bibliotecas

- `Wire.h`
- `LiquidCrystal_I2C.h`
