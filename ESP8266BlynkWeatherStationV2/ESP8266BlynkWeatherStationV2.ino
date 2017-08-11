#define BLYNK_PRINT Serial // Enables Serial Monitor

#include "userDef.h"
#include "sensor.h"
#include "oled.h"
#include "WiFiBlynk.h"

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  
  //检测AM2321是否在线
  for (uint8_t i = 0; i < 2; i++)
  {
    if (termo.begin())
    {
      AM_online = true;
      Serial.println("------AM2321 is online---------");
    }
    else
    {
      AM_online = false;
      Serial.println("------AM2321 is offline---------");
    }
    delay(500);
  }
  
  //检测SHT2X是否在线
  if (termoS2.begin())
  {
    S2_online = true;
    Serial.println("------SHT2X is online---------");
  }
  else
  {
    S2_online = false;
    Serial.println("------SHT2X is offline---------");
  }

  // Set ESP8266 baud rate
  EspSerial.begin(115200);
  delay(10);
  Blynk.begin(auth, wifi, SSID, PASS);

  // Setup a function to be called every second
  temHumtimer.setInterval(2000L, senTempHumi);
  delay(10);
}


void loop() {
  Blynk.run(); // All the Blynk Magic happens here...
  temHumtimer.run(); // Initiates SimpleTimer

  getSensorDate();

  oled(sensor_tem, sensor_hum, sensor_light, sensorPM25, Sensor_etoh);
}



