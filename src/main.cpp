#include "common.h"
#include "auth.h"
#include "utilities.h"
#include "internal.h"

using namespace strict_variant;
using namespace Internal;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  Utilities::authenticateWifi();

  client.validateConnection()
    ? Serial.printf("Connected to InfluxDB: %s.\n", client.getServerUrl().c_str())
    : Serial.printf("InfluxDB connection failed: %s.\n", client.getLastErrorMessage().c_str());

  sgp.begin()
    ? Serial.println("Connected to SGP30 successfully.")
    : Serial.println("Failed to connect to SGP30.");

  dht.begin();

  sensor.addField("Module", MODULE);
  sensor.addField("SSID", WIFI_SSID);
  PRINT_DIVIDER();
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  sgp.setHumidity(Utilities::getAbsoluteHumidity(temperature, humidity));

  if (!sgp.IAQmeasure()) Serial.printf("%s CO2 Measurement failed.", CO2_SENSOR);
  if (!sgp.IAQmeasureRaw()) Serial.printf("%s Raw Measurement failed.", CO2_SENSOR);

  if (!isnan(temperature) && !isnan(humidity)) 
  {
    digitalWrite(LED_PIN, HIGH);

    std::vector<std::pair<std::string, variant<float, uint16_t>>> measurements = {
      {"Temperature", temperature},
      {"Humidity", humidity},
      {"Carbon Dioxide", sgp.eCO2},
      {"TVOC", sgp.TVOC},
      {"Ethanol", sgp.rawEthanol},
      {"Hydrogen", sgp.rawH2}
    };

    sensor.clearFields();
    for (const auto& pair : measurements) 
    {
      auto measurement = pair.first;
      auto value = pair.second;
      apply_visitor(Visitor(measurement), value);
    }

    Serial.printf("Writing: %s.\n", client.pointToLineProtocol(sensor).c_str());

    if (WiFi.status() != WL_CONNECTED) Serial.println("Wifi connection lost.");
    if (!client.writePoint(sensor)) Serial.printf("InfluxDB write failed: %s.\n", client.getLastErrorMessage().c_str());
    
    Serial.printf("Waiting %d seconds before recording next reading...\n", DELAY / 1000);
    PRINT_DIVIDER();

    digitalWrite(LED_PIN, LOW);
    delay(DELAY);
  } 
  else 
  {
    Serial.printf("Temperature: %f Humidity: %f\n", temperature, humidity);
  }
}
