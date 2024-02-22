#include <DHT11.h>
DHT11 dht11(2);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int temperature = dht11.readTemperature();
  int humidity = dht11.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  delay(1000);
}
