#include <Microduino_Dust.h>
#include <Microduino_Tem_Hum.h>

Tem_Hum     termo;   //AM2321
Tem_Hum_S2  termoS2; //SHT2X

SoftwareSerial mySerial(4, -1); // RX, TX
Dust pmSensor(&mySerial);    //使用软串口

float sensor_tem, sensor_hum, sensor_light, Sensor_etoh;
float sensorPM25;

boolean AM_online, S2_online;

void getSensorDate()
{
  sensor_light = map(analogRead(LIGHTPIN), 0, 1023, 0, 255);
  Sensor_etoh = map(analogRead(ETOHPIN), 0, 1023, 0, 30);

  if (AM_online)
  {
    sensor_tem = termo.getTemperature();
    delay(500);
    sensor_hum = termo.getHumidity();
    delay(500);
  }
  else if (S2_online)
  {
    sensor_tem = termoS2.getTemperature();
    sensor_hum = termoS2.getHumidity();
  }
  else if (!AM_online && !S2_online)
  {
    sensor_tem = 0;
    sensor_hum = 0;
  }

  if (pmSensor.available()) {
    sensorPM25 = pmSensor.getPM25();
  }
}
