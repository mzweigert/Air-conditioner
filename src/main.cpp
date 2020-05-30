#include<Wire.h>
#include<SPI.h>
#include<DHT.h>

int minFanAnalogVal = 10;
int maxFanAnalogVal = 100;
int current = minFanAnalogVal;

#define DHT11_PIN D2
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(D1, OUTPUT); // sets the pins as outputs:

  dht.begin();
  analogWriteRange(100); // to have a range 1 - 100 for the fan
  analogWriteFreq(10000);
  analogWrite(D1, minFanAnalogVal);
}

void loop() {

}