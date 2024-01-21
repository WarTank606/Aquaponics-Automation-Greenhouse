/*
  Portenta Breakout - BreakoutRTCGet

  The sketch shows how to read the RTC of the Portenta H7 using the Portenta Breakout.

  The circuit:
   - Portenta H7
   - Portenta Breakout
   - CR2032 Battery

  This example code is in the public domain.
*/
#include <Arduino_PortentaBreakout.h>

Timestamp utcTime;


int Eastern_Year = 0, Eastern_Month = 0, Eastern_Day = 0;
int Eastern_Hour = 0, Eastern_Minute = 0, Eastern_Second = 0;
String Formatted_Eastern_Hour = "", Formatted_Eastern_Minute = "";
 
bool Day_Check = false, AM_PM = false, Year_Check = false;

void Read_Date_And_Time() {
  // Read the current timestamp from the RTC
  utcTime = Breakout.RTClock.getTime();
  
  //Create variables to store the Time and Date values
  Eastern_Year = (utcTime.year() + 1900); 
  Eastern_Month = (utcTime.month() + 1);
  Eastern_Day = utcTime.day();
  Eastern_Hour = utcTime.hour() + 20;
  Eastern_Minute = utcTime.minute();
  Eastern_Second = utcTime.second();
  
  
  //If added time goes over the 24 maximum, then substract 24 hours
  if (Eastern_Hour > 23)
  {
    Eastern_Hour = Eastern_Hour - 24;
    
    Day_Check = true; 
    /* UTC day is one day ahead of eastern day, so if this added time pushes past 24 hours, then we know that 1 day has pasted
    so we just use the UTC day */
  }
  //If added time DOES NOT goes over the 24 maximum, then Do Nothing 
  else if (Eastern_Hour <= 23)
  {
    Day_Check = false;
    /* UTC day is one day ahead of eastern day, so if this added time DOES NOT push past 24 hours, then we know that 1 day has NOT pasted
    so we just use the (UTC day - 1) */
  }
  
  
  
  //Depending on Day_Check, we either remove a day from Eastern Date or Do Nothing 
  if (Day_Check == false)
  {
    Eastern_Day = (Eastern_Day - 1);
  }
  
  /*
  If adjusting the Eastern Day causes it to become 0 or negative, then what has happened is that it was the 1st day of a new month,
  so we now need to subtract the month by 1, and then determine the last day of that month.
  */
  if ((Eastern_Day) <= 0)
  {
    
    Eastern_Month = (utcTime.month() + 1) - 1; //Subtracting the month by 1
    
    //If subtracting the month makes it 0, then is was probably January(1), so make it December(12)
    if (Eastern_Month == 0)
    {
      Eastern_Month = 12;
      Year_Check = true; //We also need to back 1 year because we're going from January to December
    }
    
    //Subtracting the year by 1
    if (Year_Check == true)
    {
      Eastern_Year = (utcTime.year() + 1900) - 1;
    }
    
    //Different months have different last days, determine whether it's 31, 30, or 28 
    if (Eastern_Month == 1 || Eastern_Month == 3 || Eastern_Month == 5 || Eastern_Month == 7 || Eastern_Month == 8 || Eastern_Month == 10 || Eastern_Month == 12)
    {
     Eastern_Day = 31;
    }
    else if (Eastern_Month == 4 || Eastern_Month == 6 || Eastern_Month == 9 || Eastern_Month == 11)
    {
     Eastern_Day = 30;
    }
    else if (Eastern_Month == 2)
    {
     Eastern_Day = 28;
    }
    
    
  }
  
  //Check if we are in AM or PM Time
  if (Eastern_Hour > 12)
  {
    Eastern_Hour = Eastern_Hour - 12;
    AM_PM = true;
  }
  else if (Eastern_Hour < 12)
  {
    AM_PM = false;
  }
  
  //Create the final version of the Time and Date and make it a string
  Formatted_Eastern_Hour = String(Eastern_Hour);
  Formatted_Eastern_Minute = String(Eastern_Minute);
  
  /*These format the string value, so it the value is NOT a double digit then add a '0',
    but if it is a double digit then Do Nothing
  */
  if (Eastern_Hour < 10)
  {
    Formatted_Eastern_Hour = "0" + Formatted_Eastern_Hour;
  }
  
  if (Eastern_Minute < 10)
  {
    Formatted_Eastern_Minute = "0" + Formatted_Eastern_Minute;
  }
  
  
  /*Check whether the AM_PM is true or false, and add the correct string to complete the format
  */
  if (AM_PM == true)
  {
    Full_Eastern_Time = Formatted_Eastern_Hour + ":" + Formatted_Eastern_Minute + " PM"; // Completed Eastern Time PM
  }
  else if (AM_PM == false)
  {
    Full_Eastern_Time = Formatted_Eastern_Hour + ":" + Formatted_Eastern_Minute + " AM"; // Completed Eastern Time AM
  }
  
  Full_Eastern_Date = String(Eastern_Year) + "/" + String(Eastern_Month) + "/" + String(Eastern_Day); // Completed Eastern Date PM
 
}

void Display_Time_Date()
{
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("***************************************"); 
  Serial.print("\n");
  Serial.print("Date: ");
  Serial.print(Full_Eastern_Date);
  Serial.print("\n");
  Serial.print("Time: ");
  Serial.print(Full_Eastern_Time);
  Serial.print("\n");
}


