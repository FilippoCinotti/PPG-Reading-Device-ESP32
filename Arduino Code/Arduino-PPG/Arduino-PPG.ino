int LEDPIN = 11;
int PINDATA = A0;


String stringECG = "0";
int HeartBeat = 0;
float data = 0, thresh = 52000, HRV = 0, HR = 0;
unsigned long Rcurrent = 0, Tcurrent = 0, Ptime = 0;
bool inrange = false;


// Import required libraries
#include <ArducamSSD1306.h>    // Modification of Adafruit_SSD1306 for ESP8266 compatibility
#include <Adafruit_GFX.h>   // Needs a little change in original Adafruit library (See README.txt file)
#include <Wire.h>           // For I2C comm, but needed for not getting compile error

/*
  HardWare I2C pins
  A4   SDA
  A5   SCL
*/

// Pin definitions
#define OLED_RESET  16  // Pin 15 -RESET digital signal

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

ArducamSSD1306 display(OLED_RESET); // FOR I2C

void setup() {
  // initialize the serial communication:
  Serial.begin(19200);
  pinMode(LEDPIN, OUTPUT); // Setup for led
  Ptime = millis();

  // SSD1306 Init
  display.begin();  // Switch OLED
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.println("Hello, Arducam!");
  display.display();

}

void loop() {
  String string = " ";
  // send the value of analog input 0:
  // Serial.println(data);
  data = analogRead(A0);
  data = data * 100;
  delay(30);
  //Serial.println(data);
  if (data >= thresh) {
    if (inrange == false) {
      HeartBeat++;
      Tcurrent = millis();
      HRV = Tcurrent - Rcurrent;
      Rcurrent = Tcurrent;
      digitalWrite(LEDPIN, HIGH);
      delay(500);
    }
    inrange = true;
    //digitalWrite(LEDPIN,LOW);

  }
  else
  {
    inrange = false;
    digitalWrite(LEDPIN, LOW);
  }

  if (millis() - Ptime > 10000) {
    HR = 6 * HeartBeat;
    Ptime = millis();
    HeartBeat = 0;
  }
  Serial.print(HR);
  Serial.write(',');
  Serial.print(HRV);
  Serial.write(',');
  Serial.println(data);
  display.clearDisplay();
    display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,20);
  display.print("Heart Rate: ");
  display.setCursor(20,30);
  display.print(HR);
  display.display();
}
