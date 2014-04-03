#include "Arduino.h"

/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <LedDisplay.h>
LedDisplay screen = LedDisplay(22, 21, 20, 18, 17, 8);

const byte ROWS = 6;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'!','U','?'},
  {'L','D','R'},
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};  
byte rowPins[ROWS] = {25, 27, 28, 29, 30, 31};
byte colPins[COLS] = {26, 24, 23};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const char *loadingStr="-\\|/";
const unsigned long loadingAdvance = 100;
unsigned long loadingTime = 0;
unsigned int loadingi = 0;
unsigned int loadingPos = 7;
void loading() {
  unsigned long m = millis();
  if (m > loadingTime) {
    loadingTime = m+loadingAdvance;
    if (loadingi > 3) loadingi = 0;
    screen.setCursor(loadingPos);
    screen.print(loadingStr[loadingi++]);
    screen.display();
  }
}

void loadingDelay(unsigned long d,unsigned int p) {
  loadingPos = p;
  d += millis();
  while(millis() < d) {
    loading();
  }
}


void setup(){
  Serial.begin(9600);
  screen.begin();
  screen.flip();
  screen.clear();
}

int brightness = 15;


int i = 128;  
void loop(){
	
	
	
    if (key == 'U') { brightness += 1; } 
    if (key == 'D') { brightness -= 1; }
    if (key == 'U' || key == 'D') { brightness = constrain(brightness, 0, 15); screen.setBrightness(brightness); lastKeyPressTime = millis(); screen.setCursor(7); screen.write(128 + (brightness / 2)); screen.display(); delay(100); }
	
    screen.setCursor(0);
    screen.write(i++);
    screen.display();
	loadingDelay(1000,5);
	if (i > 135) i = 128;
 //   loadingDelay(1000,4);
}
