//=========================================================|
// Program: OLED Clock 03/05/2018
// Autor: Juan Sirgado y Antico
//=========================================================|
#include <Wire.h>
#include <DS3231.h>
#include <U8glib.h>
//---------------------------------------------------------|
// Definictions of OLED Display
// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
//---------------------------------------------------------|
// Definitions for RTC DS3231
DS3231 Clock;
RTClib RTC;
DateTime dtNow;
// Definicoes do display Oled
String sDate, sTime, sTemp;
String sDay, sMonth, sYear, sWeek;
String sHour, sMinute, sSecond;
bool Century=false;
bool h12;
bool PM;                  
int iContrast = 0;
char cDate[11];
char cTime[9];
char cTemp[13];
char cDoW[10];
const char *cWeek[8] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
const char *cMonth[12] = {"Jan","Feb","Mar","Apr","May","Jun", 
                          "Jul","Aug","Sep","Oct","Nov","Dec"};
//---------------------------------------------------------|
void setup(void)
{
   Serial.begin(19200);
   Wire.begin();
   //---------------------------------------------------------|
   // To set the Date and Time in the Clock
   // Run just once time at the first to adjust the clock, 
   // or after change the Clock battery  
   // setClock(Year, Month, Day, Weekday, Hour, Minute, Second);
   // setClock(19,11,04,1,18,22,30);
//---------------------------------------------------------|
   if ( u8g.getMode() == U8G_MODE_BW ) 
   {
      u8g.setColorIndex(1);  // pixel on monochrome
      u8g.setContrast(iContrast);
      Serial.println("U8G mode mono");
   }
}
//---------------------------------------------------------|
void loop(void)
{
   Serial.println("Inicio Loop");
   // Show the information in the OLED Display
   u8g.firstPage();
   dtNow = RTC.now();
   showClock();
   do
   {
      if(int(dtNow.second()/3)%4 == 0)
      {
         // Read and Draw the Date from the DS3231
         Serial.println("Date Loop");
         drawDate(Clock.getYear(), Clock.getMonth(Century), Clock.getDate());
      }
      if(int(dtNow.second()/3)%4 == 1)
      {
         // Read and Draw the Day of Week from the DS3231
         Serial.println("Time Loop");
         drawWeek(Clock.getDoW());
      }
      if(int(dtNow.second()/3)%4 == 2)
      {
         // Read and Draw the Time from the DS3231
         Serial.println("Week Loop");
         drawTime(Clock.getHour(h12,PM), Clock.getMinute(), Clock.getSecond());
      }
      if(int(dtNow.second()/3)%4 == 3)
      {
         // Read and Draw the temperature from the DS3231
         Serial.println("Temperature Loop");
         drawTemp(Clock.getTemperature());
      }
   }
   while(u8g.nextPage());
   delay(250);
   Serial.println("Fim Loop");
}
//---------------------------------------------------------|
void drawDate(byte bYear, byte bMonth, byte bDay)
{
   // Mount the Time before the draw
   sDay = bDay>9?String(bDay):"0" + String(bDay);
   sMonth = bMonth>9?String(bMonth):"0" + String(bMonth);
   sYear = String(bYear);
   sDate =  sDay + '/' + sMonth + '/' + sYear;
   sDate.toCharArray(cDate, 9);
   // Graphic commands to show the Date
   u8g.drawRFrame(0, 0, 128, 32, 2);
   u8g.setFont(u8g_font_fub20);
   u8g.setColorIndex(1);
   u8g.drawStr( 5, 27, cDate);
}
//---------------------------------------------------------|
void drawTime(byte bHour, byte bMinute, byte bSecond)
{
   // Mount the Time before the draw
   sHour = bHour>9?String(bHour):"0" + String(bHour);
   sMinute = bMinute>9?String(bMinute):"0" + String(bMinute);
   sSecond = bSecond>9?String(bSecond):"0" + String(bSecond);
   sTime = sHour + ':' + sMinute + ':' + sSecond;
   sTime.toCharArray(cTime, 9);
   // Graphic commands to show the Time
   u8g.drawRFrame(0, 0, 128, 32, 2);
   u8g.setFont(u8g_font_fub20);
   u8g.setColorIndex(1);
   u8g.drawStr(10, 27, cTime);
}
//---------------------------------------------------------|
void drawWeek(byte bDoW)
{
   // Mount the Day of Week before the draw
   sWeek = String(cWeek[bDoW-1]);
   sWeek.toCharArray(cDoW, 9);
   // Graphic commands to show the Day of Week
   u8g.drawRFrame(0, 0, 128, 32, 2);
   u8g.setFont(u8g_font_fub20);
   u8g.setColorIndex(1);
   u8g.drawStr( 35, 27, cDoW);
}
//---------------------------------------------------------|
void drawTemp(float fTemp)
{
   // Mount the Temperature before the draw
   sTemp = String(fTemp,1) + "C";
   sTemp.toCharArray(cTemp, 9);
   // Graphic commands to show the Temperature
   u8g.drawRFrame(0, 0, 128, 32, 2);
   u8g.setFont(u8g_font_fub20);
   u8g.setColorIndex(1);
   u8g.drawStr( 30, 27, cTemp);
}
//---------------------------------------------------------|
void setClock(int iYear, int iMonth, int iDay, int iDoW, int iHour, int iMinute, int iSecond)
{ 
   Serial.println("Start of Clock Setup.");
   // Then write it to the clock
   Clock.setClockMode(false);  // set to 24h
   // Clock.setClockMode(true);   // set to 12h
   Clock.setYear(iYear);
   Clock.setMonth(iMonth);
   Clock.setDate(iDay);
   Clock.setDoW(iDoW);
   Clock.setHour(iHour);
   Clock.setMinute(iMinute);
   Clock.setSecond(iSecond);
   showClock();
   Serial.println("End Of Clock Setup.");
}
//---------------------------------------------------------|
void showClock()
{
   // Show the Date and Time for the RTC DS3231  
   Serial.println("The time in the Clock has been set to: YYYY-MM-DD WW HH:MM:SS");
   Serial.print(Clock.getYear(), DEC);
   Serial.print("-");
   Serial.print(Clock.getMonth(Century), DEC);
   Serial.print("-");
   Serial.print(Clock.getDate(), DEC);
   Serial.print(" ");
   Serial.print(Clock.getDoW(), DEC);
   Serial.print(" ");
   Serial.print(Clock.getHour(h12,PM), DEC);
   Serial.print(":");
   Serial.print(Clock.getMinute(), DEC);
   Serial.print(":");
   Serial.println(Clock.getSecond(), DEC);
   Serial.println();
}
//=========================================================|
