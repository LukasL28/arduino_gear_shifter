#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int clutch_push_delay = 50;  //in ms
int clutch_release_delay = 50;  //in ms
int betwean_piston_delay = 50; //in ms

// define relay's 
#define MB1_1 2 // MM1 out
#define MB1_2 3 // MM1 mid
#define MB1_3 4 // MM1 in
#define MB2_1 5 // MM2 out
#define MB2_2 6 // MM2 mid
#define MB2_3 7 // MM2 in
#define MB3_1 8 // MM3
#define Button_UP 10
#define Button_DOWN 11

//System variables DONT CHANGE
int Button_DOWN_last = LOW;
int Button_UP_last = LOW;

int gear_counter = 1;

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
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(10, INPUT);
  pinMode(11, INPUT);

}

void loop() {

gear_display(gear_counter);

if (Button_DOWN == HIGH && Button_DOWN_last == LOW) {
  gear_counter--;
}

if (Button_UP == HIGH && Button_UP_last == LOW) {
  gear_counter++;
}


Button_DOWN_last = digitalRead(Button_DOWN);
Button_UP_last = digitalRead(Button_UP);

}

void gear_display(long number) {
  display.setCursor(2,85);
  display.clearDisplay();
  display.println(number);
  display.display();
}

void gears(long gear){

    switch (gear)
    {
    case 0: //reverse
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, HIGH);
        digitalWrite(MB2_2, HIGH);
        digitalWrite(MB2_3, LOW);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, HIGH);
        digitalWrite(MB1_2, HIGH);
        digitalWrite(MB1_3, LOW);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
        break;
      break;
    case 1: //neutral 
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, HIGH);
        digitalWrite(MB2_2, LOW);
        digitalWrite(MB2_3, HIGH);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, HIGH);
        digitalWrite(MB1_2, LOW);
        digitalWrite(MB1_3, HIGH);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
      break;
    case 2: //1st
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, LOW);
        digitalWrite(MB2_2, LOW);
        digitalWrite(MB2_3, HIGH);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, LOW);
        digitalWrite(MB1_2, LOW);
        digitalWrite(MB1_3, HIGH);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
      break;

    case 3: //2nd
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, LOW);
        digitalWrite(MB2_2, LOW);
        digitalWrite(MB2_3, HIGH);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, HIGH);
        digitalWrite(MB1_2, HIGH);
        digitalWrite(MB1_3, LOW);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
        break;

    case 4: //3rd
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, HIGH);
        digitalWrite(MB2_2, LOW);
        digitalWrite(MB2_3, HIGH);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, LOW);
        digitalWrite(MB1_2, LOW);
        digitalWrite(MB1_3, HIGH);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
          break;

    case 5: //4th
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, HIGH);
        digitalWrite(MB2_2, LOW);
        digitalWrite(MB2_3, HIGH);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, HIGH);
        digitalWrite(MB1_2, HIGH);
        digitalWrite(MB1_3, LOW);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
          break;

    case 6: //5th
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, HIGH);
        digitalWrite(MB2_2, HIGH);
        digitalWrite(MB2_3, LOW);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, LOW);
        digitalWrite(MB1_2, LOW);
        digitalWrite(MB1_3, HIGH);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
          break;

    default: //fallback to neutral
        digitalWrite(MB3_1, HIGH);
        delay(clutch_push_delay);
        digitalWrite(MB2_1, HIGH);
        digitalWrite(MB2_2, LOW);
        digitalWrite(MB2_3, HIGH);
        delay(betwean_piston_delay);
        digitalWrite(MB1_1, HIGH);
        digitalWrite(MB1_2, LOW);
        digitalWrite(MB1_3, HIGH);
        delay(clutch_release_delay);
        digitalWrite(MB3_1, LOW);
      break;
    }
}