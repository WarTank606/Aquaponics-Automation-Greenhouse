#include "Time_Date_Control.h"

int Eastern_Seconds = 0;

int Preset_Fish_Start_Seconds = 0, Preset_Fish_End_Seconds = 0;
int Preset_Hydro_Start_Seconds = 0, Preset_Hydro_End_Seconds = 0;
int Preset_Soil_Start_Seconds = 0, Preset_Soil_End_Seconds = 0;

const unsigned char Fish_Light = 0; //Digital Pin
const unsigned char Hydro_Light = GPIO_5; //Digital Pin
const unsigned char Soil_Light = GPIO_4; //Digital Pin

void Fish_Light_Control()
{
  Read_Date_And_Time(); //Get Eastern Time
  
  if (AM_PM == true)
  {
    Eastern_Seconds = ((Eastern_Hour + 12) * 3600) + (Eastern_Minute * 60); //Convert to Seconds for easier comparison  
  }
  else if (AM_PM == false)
  {
    Eastern_Seconds = ((Eastern_Hour) * 3600) + (Eastern_Minute * 60); //Convert to Seconds for easier comparison
  }
  
  
  //Create new values to store start and end seconds for each unit
  Preset_Fish_Start_Seconds = Preset_Fish_Start;
  Preset_Fish_End_Seconds = Preset_Fish_End;
  
  // Check if eastern seconds is greater or equal to END time, if so turn the light OFF
  if (Eastern_Seconds >= Preset_Fish_End_Seconds)
  {
    Light_Statue_Fish = false; // Update light staue
  }
  // Check if eastern seconds is greater or equal to START time, and less then END time, if so turn the light ON
  else if ((Eastern_Seconds >= Preset_Fish_Start_Seconds) && (Eastern_Seconds < Preset_Fish_End_Seconds))
  {
    Light_Statue_Fish = true; // Update light staue
  }
  // Check if eastern seconds is less then START time, if so turn the light OFF
  else if (Eastern_Seconds < Preset_Fish_Start_Seconds)
  {
    Light_Statue_Fish = false; // Update light staue
  }
}


void Hydro_Light_Control()
{
  Read_Date_And_Time(); //Get Eastern Time
  
  //Create new values to store start and end seconds for each unit
  Preset_Hydro_Start_Seconds = Preset_Hydro_Start;
  Preset_Hydro_End_Seconds = Preset_Hydro_End;
  
  // Check if eastern seconds is greater or equal to END time, if so turn the light OFF
  if (Eastern_Seconds >= Preset_Hydro_End_Seconds)
  {
    Light_Statue_Hydro = false; // Update light staue
  }
  // Check if eastern seconds is greater or equal to START time, and less then END time, if so turn the light ON
  else if ((Eastern_Seconds >= Preset_Hydro_Start_Seconds) && (Eastern_Seconds < Preset_Hydro_End_Seconds))
  {
    Light_Statue_Hydro = true; // Update light staue
  }
  // Check if eastern seconds is less then START time, if so turn the light OFF
  else if (Eastern_Seconds < Preset_Hydro_Start_Seconds)
  {
    Light_Statue_Hydro = false; // Update light staue
  }
}


void Soil_Light_Control()
{
  Read_Date_And_Time(); //Get Eastern Time

  //Create new values to store start and end seconds for each unit
  Preset_Soil_Start_Seconds = Preset_Soil_Start;
  Preset_Soil_End_Seconds = Preset_Soil_End;
  
  // Check if eastern seconds is greater or equal to END time, if so turn the light OFF
  if (Eastern_Seconds >= Preset_Soil_End_Seconds)
  {
    Light_Statue_Soil = false; // Update light staue
  }
  // Check if eastern seconds is greater or equal to START time, and less then END time, if so turn the light ON
  else if ((Eastern_Seconds >= Preset_Soil_Start_Seconds) && (Eastern_Seconds < Preset_Soil_End_Seconds))
  {
    Light_Statue_Soil = true; // Update light staue
  }
  // Check if eastern seconds is less then START time, if so turn the light OFF
  else if (Eastern_Seconds < Preset_Soil_Start_Seconds)
  {
    Light_Statue_Soil = false; // Update light staue
  }
}


void Display_Light_Statue()
{
  Serial.print("\n\n");
  
  Serial.print("Eastern_Seconds: ");
  Serial.print(Eastern_Seconds);
  Serial.print("\n");
  
  Serial.print("Preset Fish Start Seconds: ");
  Serial.print(Preset_Fish_Start_Seconds);
  Serial.print("\n");
  Serial.print("Preset_Fish_End_Seconds: ");
  Serial.print(Preset_Fish_End_Seconds);
  Serial.print("\n");
  
  Serial.print("Preset_Hydro_Start_Seconds: ");
  Serial.print(Preset_Hydro_Start_Seconds);
  Serial.print("\n");
  Serial.print("Preset_Hydro_End_Seconds: ");
  Serial.print(Preset_Hydro_End_Seconds);
  Serial.print("\n");
  
  Serial.print("Preset_Soil_Start_Seconds: ");
  Serial.print(Preset_Soil_Start_Seconds);
  Serial.print("\n");
  Serial.print("Preset_Soil_End_Seconds: ");
  Serial.print(Preset_Soil_End_Seconds);
  
  //Determine Light Staue of Fish unit
  Serial.print("\n");
  Serial.print("***************************************");
  Serial.print("Lighting Statue");
  Serial.print("\n");
  Serial.print("\n");
  
  if (Light_Statue_Fish == true)
  {
  Serial.print("Light Statue Fish: ON");
  digitalWrite(Fish_Light, HIGH);
  }
  else if (Light_Statue_Fish == false)
  {
  Serial.print("Light Statue Fish: OFF");
  digitalWrite(Fish_Light, LOW);
  }
  
  Serial.print("\n");
  
  //Determine Light Staue of Hydro unit
  if (Light_Statue_Hydro == true)
  {
  Serial.print("Light Statue Hydro: ON");
  digitalWrite(Hydro_Light, HIGH);
  }
  else if (Light_Statue_Hydro == false)
  {
  Serial.print("Light Statue Hydro: OFF");
  digitalWrite(Hydro_Light, LOW);
  }
  
  Serial.print("\n");
  
  //Determine Light Staue of Soil unit 
  if (Light_Statue_Soil == true)
  {
  Serial.print("Light Statue Soil: ON");
  digitalWrite(Soil_Light, HIGH);
  }
  else if (Light_Statue_Soil == false)
  {
  Serial.print("Light Statue Soil: OFF");
  digitalWrite(Soil_Light, LOW);
  }
  
  Serial.print("\n\n");
}