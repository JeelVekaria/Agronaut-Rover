#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

const int soilMoisturePin = A0;
const int tempPin = A4;
const int buttonPin = 8;


int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button
int state = 0;

const int dryValue = 870;  // calibrated dry value
const int wetValue = 0;     // calibrated wet value

void setup() {
  
  pinMode(buttonPin, INPUT);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);


  lcd.begin(16, 2);
  lcd.print("TEAM ECLIPSE'S");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("AGRONAUT");
  delay(1000);
  lcd.clear();
}

void loop() {



  /* SOIL MOISTURE */
  int soilMoistureValue = analogRead(soilMoisturePin);
  // Map the soil moisture value to a percentage
  int moisturePercentage = map(soilMoistureValue, wetValue, dryValue, 0, 100);
  
  /* TEMPERATURE */
  int tempValue = analogRead(tempPin);
  float voltage = tempValue * 5.0;
  voltage /= 1024.0;
  float tempCelsius = (voltage - 0.5) * 10;

  /* BUTTON */
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
        if (state == 0) state = 1;
        else state = 0;
        lcd.clear();
    }
    delay(50);
  }
  
  lastButtonState = buttonState;

  // Display
  if (state == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Soil Moisture: ");
    lcd.setCursor(0, 1);
    lcd.print(moisturePercentage);
    lcd.print("%");
  }
  else if (state == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.setCursor(0, 1);
    lcd.print(tempCelsius, 1);  // Display temperature with 1 decimal place
    lcd.print(" C");
  }
  
  delay(100);  // Adjust as needed


}