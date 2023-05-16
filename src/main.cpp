#include <main.h>
#include <utilities.h>
#include <auth.h>

InfluxDBClient client(INFLUXDB_HOST, INFLUXDB_ORGANISATION, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
Point sensor("WifiStatus");

void setup()
{
  Serial.begin(9600);
  while (!Serial) {};

  Utilities::authenticateWifi();
  pinMode(LED, OUTPUT);

  client.validateConnection()
    ? Serial.printf("Connected to InfluxDB: %s\n", client.getServerUrl().c_str())
    : Serial.printf("InfluxDB connection failed: %s\n", client.getLastErrorMessage().c_str());

  Serial.printf("%s\n", DIVIDER);
}

void loop()
{
  sensor.clearFields();
  sensor.addField("RSSI", WiFi.RSSI());

  Serial.printf("Writing: %s\n", client.pointToLineProtocol(sensor).c_str());

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }

  if (!client.writePoint(sensor)) {
    Serial.printf("InfluxDB write failed: %s\n", client.getLastErrorMessage().c_str());
  }

  Serial.printf("Waiting %dms...\n", DELAY * 100);
  delay(DELAY * 100);
}