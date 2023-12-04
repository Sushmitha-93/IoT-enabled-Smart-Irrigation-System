/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino.org UNO WiFi
  to connect your project to Blynk.

  NOTE: This requires WiFi Link library

  Please update your UNO WiFi firmware to WiFiLink 1.0.0 (at least).

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */

#define BLYNK_TEMPLATE_ID "TMPL2SnAap2O-"
#define BLYNK_TEMPLATE_NAME "Smart irrigation system"
#define BLYNK_AUTH_TOKEN "v9xm3iiTO3EHdHAS6rHd-eiUaCEaIwqq"

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

//initialization
const int dry = 558; //dry constant
const int wet = 239; //wet constant
int automatic;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = <wifi-name>;
char pass[] = <password>;

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
BLYNK_WRITE(V1)
{
  automatic = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}


void myTimerEvent()
{
  int value1 = analogRead(A0);
  int percentageHumidity = map(value1, wet, dry, 100, 0);
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, percentageHumidity);
  if(automatic)
  {
    if(percentageHumidity<70)
    {
    digitalWrite(2, LOW);
    }
    else
    {
    digitalWrite(2, HIGH);
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  digitalWrite(2, LOW);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Setup a function to be called every second
  timer.setInterval(5000L, myTimerEvent);

}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
