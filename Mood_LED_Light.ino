#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int lightPin = A1;
int redPin = 5;
int greenPin = 6;
int bluePin = 11;
double high_temp = 26;
double low_temp = 25.6;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

double pre_red, pre_green, pre_blue;
double red, green, blue;

void loop()
{
  float temp = dht.readTemperature();
  int temp_value = random(3);
  initial_RGB(temp, temp_value);

  //display code
  Serial.println("Temperature:");
  Serial.println(temp);
  //Serial.println(temp_value);

  for (int i = 0; i < 200; i++)
  {
    double adjust = analogRead(lightPin) / 850.0;
    setColour((pre_red + (red - pre_red) * i / 200 * adjust), (pre_green + (green - pre_green) * i / 200 * adjust), (pre_blue + (blue - pre_blue) * i / 200));
    delay(25);
    Serial.println(adjust);
    /*
    Serial.print("Current red value: ");
    Serial.print((pre_red + (red - pre_red) * i / 200) * adjust);
    Serial.print("   Current green value: ");
    Serial.print((pre_green + (green - pre_green) * i / 200) * adjust);
    Serial.print("   Current blue value: ");
    Serial.println((pre_blue + (blue - pre_blue) * i / 200) * adjust);
    */
  }
  pre_red = red;
  pre_green = green;
  pre_blue = blue;
}
 
void setColour(double red, double green, double blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void change_RGB(int red0, int green0, int blue0)
{
  red = red0;
  green = green0;
  blue = blue0;
}

void initial_RGB(float temp, int temp_value)
{
  if(temp >= high_temp)
  {
    if(temp_value == 0)
    change_RGB(255, 0, 0);
    else if(temp_value == 1)
    change_RGB(255, 127, 0);
    else
    change_RGB(255, 255, 0);
  }
  else if(temp <= low_temp)
  {
    if(temp_value == 0)
    change_RGB(0, 255, 255);
    else if(temp_value == 1)
    change_RGB(0, 127, 255);
    else
    change_RGB(0, 0, 255);
  }
  else
  {
    if(temp_value == 0)
    change_RGB(127, 255, 0);
    else if(temp_value == 1)
    change_RGB(0, 255, 0);
    else
    change_RGB(0, 255, 127);
  }
}
