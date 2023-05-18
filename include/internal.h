namespace Internal
{
    InfluxDBClient client(INFLUXDB_HOST, INFLUXDB_ORGANISATION, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Readings");
    DHT dht(DHT_PIN, DHT_TYPE);
    Adafruit_SGP30 sgp;

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
}
