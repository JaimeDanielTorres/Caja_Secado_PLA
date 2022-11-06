 #include "Adafruit_BME280.h"
 #include "SPI.h"
 #include <LiquidCrystal.h>
 
 #define BME_SCK 13 // Serial Clock
 #define BME_MISO 12 // Serial Data Out
 #define BME_MOSI 11 // Serial Data In
 #define BME_CS 10 // Chip Select

 #define SEALEVELPRESSURE_HPA (1013.25)

 const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

 float temp=0, hume=0;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    lcd.setCursor(0, 0);
    lcd.print(" No se encontro");
    lcd.setCursor(0, 1);
    lcd.print(" BME280");
    while (1);
  }
  Serial.println("Pressure\tHumdity\t\tTemp");
  
  lcd.setCursor(0, 0);
  lcd.print("Cargando...");
  for(int i=0; i<=15; i++){
    lcd.setCursor(i, 1);
    lcd.print(".");
    delay(50);
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Temperatura OK  ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Humedad OK      ");
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("Temperat:       ");
  lcd.setCursor(0, 1);
  lcd.print("Humedad:        ");

}

void loop() {
  bme.takeForcedMeasurement(); // has no effect in normal mode

  temp=bme.readHumidity();
  hume=bme.readTemperature();
 
  Serial.print(hume); Serial.print("% \t\t");
  Serial.print(temp); Serial.println(" *C\t"); // temperature in Centigrades

  lcd.setCursor(10, 0);
  lcd.write(temp);
  lcd.setCursor(10, 1);
  lcd.write(hume);
  lcd.setCursor(14, 1);
  lcd.print("%");
  delay(2000);
 
 }



 
