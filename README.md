# Esp-32 Sensor Records
## A PlatformIO project which records various metrics, such as:
- Temperature
- Humidity
- Carbon Dioxide
- TVOC
- Ethanol
- Hydrogen

#### This uses the following physical modules:
- ESP32 for running the binary via USB, the core of the project
- DHT22 for recording Temperature and Humidity (aswell as calculating Absolute Humidity for the SGP30)
- SGP30 for recording Carbon Dioxide, Ethanol, etc

<hr />

#### This project uses the variant library, as INO C++ is outdated and there is no official variant type.
This is implemented by creating a vector of pairs of strings and variants, where the type can either be a float or an integer.
```cpp
std::vector<std::pair<std::string, variant<float, uint16_t>>> measurements = {
  {"Temperature", temperature},
  {"Humidity", humidity},
  {"Carbon Dioxide", sgp.eCO2},
  {"TVOC", sgp.TVOC},
  {"Ethanol", sgp.rawEthanol},
  {"Hydrogen", sgp.rawH2}
};
```
Afterwards, a Visitor is created, available in the Internal namespace, which adds the field provided when the value is called on it:
```cpp
struct Visitor 
{
    std::string _measurement;
    Visitor(std::string measurement) : _measurement(measurement) {};

    void operator() (float value)const 
    {
        sensor.addField(_measurement.c_str(), value);
    }

    void operator() (uint16_t value)const 
    {
        sensor.addField(_measurement.c_str(), value);
    }
};
```
And finally the Visitor is applied to the vector:
```cpp
for (const auto& pair : measurements) 
{
  auto measurement = pair.first;
  auto value = pair.second;
  apply_visitor(Visitor(measurement), value);
}
```

<hr />

### About sending the recordings to InfluxDB:
The module first connects to the InfluxDB instance, using this call inside Internal.h
```cpp
InfluxDBClient client(INFLUXDB_HOST, INFLUXDB_ORGANISATION, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
```
Note that all of the constants are inside of file called `auth.h` which is gitignored.

During runtime setup, the module validates that it has successfully connected to the database:
```cpp
client.validateConnection()
    ? Serial.printf("Connected to InfluxDB: %s.\n", client.getServerUrl().c_str())
    : Serial.printf("InfluxDB connection failed: %s.\n", client.getLastErrorMessage().c_str());
```

When writing, it simply attempts to write to the point defined in the authentication header, and logs if it fails.
```cpp
if (!client.writePoint(sensor)) Serial.printf("InfluxDB write failed: %s.\n", client.getLastErrorMessage().c_str());
```

<hr />

WiFi connection on this ESP32 is reimplemented, using wrapper methods, following this structure:
- `WiFi::setup()` Disconnects from the WiFi if already connected, configures the WiFi with INADDR_NONE, and sets the mode to STA (standard)
- `WiFi::hostname()` Sets the hostname of the network to the Sensor-{MAC_ADDRESS}
- `WiFi::debug()` Prints to the debug console relevant information about the WiFi, such as MAC Address, IP, SSID, etc
- `WiFi::connect()` Attempts to connect to the WiFi, calling `WiFi.begin()` with the private WIFI_SSID and WIFI_PASSWORD, waiting for `WiFi.status()` to be connected.

In practice (`Utilities::authenticateWifi()`):
- Call `WiFi::setup()` to configure the connection
- Call `WiFi::hostname()` to set the network hostname
- Call `WiFi::connect()` and review the returned boolean:
  - If the return value is `true`, then the connection was successful!
  - Otherwise, recursively call the `authenticateWifi()` function again
- Call `WiFi::debug()` for relevant information about the connection

<hr />

♡ Made by Rosie
Copyright © 2023 Rosie ([acquitelol](https://github.com/acquitelol))

```
All rights reserved.
All software is provided for educational purposes only, and should not be used for unlawful or unethical purposes.
```
