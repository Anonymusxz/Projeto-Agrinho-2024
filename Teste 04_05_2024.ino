//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL: https://github.com/RobTillaart/DHTstable


#include "DHTStable.h"

DHTStable DHT;

#define DHT11_PIN 2
#define pin_bomba 6

float umidade_solo = 0;
float temp_ambiente = 0.0;
float umidade_ambiente = 0.0;

float valorA0 = 0;

long long tempo_leitura_sensor = 0;
long long tempo_leitura_cmd_bomba = 0;
long long tempo_escreve_serial = 0;



void setup() {
  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");

  pinMode(pin_bomba, OUTPUT);
  digitalWrite(pin_bomba, 1);
}


void loop() {

  //inicio leitura do sensor de umidade

  if (millis() - tempo_leitura_sensor > 50) {

    valorA0 = analogRead(A0);
    umidade_solo = map(valorA0, 1023, 325, 0, 100);


    //fim letura do sensor de umidade

    // READ DATA
    //Serial.print("DHT11, \t");
    int chk = DHT.read11(DHT11_PIN);
    switch (chk) {
      case DHTLIB_OK:
        //Serial.print("OK,\t");
        break;
      case DHTLIB_ERROR_CHECKSUM:
        //Serial.print("Checksum error,\t");
        break;
      case DHTLIB_ERROR_TIMEOUT:
        //Serial.print("Time out error,\t");
        break;
      default:
        //Serial.print("Unknown error,\t");
        break;
    }
    // DISPLAY DATA
    umidade_ambiente = DHT.getHumidity();
    temp_ambiente = DHT.getTemperature();

    tempo_leitura_sensor = millis();
  }


  if (millis() - tempo_escreve_serial > 2000) {

    Serial.print("Valor analogica = ");
    Serial.print(valorA0);
    Serial.print(" umidade solo = ");
    Serial.print(umidade_solo);
    Serial.println("%");

    Serial.print(umidade_ambiente);
    Serial.print(" ");
    Serial.println(temp_ambiente);

    tempo_escreve_serial = millis();
  }

  if (millis() - tempo_leitura_cmd_bomba > 5000) {

    if (umidade_solo < 60.0) {

      digitalWrite(pin_bomba, LOW);
      delay(400);
      digitalWrite(pin_bomba, HIGH);
    }
    tempo_leitura_cmd_bomba = millis();
  }
}


// -- END OF FILE --
