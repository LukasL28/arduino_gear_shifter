#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.setFont(&FreeMonoBold24pt7b);
  display.clearDisplay();
  display.setRotation(3);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  // Display static text
  
  //pinMode(2, OUTPUT);
  //pinMode(3, OUTPUT);
  //pinMode(4, OUTPUT);
  //pinMode(5, OUTPUT);
  //pinMode(6, OUTPUT);  
  //pinMode(7, OUTPUT);
  //pinMode(8, OUTPUT);
  //pinMode(9, OUTPUT);
}

void loop() {

      display.setCursor(2,85);
  display.clearDisplay();
  display.println("R");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("N");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("1");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("2");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("3");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("4");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("5");
  display.display();
  delay(500);
  display.setCursor(2,85);
  display.clearDisplay();
  display.println("6");
  display.display();
  delay(500);

}
