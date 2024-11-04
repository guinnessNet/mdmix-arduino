/* @file MultiKey.ino
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/
#include <Wire.h>
#include "Motor.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
// #include "Scanner.h"
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the kpd

Motor motor1(11);
Motor motor2(12);
Motor motor3(13);
Motor* motors[] = { &motor1, &motor2, &motor3 }; // Motor 객체 포인터 배열


class Display {
  public:
    Display() : display(Adafruit_SSD1306(128, 64, &Wire, 4)) {
    }
    void init() {
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      display.display();
      delay(2000); // Pause for 2 seconds
      display.clearDisplay();
    } 

    void print(String msg) {
      display.clearDisplay();
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(0,12);
      display.println(msg);
      display.display();
    }


    void updateDisplay(){
      display.clearDisplay();

      for (int i=0; i< 3; i++){
        int spinValue = motors[i]->getSpin(); // 포인터를 사용하여 getSpin 호출
        Serial.print(spinValue);
        Serial.println(" update display");
        display.setTextSize(1);
        display.setCursor(0, i * 16);
        display.print("M");
        display.print(i + 1);
        display.print(": ");
        display.print(spinValue);
        // int barLength = map(spinValue, 0, 1000, 0, 64);
        display.fillRect(40, i * 16 + 2, spinValue, 10, SSD1306_WHITE);
    // 스텝 값에 따른 바 표시
      }
    display.display();
    }
    void displaySpinStart(){
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,12);
      display.println("Motor Start!");
      display.display();
    }
    void drawRect(){
      display.clearDisplay();
      display.drawRoundRect(10, 10, 128-10, 32, 20, SSD1306_WHITE);
      display.display();
    };
    
  private:
    Adafruit_SSD1306 display;
};

// Adafruit_SSD1306 display(128, 64, &Wire, 4);


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// unsigned long loopCount;
// unsigned long startTime;
// String msg;


Display display;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // 모터가 작동하는동안 LED가 켜지도록 설정(현재는 우노의 기본 LED)
    Serial.begin(9600);
    while (!Serial); // 시리얼 모니터가 준비될 때까지 대기
    Serial.println("\nI2C Scanner");
    display.init();
    display.print("hello world!");
    delay(1000);
    display.drawRect();
    Serial.println("init display");
    
    display.updateDisplay();
    // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    // Display display;
    // display.clearDisplay();



    // display.print("I2C Scanner");

// 버퍼를 비움
    // display.clearDisplay();
    // scanI2C();
    // loopCount = 0;
    // startTime = millis();

};



void loop() {
  // Serial.println("loop");
  // display.updateDisplay();
  // display.print(String(loopCount));
  // display.display();
  // loopCount++;
  // delay(1000);
    // if ( (millis()-startTime)>5000 ) {
    //     Serial.print("Average loops per second = ");
    //     Serial.println(loopCount/5);
    //     startTime = millis();
    //     loopCount = 0;
    // }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged && kpd.key[i].kstate == PRESSED)   // Only find keys that have changed state.
            {
              switch (kpd.key[i].kchar) {
                case '1':
                  motor1.increaseSpin();
                  break;
                case '2':
                  motor1.decreaseSpin();
                  break;
                case '3':
                  motor1.resetSpin();
                  break;
                case 'A':
                  display.displaySpinStart();
                  motor1.spinMotor();
                  break;
                case '4':
                  motor2.increaseSpin();
                  break;
                case '5':
                  motor2.decreaseSpin();
                  break;
                case '6':
                  motor2.resetSpin();
                  break;
                case 'B':
                  display.displaySpinStart();
                  motor2.spinMotor();
                  break;
                case '7':
                  motor3.increaseSpin();
                  break;
                case '8':
                  motor3.decreaseSpin();
                  break;
                case '9':
                  motor3.resetSpin();
                  break;
                case 'C':
                  display.displaySpinStart();
                  motor3.spinMotor();
                  break;
              }

            }
        }
    }
    // 모터 업데이트
    motor1.update();
    motor2.update();
    motor3.update();

    display.updateDisplay();
    delay(100); // 100ms 대기
}  // End loop