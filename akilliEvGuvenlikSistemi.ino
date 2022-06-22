#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "DHT.h"


#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

int buzzerPin = 13;
int trig= 8;
int echo = 9;
long duration=0;
int distance=0;
int yagmurPin = A1;
int yagmurDeger = 0;
int gazPin = A0;
int gazDeger = 0;

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial bt_iletisim(1, 0); // RX,TX
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(buzzerPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(yagmurPin, INPUT);
  pinMode(gazPin,INPUT);
}

void loop() {
  digitalWrite(buzzerPin,HIGH);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    return;
  }
 
  lcd.clear();
  lcd.home();
  lcd.print("Nem ");
  lcd.print(h);
  delay(1000);
  lcd.clear();
  lcd.println("Sicaklik ");
  lcd.print(t);
  lcd.print("°C ");
  delay(1000);

   gazDeger = analogRead(gazPin);
  
  if(gazDeger > 700){
    digitalWrite(buzzerPin,HIGH);
    delay(10);
    digitalWrite(buzzerPin,LOW);
    delay(10);
    
  }else {
      digitalWrite(buzzerPin,HIGH);
    }
  delay(500);
  lcd.clear();
  lcd.print("gaz orani ");
  lcd.print(gazDeger);
  delay(1000); 
  
  yagmurDeger = analogRead(yagmurPin);
  delay(300);
 
  lcd.clear();
  lcd.print("yagmur ");
  lcd.print(yagmurDeger);
  delay(1000); 
  
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  
  lcd.clear();
  lcd.home();
  lcd.print("Mesafe ");
  lcd.print(distance);
  lcd.print(" cm");

  Serial.print(t);
  Serial.print(" C");
  Serial.print("|");
  Serial.print(h);
  Serial.print(" %");
  Serial.print("|");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print("|");
  Serial.print(gazDeger);
  Serial.print("|");
  Serial.print(yagmurDeger);
  
  delay(2000);
  
}
