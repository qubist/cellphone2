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
unsigned int loadingPos = 0;
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


int x,y;

void setup(){
  Serial.begin(9600);
  screen.begin();
  screen.flip();
  screen.clear();
  x = y = 0;
}

int brightness = 15;
unsigned long lastKeyPressTime;


int i = 128;  
void loop(){
	
    char key = keypad.getKey();
	
    if (key){
      Serial.println(key);
    }
	
	
//    if (key == 'U') { brightness += 1; } 
//    if (key == 'D') { brightness -= 1; }
//    if (key == 'U' || key == 'D') { brightness = constrain(brightness, 0, 15); screen.setBrightness(brightness); lastKeyPressTime = millis(); screen.setCursor(0); screen.write(128 + (constrain(brightness - 1,0,15) / 2)); screen.print(brightness); screen.display(); delay(100); }

    if (key == 'D') { screen.draw(x,y,false); y++; if (y>6) y = 0; } 
    if (key == 'U') { screen.draw(x,y,false); y--; if (y<0) y = 6; } 

    if (key == 'R') { screen.draw(x,y,false); x++; if (x>5*8-1) x = 0; } 
    if (key == 'L') { screen.draw(x,y,false); x--; if (x<0) x = 5*8-1; } 

	screen.draw(x,y,true);
//    screen.print(" TEST!");
    screen.loadDotRegister();

	
// 	loading();
//	loadingDelay(1000,5);
//	if (i > 135) i = 128;
 //   loadingDelay(1000,4);
}
