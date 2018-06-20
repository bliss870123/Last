#include <Ultrasonic.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "AA201-2G";
char _lwifi_pass[] = "iteaa201";
MCSDevice mcs("DZ8wvwA0", "ACt1I7rAAL2ehyWl");

MCSDisplayInteger  Temp("87878787");

void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");

  mcs.addChannel(Temp);

}


void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
    mcs.process(1000);
    
  float cmMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);


  Serial.print(", CM: ");
  Serial.print(cmMsec);

  delay(1000);
  
  Temp.set(cmMsec);

  delay(200);
}
