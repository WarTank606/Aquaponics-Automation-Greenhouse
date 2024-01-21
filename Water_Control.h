/*
  # Example code for the moisture sensor
  # Editor     : Lauren
  # Date       : 13.01.2012
  # Version    : 1.0
  # Connect the sensor to the A0(Analog 0) pin on the Arduino board

  # the sensor value description
  # 0  ~300     dry soilhttps://create.arduino.cc/
  # 300~700     humid soil
  # 700~950     in water
*/

#include <Arduino_PortentaBreakout.h>

const unsigned char Fish_Water_Sensor = A7;
const unsigned char Hydro_Water_Sensor = A6;
const unsigned char Soil_Water_Sensor = A5;
const unsigned char Hydro_Reservoir_Water_Sensor = A4;
const unsigned char Soil_Reservoir_Water_Sensor = A3;
// Low 535
// Mid 
//High 

const unsigned char waterpump_1 = PWM5; //Fish Tank
const unsigned char waterpump_2 = PWM1; //Soil Reservoir 
const unsigned char waterpump_3 = PWM2; //Hydro Reservoir
const unsigned char waterpump_4 = PWM7; //Soil Unit
const unsigned char waterpump_5 = PWM9; //Hydro Unit

//PWM0, PWM3, PWM4, PWM6 NOT WORKING
//GPI0 4, 6
int water_pump_speed_1 = 0;
int water_pump_speed_2 = 0;
int water_pump_speed_3 = 0;
int water_pump_speed_4 = 0;
int water_pump_speed_5 = 0;

int Timer_1 = 0;
int Timer_2 = 0;
int Timer_3 = 0;
int Over_Under_Timer = 0;
int Over_Under_Timer_2 = 0;
int Over_Under_Timer_3 = 0;
int Over_Under_Timer_4 = 0;
int Over_Under_Timer_5 = 0;

int Current_Time_1 = 0;
int Current_Time_2 = 0;
int Current_Time_3 = 0;
int Current_Time_4 = 0;
int Current_Time_5 = 0;
int Current_Time_6 = 0;
int Current_Time_7 = 0;
int Current_Time_8 = 0;

int Past_Time_1 = 0;
int Past_Time_2 = 0;
int Past_Time_3 = 0;
int Past_Time_4 = 0;
int Past_Time_5 = 0;
int Past_Time_6 = 0;
int Past_Time_7 = 0;
int Past_Time_8 = 0;

int Flooding_Frequency_Read = 0;
int Flooding_Duration_Read = 0;

bool Set_Timer_1 = false;
bool Set_Timer_2 = false;
bool Set_Timer_3 = false;
bool Set_Timer_4 = false;
bool Set_Timer_5 = false;
bool Set_Timer_6 = false;
bool Set_Timer_7 = false;
bool Set_Timer_8 = false;


void Read_Water_Level()
{
  // Reset all level values to 0
  Fish_Level = 0;
  Hydro_Level = 0;
  Soil_Level = 0;
  Soil_Reservoir_Level = 0;
  Hydro_Reservoir_Level = 0;

  // Read water level from sensors
  Fish_Level = analogRead(Fish_Water_Sensor);
  Hydro_Level = analogRead(Hydro_Water_Sensor);
  Soil_Level = analogRead(Soil_Water_Sensor);
  Soil_Reservoir_Level = analogRead(Soil_Reservoir_Water_Sensor);
  Hydro_Reservoir_Level = analogRead(Hydro_Reservoir_Water_Sensor);
}

void Watering_Soil_Unit()
{
  if (Manual == false)
  {
  
    if (Display_Statue_Soil == "Low")
    {
      if (Set_Timer_3 == false)
      {
        Past_Time_3 = millis();
        Set_Timer_3 = true;
        Water_Pump_Speed_Percentage_4 = 100;
      }
    }
  
  
    Current_Time_3 = millis(); // Get Current Time
  
    Timer_3 = Current_Time_3 - Past_Time_3;  // Determine the amount of milliseconds that have past
  
    if (Timer_3 >= 3000)
    {
      Set_Timer_3 = false;
      Water_Pump_Speed_Percentage_4 = 0;
    }
    
  }
}

void Determine_Water_Column()
{

  //Determine height of water column
  if (Fish_Level > 800)
  {
    // Increase Current Flow Rate
    // Low Water Level
    Display_Statue_Fish = "Low";
    Current_Time_4 = millis();

  }
  else if (Fish_Level > 500 && Fish_Level < 800)
  {
    // Maintain Current Flow Rate
    // Normal Mode
    Display_Statue_Fish = "Normal";
  }
  else if (Fish_Level < 500)
  {
    // Decrease Current Flow Rate
    // Draining Mode
    Display_Statue_Fish = "High";
  }


  //Determine height of water column
  if (Hydro_Level > 800)
  {
    // Increase Current Flow Rate
    // Low Water Level
    Display_Statue_Hydro = "Low";
  }
  else if (Hydro_Level > 500 && Hydro_Level < 800)
  {
    // Maintain Current Flow Rate
    // Normal Mode
    Display_Statue_Hydro = "Normal";
  }
  else if (Hydro_Level < 500)
  {
    if (Set_Mode != 3)
    {
      // Decrease Current Flow Rate
      // Draining Mode
      Display_Statue_Hydro = "High";
    }

    if (Hydro_Level < 450)
    {
      // Decrease Current Flow Rate
      // Draining Mode
      Display_Statue_Hydro = "High";
    }

  }

  //Determine height of water column
  if (Soil_Reservoir_Level > 800)
  {
    // Increase Current Flow Rate
    // Low Water Level
    Display_Statue_Soil_Reservoir = "Low";
  }
  else if (Soil_Reservoir_Level > 500 && Soil_Reservoir_Level < 800)
  {
    // Maintain Current Flow Rate
    // Normal Mode
    Display_Statue_Soil_Reservoir = "Normal";
  }
  else if (Soil_Reservoir_Level < 500)
  {
    // Decrease Current Flow Rate
    // Draining Mode
    Display_Statue_Soil_Reservoir = "High";
  }


  //Determine height of water column
  if (Hydro_Reservoir_Level > 800)
  {
    // Increase Current Flow Rate
    // Low Water Level
    Display_Statue_Hydro_Reservoir = "Low";
  }
  else if (Hydro_Reservoir_Level > 500 && Hydro_Reservoir_Level < 800)
  {
    // Maintain Current Flow Rate
    // Normal Mode
    Display_Statue_Hydro_Reservoir = "Normal";
  }
  else if (Hydro_Reservoir_Level < 500)
  {
    // Decrease Current Flow Rate
    // Draining Mode
    Display_Statue_Hydro_Reservoir = "High";
  }

  //Determine height of water column
  if (Soil_Level > 800)
  {
    // Increase Current Flow Rate
    // Low Water Level
    Display_Statue_Soil = "Low";
  }
  else if (Soil_Level > 500 && Soil_Level < 800)
  {
    // Maintain Current Flow Rate
    // Normal Mode
    Display_Statue_Soil = "Normal";
  }
  else if (Soil_Level < 500)
  {
    // Decrease Current Flow Rate
    // Draining Mode
    Display_Statue_Soil = "High";
  }

}


void Water_Pump_Control()
{
  // Calculate the analog equivalent of the "water_pump_speed_percentage" value for each unit
  water_pump_speed_1 = Water_Pump_Speed_Percentage_1;
  water_pump_speed_1 = ((water_pump_speed_1 - 0) * (255 - 160));
  water_pump_speed_1 = ((water_pump_speed_1) / (100 - 0));
  water_pump_speed_1 = (water_pump_speed_1 + 160);

  water_pump_speed_2 = Water_Pump_Speed_Percentage_2;
  water_pump_speed_2 = ((water_pump_speed_2 - 0) * (255 - 160));
  water_pump_speed_2 = ((water_pump_speed_2) / (100 - 0));
  water_pump_speed_2 = (water_pump_speed_2 + 160);

  water_pump_speed_3 = Water_Pump_Speed_Percentage_3;
  water_pump_speed_3 = ((water_pump_speed_3 - 0) * (255 - 160));
  water_pump_speed_3 = ((water_pump_speed_3) / (100 - 0));
  water_pump_speed_3 = (water_pump_speed_3 + 160);

  water_pump_speed_4 = Water_Pump_Speed_Percentage_4;
  water_pump_speed_4 = ((water_pump_speed_4 - 0) * (255 - 160));
  water_pump_speed_4 = ((water_pump_speed_4) / (100 - 0));
  water_pump_speed_4 = (water_pump_speed_4 + 160);

  water_pump_speed_5 = Water_Pump_Speed_Percentage_5;
  water_pump_speed_5 = ((water_pump_speed_5 - 0) * (255 - 160));
  water_pump_speed_5 = ((water_pump_speed_5) / (100 - 0));
  water_pump_speed_5 = (water_pump_speed_5 + 160);

  if (Manual == false)
  {
    if (Display_Statue_Fish == "Normal")
    {
      Water_Pump_Speed_Percentage_1 = 50;
      Water_Pump_Speed_Percentage_3 = 50;
    }
    else if (Display_Statue_Fish == "High")
    {
      Water_Pump_Speed_Percentage_1 = 100;
      Water_Pump_Speed_Percentage_3 = 50;
    }

    if (Display_Statue_Soil_Reservoir == "Normal")
    {
      Water_Pump_Speed_Percentage_1 = 50;
      Water_Pump_Speed_Percentage_2 = 50;
    }
    else if (Display_Statue_Soil_Reservoir == "High")
    {
      Water_Pump_Speed_Percentage_1 = 50;
      Water_Pump_Speed_Percentage_2 = 100;
    }
    
    if (Display_Statue_Hydro_Reservoir == "Normal")
    {
      Water_Pump_Speed_Percentage_2 = 50;
      Water_Pump_Speed_Percentage_3 = 50;
    }
    else if (Display_Statue_Hydro_Reservoir == "High")
    {
      Water_Pump_Speed_Percentage_2 = 50;
      Water_Pump_Speed_Percentage_3 = 100;
    }
    
    
    
    if (Display_Statue_Fish == "Low")
    {
      Water_Pump_Speed_Percentage_1 = 0;
    }
    
    if (Display_Statue_Soil_Reservoir == "Low")
    {
      Water_Pump_Speed_Percentage_2 = 0;
    }
    
    if (Display_Statue_Hydro_Reservoir == "Low")
    {
      Water_Pump_Speed_Percentage_3 = 0;
    }

  }
  //If Water Pump Speed if set to 0, and make analog output 0
  if (Water_Pump_Speed_Percentage_1 == 0)
  {
    water_pump_speed_1 = 0;
  }
  else if (Water_Pump_Speed_Percentage_1 == 100)
  {
    water_pump_speed_1 = 255;
  }

  if (Water_Pump_Speed_Percentage_2 == 0)
  {
    water_pump_speed_2 = 0;
  }
  else if (Water_Pump_Speed_Percentage_2 == 100)
  {
    water_pump_speed_2 = 255;
  }

  if (Water_Pump_Speed_Percentage_3 == 0)
  {
    water_pump_speed_3 = 0;
  }
  else if (Water_Pump_Speed_Percentage_3 == 100)
  {
    water_pump_speed_3 = 255;
  }

  if (Water_Pump_Speed_Percentage_4 == 0)
  {
    water_pump_speed_4 = 0;
  }
  else if (Water_Pump_Speed_Percentage_4 == 100)
  {
    water_pump_speed_4 = 255;
  }

  if (Water_Pump_Speed_Percentage_5 == 0)
  {
    water_pump_speed_5 = 0;
  }
  else if (Water_Pump_Speed_Percentage_5 == 100)
  {
    water_pump_speed_5 = 255;
  }

  // Set Water Pump Speed
  analogWrite(waterpump_1, water_pump_speed_1);
  analogWrite(waterpump_2, water_pump_speed_2);
  analogWrite(waterpump_3, water_pump_speed_3);
  analogWrite(waterpump_4, water_pump_speed_4);
  analogWrite(waterpump_5, water_pump_speed_5);
}

void Flooding_Mode()
{
  if (Manual == false)
  {
  
    Flooding_Frequency_Read = ((Flooding_Frequency * 60) * 1000); // Minutes
    Flooding_Duration_Read = ((Flooding_Duration * 60) * 1000); // Minutes
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Frequency of the flood (time between floods)
  
    // Begin timer to count the Frequency of the flood (time between floods)
    if (Set_Timer_1 == false)
    {
      Past_Time_1 = millis();
      Set_Timer_1 = true;
    }
  
    Current_Time_1 = millis(); // Get Current Time
  
    Timer_1 = Current_Time_1 - Past_Time_1;  // Determine the amount of milliseconds that have past
  
    /*
      If the timer is equal to or greater then the "Flooding_Frequency",
      then reset the timer and move to flooding mode
    */
  
    if (Timer_1 >= Flooding_Frequency_Read)
    {
      Set_Mode = 3; //Flooding Set
      Set_Timer_1 = false;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Duration of the flood (time in flood mode)
  
    // Begin timer to count the Duration of the flood (time in flood mode)
    if (Set_Timer_2 == false)
    {
      Past_Time_2 = millis();
      Set_Timer_2 = true;
    }
  
    Current_Time_2 = millis(); // Get Current Time
  
    Timer_2 = Current_Time_2 - Past_Time_2;  // Determine the amount of milliseconds that have past
  
    /*
      If the timer is equal to or greater then the "Flooding_Duration",
      then reset the timer and move to draining mode
    */
  
    if (Timer_2 > Flooding_Duration_Read)
    {
      Set_Mode = 2; //Normal Set
      Set_Timer_2 = false;
      
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Set Water Pump 5 Speed
    if (Display_Statue_Hydro == "High" || Display_Statue_Hydro == "Normal")
    {
      if (Set_Mode == 3)
      {
        Water_Pump_Speed_Percentage_5 = 100;
      }
      else
      {
        Water_Pump_Speed_Percentage_5 = 0;
      }
    }
  }
}

void Display_Water_Data()
{

  Serial.print("\n");
  Serial.print("***************************************");
  Serial.print("Current Water Level");
  Serial.print("\n");
  Serial.print("\n");
  Serial.println("Fish Tank: " + Display_Statue_Fish + " (" + Fish_Level + ")");
  Serial.println("Soil Unit: " + Display_Statue_Soil + " (" + Soil_Level + ")");
  Serial.println("Hydroponic Unit: " + Display_Statue_Hydro + " (" + Hydro_Level + ")");
  Serial.println("Soil Reservoir: " + Display_Statue_Soil_Reservoir + " (" + Soil_Reservoir_Level + ")");
  Serial.println("Hydroponic Reservoir: " + Display_Statue_Hydro_Reservoir + " (" + Hydro_Reservoir_Level + ")");
  Serial.println("Elapsed Duration Time: " + String(Timer_2) + " of " + String(Flooding_Duration_Read));
  Serial.println("Elapsed Frequency Time: " + String(Timer_1) + " of " + String(Flooding_Frequency_Read));

  Serial.print("***************************************");
  Serial.print("Set Point Hydroponic Unit ");

  Serial.print("\n");
  Serial.print("\n");
  if (Set_Mode == 3)
  {
    Serial.println("Flooding");
  }
  else if (Set_Mode == 2)
  {
    Serial.println("Normal");
  }
  else if (Set_Mode == 1)
  {
    Serial.println("Draining");
  }

  Serial.print("***************************************");
  Serial.print("Current Water Pump Speed");
  Serial.print("\n");
  Serial.print("\n");
  Serial.println("Water Pump 1: " + String(Water_Pump_Speed_Percentage_1) + "%" + " (Fish To Soil)");
  Serial.println("Water Pump 2: " + String(Water_Pump_Speed_Percentage_2) + "%" + " (Soil Reservoir  To Hydro)");
  Serial.println("Water Pump 3: " + String(Water_Pump_Speed_Percentage_3) + "%" + " (Hydro Reservoir To Fish)");
  Serial.println("Water Pump 4: " + String(Water_Pump_Speed_Percentage_4) + "%" + " (Soil Reservoir To Soil)");
  Serial.println("Water Pump 5: " + String(Water_Pump_Speed_Percentage_5) + "%" + " (Hydro Reservoir To Hydro)");
}

void Water_Level_Alerts()
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (Display_Statue_Fish == "Low" || Display_Statue_Fish == "High")
  {
    if (Set_Timer_4 == false)
    {
      Past_Time_4 = millis();
      Set_Timer_4 = true;
    }
  }

  if (Display_Statue_Fish == "Normal")
  {
    Past_Time_4 = millis();
    Set_Timer_4 = false;
  }

  Current_Time_4 = millis(); // Get Current Time

  Over_Under_Timer = Current_Time_4 - Past_Time_4;  // Determine the amount of milliseconds that have past

  if (Over_Under_Timer > 18000)
  {
    if (Display_Statue_Fish == "Low")
    {
      Error_Message = Error_Message + "\n" + "Fish Unit Water Level Low";
    }
    else if (Display_Statue_Fish == "High")
    {
      Error_Message = Error_Message + "\n" + "Fish Unit Water Level High";
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (Display_Statue_Hydro == "Low" || Display_Statue_Hydro == "High")
  {
    if (Set_Timer_5 == false)
    {
      Past_Time_5 = millis();
      Set_Timer_5 = true;
    }
  }

  if (Display_Statue_Hydro == "Normal")
  {
    Past_Time_5 = millis();
    Set_Timer_5 = false;
  }

  Current_Time_5 = millis(); // Get Current Time

  Over_Under_Timer_2 = Current_Time_5 - Past_Time_5;  // Determine the amount of milliseconds that have past

  if (Over_Under_Timer_2 > 18000)
  {
    if (Display_Statue_Hydro == "Low")
    {
      Error_Message = Error_Message + "\n" + "Hydro Unit Water Level Low";
    }
    else if (Display_Statue_Hydro == "High")
    {
      Error_Message = Error_Message + "\n" + "Hydro Unit Water Level High";
    }
  }
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (Display_Statue_Soil_Reservoir == "Low" || Display_Statue_Soil_Reservoir == "High")
  {
    if (Set_Timer_6 == false)
    {
      Past_Time_6 = millis();
      Set_Timer_6 = true;
    }
  }

  if (Display_Statue_Soil_Reservoir == "Normal")
  {
    Past_Time_6 = millis();
    Set_Timer_6 = false;
  }

  Current_Time_6 = millis(); // Get Current Time

  Over_Under_Timer_3 = Current_Time_6 - Past_Time_6;  // Determine the amount of milliseconds that have past

  if (Over_Under_Timer_3 > 18000)
  {
    if (Display_Statue_Soil_Reservoir == "Low")
    {
      Error_Message = Error_Message + "\n" + "Soil Reservoir Water Level Low";
    }
    else if (Display_Statue_Soil_Reservoir == "High")
    {
      Error_Message = Error_Message + "\n" + "Soil Reservoir Water Level High";
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (Display_Statue_Hydro_Reservoir == "Low" || Display_Statue_Hydro_Reservoir == "High")
  {
    if (Set_Timer_7 == false)
    {
      Past_Time_7 = millis();
      Set_Timer_7 = true;
    }
  }

  if (Display_Statue_Hydro_Reservoir == "Normal")
  {
    Past_Time_7 = millis();
    Set_Timer_7 = false;
  }

  Current_Time_7 = millis(); // Get Current Time

  Over_Under_Timer_4 = Current_Time_7 - Past_Time_7;  // Determine the amount of milliseconds that have past

  if (Over_Under_Timer_4 > 18000)
  {
    if (Display_Statue_Hydro_Reservoir == "Low")
    {
      Error_Message = Error_Message + "\n" + "Hydro Reservoir Water Level Low";
    }
    else if (Display_Statue_Hydro_Reservoir == "High")
    {
      Error_Message = Error_Message + "\n" + "Hydro Reservoir Water Level High";
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (Display_Statue_Soil == "Low" || Display_Statue_Soil == "High")
  {
    if (Set_Timer_8 == false)
    {
      Past_Time_8 = millis();
      Set_Timer_8 = true;
    }
  }

  if (Display_Statue_Soil == "Normal")
  {
    Past_Time_8 = millis();
    Set_Timer_8 = false;
  }

  Current_Time_8 = millis(); // Get Current Time

  Over_Under_Timer_5 = Current_Time_8 - Past_Time_8;  // Determine the amount of milliseconds that have past

  if (Over_Under_Timer_5 > 18000)
  {
    if (Display_Statue_Soil == "Low")
    {
      Error_Message = Error_Message + "\n" + "Soil Unit Water Level Low";
    }
    else if (Display_Statue_Soil == "High")
    {
      Error_Message = Error_Message + "\n" + "Soil Unit Water Level High";
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}