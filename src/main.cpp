#include <main.h>
#include <utilities.h>
#include <auth.h>

InfluxDBClient client(INFLUXDB_HOST, INFLUXDB_ORGANISATION, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
Point sensor("Readings");
DHT dht(DHT_PIN, DHT_TYPE);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {};

  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  Utilities::authenticateWifi();

  sensor.addField("Device", DEVICE);
  sensor.addField("SSID", WIFI_SSID);

  client.validateConnection()
    ? Serial.printf("Connected to InfluxDB: %s\n", client.getServerUrl().c_str())
    : Serial.printf("InfluxDB connection failed: %s\n", client.getLastErrorMessage().c_str());

  Serial.printf("%s\n", DIVIDER);
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    digitalWrite(LED_PIN, HIGH);

    sensor.clearFields();
    sensor.addField("Temperature", temperature);
    sensor.addField("Humidity", humidity);

    Serial.printf("Writing: %s\n", client.pointToLineProtocol(sensor).c_str());

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }

    if (!client.writePoint(sensor)) {
      Serial.printf("InfluxDB write failed: %s\n", client.getLastErrorMessage().c_str());
    }

    Serial.printf("Waiting %dms...\n", DELAY);
    Serial.printf("%s\n", DIVIDER);
    delay(DELAY);
  } else {
    Serial.printf("Temperature: %f Humidity: %f\n", temperature, humidity);
  }
}