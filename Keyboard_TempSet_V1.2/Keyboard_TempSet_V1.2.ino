#include <Keypad.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// GPIO where the DS18B20 is connected to
  const int oneWireBus = D13;     
// Setup a oneWire instance to communicate with any OneWire devices
  OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
  DallasTemperature sensors(&oneWire);

#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Keypad Configuration
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {D2, D3, D4, D5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D6, D7, D8, D9}; //connect to the column pinouts of the keypads of the keypad
//Create an object of keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Variables to store the two digits and combine them

char customKey =0;
double setTemp = 0;
float temperatureC=0.00;
float temperatureS=0.00;

void setup() {

  Serial.begin(9600);             // Start the Serial Monitor

  sensors.begin();                 // Start the DS18B20 sensor

  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.clearDisplay(); 

  OLED.setTextSize(1);              // text size = 1
  OLED.setTextColor(YELLOW);         // set text color to white and black background
  OLED.setCursor(15, 0);            // move cursor to position (25, 0) pixel
  OLED.print("WiFi Thermostat");

  OLED.setCursor(20, 10);
  OLED.print("CurrentTemp:");
  
  OLED.setCursor(20, 30);
  OLED.print("SetTemp: ");

  OLED.display();  // Update the display
}

void loop() {
  char customkey = customKeypad.getKey();
  delay(10);
   switch(customKey) 
  {
  case '0' ... '9': // This keeps collecting the first value until a operator is pressed "+-*/"
    setTemp = setTemp * 10 + (customKey - '0');
    showDisplay();  
    break;

  case 'A':
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    showDisplay();  
    break;

  case 'B':
    float temperatureC = 0.00;
    float temperatureS = 0.00;
    showDisplay();  
    break;
  }

}

void showDisplay()
{
  OLED.setCursor(20, 20);
  OLED.setTextSize(1);      // text size = 1
  
  OLED.printf(" %02u.%02u C", (int)temperatureC % 100, (int)(temperatureC * 100) % 100 );
  OLED.drawCircle(60, 23, 1, YELLOW);

  OLED.setCursor(20,40);
  OLED.printf(" %02u.%02u C", (int)temperatureS % 100, (int)(temperatureS * 100) % 100 );
  OLED.drawCircle(60, 43, 1, YELLOW);  
  OLED.display();           // update the display
}