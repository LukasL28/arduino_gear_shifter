// --------------------------------------------------------------------------
// Code By LukasL28 https://github.com/LukasL28/
// OBO Jan H.
// --------------------------------------------------------------------------

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold24pt7b.h>

// --------------------------------------------------------------------------
// Display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// --------------------------------------------------------------------------
// Change timings here!
int clutch_push_delay = 1000;  //in ms
int clutch_release_delay = 1000;  //in ms
int between_piston_delay = 1000; //in ms
int between_valve_delay = 200; //in ms
// --------------------------------------------------------------------------
// define relay's 
#define MB1_1 2 // MM1 out
#define MB1_2 3 // MM1 mid
#define MB1_3 4 // MM1 in
#define MB2_1 5 // MM2 out
#define MB2_2 6 // MM2 mid
#define MB2_3 7 // MM2 in
#define MB3_1 8 // MM3
// define buttons
#define Button_UP 10
#define Button_DOWN 11
#define Button_Reverse_unlock 12
#define Button_Nlock 13 // Prevents the clutch from firing when the paddel is pressed manually
// --------------------------------------------------------------------------


#define in 1
#define mid 2
#define out 3

#define MB1 1
#define MB2 2

#define pressed 1
#define released 0

//System variables DONT CHANGE
int Button_DOWN_last = LOW;
int Button_UP_last = LOW;

int gear_counter = 1; //gear counter Initial
// 0 = reverse gear; 1 = neutral; 2 - 6 = gear 1 - 5 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

  Serial.begin(115200);
  // initialize display
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
  
  digitalWrite(MB1_1, LOW);
  digitalWrite(MB1_2, LOW);
  digitalWrite(MB1_3, LOW);
  digitalWrite(MB2_1, LOW);
  digitalWrite(MB2_2, LOW);
  digitalWrite(MB2_3, LOW);
  digitalWrite(MB3_1, LOW);

  pinMode(MB1_1, OUTPUT);
  pinMode(MB1_2, OUTPUT);
  pinMode(MB1_3, OUTPUT);
  pinMode(MB2_1, OUTPUT);
  pinMode(MB2_2, OUTPUT);  
  pinMode(MB2_3, OUTPUT);
  pinMode(MB3_1, OUTPUT);
  pinMode(Button_UP, INPUT);
  pinMode(Button_DOWN, INPUT);
  pinMode(Button_Reverse_unlock, INPUT);
  pinMode(Button_Nlock, INPUT);

  // set default state
  gears(1);
}

void loop() {

gear_display(gear_counter);

if (digitalRead (Button_Reverse_unlock) == HIGH && digitalRead(Button_UP) == HIGH && Button_UP_last == LOW) {
  // Paddel up + Reverse lock to get in to neutral
  gear_counter = 1; 
  gears(1);
}

if (digitalRead (Button_DOWN) == HIGH && Button_DOWN_last == LOW && gear_counter > 0) {
  if (gear_counter > 1) { // prevents the reverse gear if not in neutral
    gear_counter--;
    gears(gear_counter);
  } else {
    if (digitalRead (Button_Reverse_unlock) == HIGH) {
      gear_counter = 0;
      gears(0);
    }
  }
}

if (digitalRead (Button_UP) == HIGH && Button_UP_last == LOW && gear_counter < 6 ) {
  gear_counter++;
  gears(gear_counter);
}

// save last state for flank detection
Button_DOWN_last = digitalRead(Button_DOWN);
Button_UP_last = digitalRead(Button_UP);

}

void gear_display(int number) {

  display.setCursor(2,85);
  display.clearDisplay();

  switch (number)
  {
  case 0: // special case reverse
      display.println("R");
    break;

  case 1: // special case neutral
      display.println("N");
    break;
  default:
      display.println(number-1);
    break;
  }

  display.display();
}

void clutch(int state){
  if (digitalRead (Button_Nlock) == LOW) 
  {
    switch (state)
    {
      case pressed:
        digitalWrite(MB3_1, HIGH);
        break;
      case released:
        digitalWrite(MB3_1, LOW);
        break;
      default:
        break;
    }
  } else {
    digitalWrite(MB3_1, LOW);
  }
  

}

void piston(int name, int state) {
  switch (name) {
    case MB1:
      switch (state) 
      {
        case in:
          digitalWrite(MB1_1, LOW);
          digitalWrite(MB1_2, LOW);
          digitalWrite(MB1_3, HIGH);
          break;
        case mid:
          digitalWrite(MB1_1, HIGH);
          digitalWrite(MB1_2, LOW);
          delay(between_valve_delay);
          digitalWrite(MB1_3, HIGH);
          break;
        case out:
          digitalWrite(MB1_1, LOW);
          digitalWrite(MB1_2, HIGH);
          digitalWrite(MB1_3, LOW);
          break;
        default:
          break;
      }
      break;
    case MB2:
      switch (state) 
      {
      case in:
          digitalWrite(MB2_1, LOW);
          digitalWrite(MB2_2, LOW);
          digitalWrite(MB2_3, HIGH);
          break;
        case mid:
          digitalWrite(MB2_1, HIGH);
          digitalWrite(MB2_2, LOW);
          delay(between_valve_delay);
          digitalWrite(MB2_3, HIGH);
          break;
        case out:
          digitalWrite(MB2_1, LOW);
          digitalWrite(MB2_2, HIGH);
          digitalWrite(MB2_3, LOW);
          break;
        default:
          break;
      }
      break;
  }
}

void gears(int gear){

    switch (gear)
    {
    case 0: //reverse
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(between_piston_delay);
        piston(MB2, out);
        delay(clutch_release_delay);
        piston(MB1, out);
        delay(clutch_release_delay);
        clutch(released);
        break;
      break;
    case 1: //neutral 
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(between_piston_delay);
        piston(MB2, mid);
        delay(clutch_release_delay);
        clutch(released);
      break;
    case 2: //1st
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(between_piston_delay);
        piston(MB2, in);
        delay(clutch_release_delay);
        piston(MB1, in);
        delay(clutch_release_delay);
        clutch(released);
      break;

    case 3: //2nd
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(between_piston_delay);
        piston(MB2, in);
        delay(clutch_release_delay);
        piston(MB1, out);
        delay(clutch_release_delay);
        clutch(released);
        break;

    case 4: //3rd
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(clutch_push_delay);
        piston(MB2, mid);
        delay(between_piston_delay);
        piston(MB1, in);
        delay(clutch_release_delay);
        clutch(released);
          break;

    case 5: //4th
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(clutch_push_delay);
        piston(MB2, mid);
        delay(between_piston_delay);
        piston(MB1, out);
        delay(clutch_release_delay);
        clutch(released);
          break;

    case 6: //5th
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(between_piston_delay);
        piston(MB2, out);
        delay(clutch_release_delay);
        piston(MB1, in);
        delay(clutch_release_delay);
        clutch(released);
          break;

    default: //fallback to neutral
        clutch(pressed);
        delay(clutch_push_delay);
        piston(MB1, mid);
        delay(between_piston_delay);
        piston(MB2, mid);
        delay(clutch_release_delay);
        clutch(released);
      break;
    }
}