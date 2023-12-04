// Blynk app info
#define BLYNK_TEMPLATE_ID "XXXXX-"
#define BLYNK_TEMPLATE_NAME "XXXXX"
#define BLYNK_AUTH_TOKEN "XXXXX"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// Initialization
const int soilSensorPin = A0; // Analog input pin for the soil moisture sensor
const int relayPin = 2; // Digital output pin for the relay
const int WET = 280; // Wet constant
const int DRY = 560; // Dry constant
const char ssid[] = "XXXXX"; // Wifi name
const char pass[] = "XXXXX"; // wifi pass
int automatic=1;
int manual=0;
BlynkTimer timer;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Set relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

BLYNK_WRITE(V1)
{
  automatic = param.asInt(); // assigning incoming value from pin V1 to a variable
  //Serial.print("********automatic*************");
  //Serial.println(automatic);
}

BLYNK_WRITE(V2)
{
  manual = param.asInt(); // assigning incoming value from pin V1 to a variable
  //Serial.print("*********manual************");
  //Serial.println(manual);
}

void myTimerEvent(){
  // Read analog input from Soil Moisture sensor
  int rawValue = analogRead(soilSensorPin);
  // Map value to percentage
  int percentageMoisture = map(rawValue,WET,DRY,100,0);
  
  
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print("\tMapped Value: ");
  Serial.println(percentageMoisture);

  Blynk.virtualWrite(V0, percentageMoisture); // Virtual output pin for Blynk

  if((manual==1)|| ((automatic==1) && (percentageMoisture < 70))){
    digitalWrite(relayPin, LOW);
    Serial.println("Relay Activated");
  }else{
    digitalWrite(relayPin, HIGH);
    Serial.println("Relay Deactivated");
  }
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer  
}
