#include <JeeLib.h>
#include <PortsLCD.h>
#include <dht.h>

ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup for low power waiting

const int sleepTime = 30000; //30sec

const int sensorPin = A0;
const float baselineTemp = 20.0;
const float optimalTemp = 35.0;
const float maxTemp = 40;

LiquidCrystal lcd(12,11, 9,8,7,6);

/**
*  Temperature Sensor
**/

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 8     // what digital pin we're connected to

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600); // open serial port
  
  dht.begin();

  lcd.begin(16,2);
  
  lcd.print("initializing :)");
  lcd.setCursor(0,1);
  
  for(int pinNumber = 2; pinNumber<5; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop()
{
  //int sensorVal = analogRead(sensorPin);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
 
  Serial.println(temperature);
  
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  
  if(temperature < baselineTemp)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if(temperature >= baselineTemp && temperature < optimalTemp)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if(temperature >= optimalTemp && temperature < maxTemp)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  else if(temperature >= maxTemp)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  
  //delay(sleepTime);
  Sleepy::loseSomeTime(sleepTime);
    
}
  
