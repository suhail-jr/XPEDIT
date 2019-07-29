#include<Wire.h>
#include<SPI.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>


#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

#define LOGO16_GLCD_HEIGHT 9
#define LOGO16_GLCD_WIDTH  9
const unsigned char tempicon[]PROGMEM = {
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x3c, 0x0, 0x0,
  0x0, 0x7c, 0x0, 0x0,
  0x0, 0x7e, 0xfc, 0x0,
  0x0, 0x7e, 0xfe, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x70, 0x0,
  0x0, 0x7e, 0xf8, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x70, 0x0,
  0x0, 0x7e, 0x70, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x40, 0x0,
  0x0, 0x7e, 0x60, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0x7e, 0x0, 0x0,
  0x0, 0xfe, 0x0, 0x0,
  0x1, 0xff, 0x0, 0x0,
  0x3, 0xff, 0x80, 0x0,
  0x3, 0xff, 0x80, 0x0,
  0x3, 0xff, 0xc0, 0x0,
  0x3, 0xff, 0xc0, 0x0,
  0x3, 0xff, 0xc0, 0x0,
  0x3, 0xff, 0x80, 0x0,
  0x1, 0xff, 0x80, 0x0,
  0x1, 0xff, 0x0, 0x0,
  0x0, 0x7c, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0
};

bool status;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;


int temp;
int hum;
int alt;
int prsr;

char c_temp[20];
char c_hum[20];
char c_alt[20];
char c_prsr[20];

void setup() {
  status = bme.begin();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();

  display.clearDisplay();



}

void loop()
{ 
  sensorValue();
  display.clearDisplay();
  disp_frame();
  display_data();

 


}

void sensorValue()
{

  temp = bme.readTemperature(); // *c
  hum = bme.readHumidity();// %
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA);//m
  prsr = bme.readPressure() / 100.0F; //hpa
  itoa(temp, c_temp, 10);
  itoa(temp, c_hum, 10);
  itoa(prsr, c_prsr, 10);
  itoa(alt, c_alt, 10);
  strcat(c_temp, "C");
  strcat(c_hum, "%");
  strcat(c_prsr, "hPa");
  strcat(c_alt, "M");



}

void disp_frame()
{

  display.setTextColor(WHITE);
  display.drawFastVLine( 63, 0, 48, WHITE);
  display.drawFastVLine( 66, 0, 48, WHITE);
  display.drawFastHLine( 0, 48, 63, WHITE);
  display.drawFastHLine( 63, 48, 65, WHITE);

  display.drawFastHLine( 0, 50, 63, WHITE);
  display.drawFastVLine( 63, 50, 14, WHITE);

  display.drawFastHLine( 66, 50, 63, WHITE);
  display.drawFastVLine( 66, 50, 14, WHITE);

  display.setTextSize(1);
  display.setCursor(18, 52);
  display.println("menu");

  display.setTextSize(1);
  display.setCursor(74, 53);
  display.println("bat: 80%");

  display.display();

  //display.drawBitmap(25, 2, tempicon, 10, 15, WHITE);

}
void disp_frame2()
{

  display.setTextColor(WHITE);
  
  display.drawFastHLine( 0, 48, 128, WHITE);


  display.drawFastHLine( 0, 50, 63, WHITE);
  display.drawFastVLine( 63, 50, 14, WHITE);

  display.drawFastHLine( 66, 50, 63, WHITE);
  display.drawFastVLine( 66, 50, 14, WHITE);

  display.setTextSize(1);
  display.setCursor(18, 52);
  display.println("menu");
  display.setTextSize(1);
  display.setCursor(74, 53);
  display.println("bat: 80%");

  display.display();

  //display.drawBitmap(25, 2, tempicon, 10, 15, WHITE);

}

void display_data()
{



  display.setTextSize(1);
  display.setCursor(0, 3);
  display.println("temperatur");
  display.setTextSize(3);
  display.setCursor(5, 20);
  display.println(c_temp);


  display.setTextSize(1);
  display.setCursor(73, 3);
  display.println("humidity");
  display.setTextSize(3);
  display.setCursor(73, 20);
  display.println(c_hum);
  display.display();
  delay(2000);
  display.clearDisplay();

  disp_frame2();



  display.setTextSize(1);
  display.setCursor(33, 3);
  display.println("Air Pressure");
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.println(c_prsr);
 display.display();
  delay(2000);
  display.clearDisplay();
disp_frame2();
  display.setTextSize(1);
  display.setCursor(38, 3);
  display.println("Altitude");
  display.setTextSize(2);
  display.setCursor(40, 25);
  display.println(c_alt);
  display.display();
  delay(2000);

  display.clearDisplay();

}

