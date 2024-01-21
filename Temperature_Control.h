#include <DFRobot_SHT3x.h>
#include <Arduino_PortentaBreakout.h>

const unsigned char Soil_Unit_Heater_Pin = 0; //Digital Pin
const unsigned char Hydro_Unit_Heater_Pin = GPIO_6; //Digital Pin
const unsigned char Soil_Unit_Fan_Pin = GPIO_0; //Digital Pin
const unsigned char Hydro_Unit_Fan_Pin = GPIO_1; //Digital Pin

const unsigned char Temperture_Humidity_Sensor_Soil = GPIO_2; // Reset Pin for Temperture & Humidity Sensor inside the Soil Unit
const unsigned char Temperture_Humidity_Sensor_Hydro = GPIO_3; // Reset Pin for Temperture & Humidity Sensor inside the Hydroponic Unit Tank
const unsigned char Temperture_Humidity_Sensor_Tank = 0; // Reset Pin for Temperture & Humidity Sensor inside the Fish Tank

float past_humidity = 0.00, current_humidity = 0.00;

bool fish_Tank_Temp_Hum = false;
bool hydro_Unit_Temp_Hum = false;
bool soil_Unit_Temp_Hum = false;

int current_time = 0, past_time = 0, Seconds = 0;
int serialnumber = 0;


bool SetTime = false;

DFRobot_SHT3x   Temperture_Humidity_Sensor;

void Setup_Temperature_Humidity_Sensors()
{
  pinMode(Temperture_Humidity_Sensor_Soil, OUTPUT); //Reset Pin for Temperture & Humidity Sensor inside the Soil Unit
  pinMode(Temperture_Humidity_Sensor_Hydro, OUTPUT); //Reset Pin for Temperture & Humidity Sensor inside the Hydroponic Unit Tank
  pinMode(Temperture_Humidity_Sensor_Tank, OUTPUT); //Reset Pin for Temperture & Humidity Sensor inside the Fish Tank

  if (Temperture_Humidity_Sensor.begin() != 0)
  {
    Serial.println("Failed to Initialize the chip, please confirm the wire connection");
    delay(1000);
  }

  if (!Temperture_Humidity_Sensor.softReset())
  {
    Serial.println("Failed to Initialize the chip....");
  }
}

void Read_Temperature_Humidity_Data() 
{
  
  if (SetTime == false)
  {
    past_time = millis();
    SetTime = true;
  }
  
  current_time = millis();

  Seconds = current_time - past_time;
  
  if (Seconds >= 15000)
  {
    fish_Tank_Temp_Hum = false;
    hydro_Unit_Temp_Hum = false;
    soil_Unit_Temp_Hum = true;
    SetTime = false;
  }
  else if (Seconds >= 10000)
  {
    fish_Tank_Temp_Hum = false;
    hydro_Unit_Temp_Hum = true;
    soil_Unit_Temp_Hum = false;
  }
  
  else if (Seconds >= 5000)
  {
    fish_Tank_Temp_Hum = true;
    hydro_Unit_Temp_Hum = false;
    soil_Unit_Temp_Hum = false;
  }
  
  serialnumber = Temperture_Humidity_Sensor.readSerialNumber();
  
    if (fish_Tank_Temp_Hum == true)
  {
    digitalWrite(Temperture_Humidity_Sensor_Tank, HIGH);
    
    if (serialnumber = 0)
    {
      Fish_Temperature_Sensor_1_C = Temperture_Humidity_Sensor.getTemperatureC();
      Fish_Temperature_Sensor_1_H = Temperture_Humidity_Sensor.getHumidityRH();
    }
  }
  else if (fish_Tank_Temp_Hum == false)
  {
    digitalWrite(Temperture_Humidity_Sensor_Tank, LOW);
  }
  
    
    if (hydro_Unit_Temp_Hum == true)
  {
    digitalWrite(Temperture_Humidity_Sensor_Hydro, HIGH);
    
    if (serialnumber = 238816016)
    {
      Hydro_Temperature_Sensor_1_C = Temperture_Humidity_Sensor.getTemperatureC();
      Hydro_Temperature_Sensor_1_H = Temperture_Humidity_Sensor.getHumidityRH();
    }
    
  }
  else if (hydro_Unit_Temp_Hum == false)
  {
    digitalWrite(Temperture_Humidity_Sensor_Hydro, LOW);
  }
  
    if (soil_Unit_Temp_Hum == true)
  {
    digitalWrite(Temperture_Humidity_Sensor_Soil, HIGH);
    
    if (serialnumber = 238814366)
    {
      Soil_Temperature_Sensor_1_C = Temperture_Humidity_Sensor.getTemperatureC();
      Soil_Temperature_Sensor_1_H = Temperture_Humidity_Sensor.getHumidityRH();
    }
    
  }
  else if (soil_Unit_Temp_Hum == false)
  {
    digitalWrite(Temperture_Humidity_Sensor_Soil, LOW);
  }
  

}

void Temperature_Alerts()
{
  
  Alert_Fish_Statue = true;
  Alert_Soil_Statue = true;
  Alert_Hydro_Statue = true;
  
//****************************************************** Alert Fish Tank Temperature **********************************************************************************  
  if (Fish_Temperature_Sensor_1_C > (Fish_Temperature_Set_Point + Fish_Temperature_Variance))
  {
    Alert_Fish_Statue = false;
    Error_Message = Error_Message + "\n" + "Fish Unit Temperature too High";
  }
  else if (Fish_Temperature_Sensor_1_C < (Fish_Temperature_Set_Point - Fish_Temperature_Variance))
  {
    Alert_Fish_Statue = false;
    Error_Message = Error_Message + "\n" + "Fish Unit Temperature too Low";
  }
  
//****************************************************** Alert Hydro Tank Temperature **********************************************************************************  
  if (Hydro_Temperature_Sensor_1_C > (Hydro_Temperature_Set_Point + Hydro_Temperature_Variance))
  {
    Alert_Hydro_Statue = false;
    Error_Message = Error_Message + "\n" + "Hydro Unit Temperature too High";
  }
  else if (Hydro_Temperature_Sensor_1_C < (Hydro_Temperature_Set_Point - Hydro_Temperature_Variance))
  {
    Alert_Hydro_Statue = false;
    Error_Message = Error_Message + "\n" + "Hydro Unit Temperature too Low";
  }
  
//****************************************************** Alert Soil Tank Temperature **********************************************************************************  
  if (Soil_Temperature_Sensor_1_C > (Soil_Temperature_Set_Point + Soil_Temperature_Variance))
  {
    Alert_Soil_Statue = false;
    Error_Message = Error_Message + "\n" + "Soil Unit Temperature too High";
  }
  else if (Soil_Temperature_Sensor_1_C < (Soil_Temperature_Set_Point - Soil_Temperature_Variance))
  {
    Alert_Soil_Statue = false;
    Error_Message = Error_Message + "\n" + "Soil Unit Temperature too Low";
  }
  
}

void Humidity_Alerts()
{
  Alert_Fish_Statue = true;
  Alert_Soil_Statue = true;
  Alert_Hydro_Statue = true;

//****************************************************** Alert Fish Tank Humidity ************************************************************************************  
  if (Fish_Temperature_Sensor_1_H > (Fish_Humidity_Set_Point + Fish_Humidity_Variance))
  {
    Alert_Fish_Statue = false;
    Error_Message = Error_Message + "\n" + "Fish Unit Humidity too High";
  }
  else if (Fish_Temperature_Sensor_1_H < (Fish_Humidity_Set_Point - Fish_Humidity_Variance))
  {
    Alert_Fish_Statue = false;
    Error_Message = Error_Message + "\n" + "Fish Unit Humidity too Low";
  }
  
//****************************************************** Alert Hydro Tank Humidity ************************************************************************************  
  if (Hydro_Temperature_Sensor_1_H > (Hydro_Humidity_Set_Point + Hydro_Humidity_Variance))
  {
    Alert_Hydro_Statue = false;
    Error_Message = Error_Message + "\n" + "Hydroponic Unit Humidity too High";
  }
  else if (Hydro_Temperature_Sensor_1_H < (Hydro_Humidity_Set_Point - Hydro_Humidity_Variance))
  {
    Alert_Hydro_Statue = false;
    Error_Message = Error_Message + "\n" + "Hydroponic Unit Humidity too Low";
  }
  
//****************************************************** Alert Soil Tank Humidity ************************************************************************************  
  if (Soil_Temperature_Sensor_1_H > (Soil_Humidity_Set_Point + Soil_Humidity_Variance))
  {
    Alert_Soil_Statue = false;
    Error_Message = Error_Message + "\n" + "Soil Unit Humidity too High";
  }
  else if (Soil_Temperature_Sensor_1_H < (Soil_Humidity_Set_Point - Soil_Humidity_Variance))
  {
    Alert_Soil_Statue = false;
    Error_Message = Error_Message + "\n" + "Soil Unit Humidity too Low";
  }
  
}

void Soil_Heater_Fan_Controls()
{
  digitalWrite(Soil_Unit_Heater_Pin, LOW);
  digitalWrite(Soil_Unit_Fan_Pin, LOW);
  
  if (Manual == false)
  {
    if (Soil_Temperature_Sensor_1_H < Soil_Humidity_Set_Point)
    {
      Soil_Unit_Fan = false;
      digitalWrite(Soil_Unit_Fan_Pin, LOW);
    }
    else if (Soil_Temperature_Sensor_1_H > Soil_Humidity_Set_Point)
    {
      Soil_Unit_Heater = false;
      Soil_Unit_Fan = true;
      digitalWrite(Soil_Unit_Heater_Pin, LOW);
      digitalWrite(Soil_Unit_Fan_Pin, HIGH);
    }
    
    if (Soil_Temperature_Sensor_1_C < Soil_Temperature_Set_Point)
    {
      Soil_Unit_Heater = true;
      Soil_Unit_Fan = true;
      digitalWrite(Soil_Unit_Heater_Pin, HIGH);
      digitalWrite(Soil_Unit_Fan_Pin, HIGH);
    }
    else if (Soil_Temperature_Sensor_1_C > Soil_Temperature_Set_Point)
    {
      Soil_Unit_Heater = false;
      Soil_Unit_Fan = true;
      digitalWrite(Soil_Unit_Heater_Pin, LOW);
      digitalWrite(Soil_Unit_Fan_Pin, HIGH);
    }
  }
  
  if (Soil_Unit_Heater == true)
  {
  digitalWrite(Soil_Unit_Heater_Pin, HIGH);
  }
  else if (Soil_Unit_Heater == false)
  {
  digitalWrite(Soil_Unit_Heater_Pin, LOW);
  }
  
  if (Soil_Unit_Fan == true)
  {
  digitalWrite(Soil_Unit_Fan_Pin, HIGH);
  }
  else if (Soil_Unit_Fan == false)
  {
  digitalWrite(Soil_Unit_Fan_Pin, LOW);
  }
  
}

void Hydro_Heater_Fan_Controls()
{
  digitalWrite(Hydro_Unit_Heater_Pin, LOW);
  digitalWrite(Hydro_Unit_Fan_Pin, LOW);
  
  if (Manual == false)
  {
    if (Hydro_Temperature_Sensor_1_H < Hydro_Humidity_Set_Point)
    {
      Hydro_Unit_Fan = false;
      digitalWrite(Hydro_Unit_Fan_Pin, LOW);
    }
    else if (Hydro_Temperature_Sensor_1_H > Hydro_Humidity_Set_Point)
    {
      Hydro_Unit_Heater = false;
      Hydro_Unit_Fan = true;
      digitalWrite(Hydro_Unit_Heater_Pin, LOW);
      digitalWrite(Hydro_Unit_Fan_Pin, HIGH);
    }
    
    if (Hydro_Temperature_Sensor_1_C < Hydro_Temperature_Set_Point)
    {
      Hydro_Unit_Heater = true;
      Hydro_Unit_Fan = true;
      digitalWrite(Hydro_Unit_Heater_Pin, HIGH);
      digitalWrite(Hydro_Unit_Fan_Pin, HIGH);
    }
    else if (Hydro_Temperature_Sensor_1_C > Hydro_Temperature_Set_Point)
    {
      Hydro_Unit_Heater = false;
      Hydro_Unit_Fan = true;
      digitalWrite(Hydro_Unit_Heater_Pin, LOW);
      digitalWrite(Hydro_Unit_Fan_Pin, HIGH);
    }
  }
  
  if (Hydro_Unit_Heater == true)
  {
  digitalWrite(Hydro_Unit_Heater_Pin, HIGH);
  }
  else if (Hydro_Unit_Heater == false)
  {
  digitalWrite(Hydro_Unit_Heater_Pin, LOW);
  }
  
  if (Hydro_Unit_Fan == true)
  {
  digitalWrite(Hydro_Unit_Fan_Pin, HIGH);
  }
  else if (Hydro_Unit_Fan == false)
  {
  digitalWrite(Hydro_Unit_Fan_Pin, LOW);
  }
}


void Display_Temperature_Humidity_Data()
{
//************************************************************************************* Current Environment **********************************************************
  Serial.print("***************************************");
  Serial.print("Soil Unit: Current Environment");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Temperature C:  ");
  Serial.print(Soil_Temperature_Sensor_1_C);
  Serial.print("\n");
  Serial.print("Humidity %:  ");
  Serial.print(Soil_Temperature_Sensor_1_H);
  Serial.print("\n");
  Serial.print("Serial Number:  ");
  Serial.print(serialnumber);
  Serial.print("\n");
  Serial.print("Fish:  ");
  Serial.print(fish_Tank_Temp_Hum);
  Serial.print("\n");
  Serial.print("Hydro:  ");
  Serial.print(hydro_Unit_Temp_Hum);
  Serial.print("\n");
  Serial.print("Soil:  ");
  Serial.print(soil_Unit_Temp_Hum);
  Serial.print("\n");
  Serial.print("***************************************");
  Serial.print("Hydroponics Unit: Current Environment");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Temperature C:  ");
  Serial.print(Hydro_Temperature_Sensor_1_C);
  Serial.print("\n");
  Serial.print("Humidity %:  ");
  Serial.print(Hydro_Temperature_Sensor_1_H);
  Serial.print("\n");
  Serial.print("***************************************");
  Serial.print("Fish Tank: Current Environment");    
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Temperature C:  ");
  Serial.print(Fish_Temperature_Sensor_1_C);
  Serial.print("\n");
  Serial.print("Humidity %:  ");
  Serial.print(Fish_Temperature_Sensor_1_H);
  Serial.print("\n");

//************************************************************************************* Temperature Settings **********************************************************
  Serial.print("***************************************");  
  Serial.print("Soil Temperature Settings");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Set Point:  ");
  Serial.print(Soil_Temperature_Set_Point);
  Serial.print("\n");
  Serial.print("Variance:  ");
  Serial.print(Soil_Temperature_Variance);
  Serial.print("\n");
  Serial.print("Upper Range:  ");
  Serial.print(Soil_Temperature_Set_Point + Soil_Temperature_Variance);
  Serial.print("\n");
  Serial.print("Lower Range:  ");
  Serial.print(Soil_Temperature_Set_Point - Soil_Temperature_Variance);
  Serial.print("\n");

  Serial.print("***************************************"); 
  Serial.print("Hydroponics Temperature Settings");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Set Point:  ");
  Serial.print(Hydro_Temperature_Set_Point);
  Serial.print("\n");
  Serial.print("Variance:  ");
  Serial.print(Hydro_Temperature_Variance);
  Serial.print("\n");
  Serial.print("Upper Range:  ");
  Serial.print(Hydro_Temperature_Set_Point + Hydro_Temperature_Variance);
  Serial.print("\n");
  Serial.print("Lower Range:  ");
  Serial.print(Hydro_Temperature_Set_Point - Hydro_Temperature_Variance);
  Serial.print("\n");

//************************************************************************************* Humidity Settings **********************************************************
  Serial.print("***************************************");   
  Serial.print("Soil Humidity Settings");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Set Point:  ");
  Serial.print(Soil_Humidity_Set_Point);
  Serial.print("\n");
  Serial.print("Variance:  ");
  Serial.print(Soil_Humidity_Variance);
  Serial.print("\n");
  Serial.print("Upper Range:  ");
  Serial.print(Soil_Humidity_Set_Point + Soil_Humidity_Variance);
  Serial.print("\n");
  Serial.print("Lower Range:  ");
  Serial.print(Soil_Humidity_Set_Point - Soil_Humidity_Variance);
  Serial.print("\n");

  Serial.print("***************************************"); 
  Serial.print("Hydroponics Humidity Settings");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Set Point:  ");
  Serial.print(Hydro_Humidity_Set_Point);
  Serial.print("\n");
  Serial.print("Variance:  ");
  Serial.print(Hydro_Humidity_Variance);
  Serial.print("\n");
  Serial.print("Upper Range:  ");
  Serial.print(Hydro_Humidity_Set_Point + Hydro_Humidity_Variance);
  Serial.print("\n");
  Serial.print("Lower Range:  ");
  Serial.print(Hydro_Humidity_Set_Point - Hydro_Humidity_Variance);
  Serial.print("\n");
  
  Serial.print("***************************************"); 
  Serial.print("Heater & Fan Statue");
  Serial.print("\n");
  Serial.print("\n");
//************************************************************************************* Soil Heater **********************************************************
  Serial.print("Soil Unit Heater:  ");
  if (Soil_Unit_Heater == true)
  {
    Serial.print("ON");
  }
  else if (Soil_Unit_Heater == false)
  {
    Serial.print("OFF");
  }
//************************************************************************************* Soil Fan **********************************************************
  Serial.print("\n");
  Serial.print("Soil Unit Fan:  ");
  if (Soil_Unit_Fan == true)
  {
    Serial.print("ON");
  }
  else if (Soil_Unit_Fan == false)
  {
    Serial.print("OFF");
  }
//************************************************************************************* Hydro Heater **********************************************************
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Hydro Unit Heater:  ");
  if (Hydro_Unit_Heater == true)
  {
    Serial.print("ON");
  }
  else if (Hydro_Unit_Heater == false)
  {
    Serial.print("OFF");
  }
//************************************************************************************* Hydro Fan **********************************************************
    Serial.print("\n");
    Serial.print("Soil Unit Fan:  ");
  if (Hydro_Unit_Fan == true)
  {
    Serial.print("ON");
  }
  else if (Hydro_Unit_Fan == false)
  {
    Serial.print("OFF");
  }
}











