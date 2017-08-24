#include <LiquidCrystal.h>
#include <SPI.h>
#include "DHT.h"

#define DHTPIN 8     // what digital pin we're connected to

#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float sum_hum=0, max_hum=0, avg_hum ;
float sum_t=0, max_t=0, avg_t ;

int  count=1, current_sec=0, past_sec=1;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); 
  Serial.println("Intializing!");
  lcd.setCursor(0, 0);
  lcd.print("Intializing!");
  
  dht.begin(); 
  }

void loop() {
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  sum_t+=t;
  avg_t=sum_t/(count);
  
  if(t>max_t)
  max_t=t;
  
  
  sum_hum+=h;
  avg_hum=sum_hum/(count);
   
  if(h>max_hum)
  max_hum=h;
  
  count++;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  
  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(h);
  lcd.print(" %");

delay(1000);  

current_sec=millis();
if ((current_sec-past_sec)>30000)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp Avg: ");
  lcd.print(avg_t);
  
  lcd.setCursor(0, 1);
  lcd.print("Temp Max: ");
  lcd.print(max_t);
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hum Avg: ");
  lcd.print(avg_hum);
  
  lcd.setCursor(0, 1);
  lcd.print("Hum Max: ");
  lcd.print(max_hum);
  
  delay(1500);
  past_sec=millis();
}
}
