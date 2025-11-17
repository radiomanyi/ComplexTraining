#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
char tempdisplay[10];

// GPIO where the DS18B20 is connected to
  const int oneWireBus = D10;     
// Setup a oneWire instance to communicate with any OneWire devices
  OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
  DallasTemperature sensors(&oneWire);


#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay(); 
  Serial.begin(9600);// Start the Serial Monitor
  sensors.begin();  // Start the DS18B20 sensor
}

void loop()
{
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  dtostrf(temperatureC,4,1,tempdisplay);
  display.setCursor(0,0);
  display.println("WiFi Thermosat");
  display.print("Temp is:");
  display.print(tempdisplay);//show the temperature in OLED
  display.println("℃");
  display.display();
  delay(5000);
}