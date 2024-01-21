/*#include <Wire.h>

String Read_Arrary_Ref = "";
String Read_Arrary_Name = "";
String Read_Arrary_Data = "";
int counter = 0;
int Position_of_Equals = 0;
int String_Size = 0;

String Arrary_Pass[43] = {
"Display_Statue_Fish: " + String(Display_Statue_Fish),
"Display_Statue_Hydro: " + String(Display_Statue_Hydro),
"Display_Statue_Hydro_Reservoir: " + String(Display_Statue_Hydro_Reservoir),
"Display_Statue_Soil: " + String(Display_Statue_Soil),
"Display_Statue_Soil_Reservoir: " + String(Display_Statue_Soil_Reservoir),
"Fish_Temperature_Set_Point: " + String(Fish_Temperature_Set_Point),
"Fish_Humidity_Set_Point: " + String(Fish_Humidity_Set_Point),
"Hydro_Temperature_Set_Point: " + String(Hydro_Temperature_Set_Point),
"Hydro_Humidity_Set_Point: " + String(Hydro_Humidity_Set_Point),
"Soil_Temperature_Set_Point: " + String(Soil_Temperature_Set_Point),
"Soil_Humidity_Set_Point:" + String(Soil_Humidity_Set_Point),
"Fish_Temperature_Variance: " + String(Fish_Temperature_Variance),
"Fish_Humidity_Variance: " + String(Fish_Humidity_Variance),
"Hydro_Temperature_Variance: " + String(Hydro_Temperature_Variance),
"Hydro_Humidity_Variance: " + String(Hydro_Humidity_Variance),
"Soil_Temperature_Variance: " + String(Soil_Temperature_Variance),
"Soil_Humidity_Variance: " + String(Soil_Humidity_Variance),
"Water_Pump_Speed_Percentage_1: " + String(Water_Pump_Speed_Percentage_1),
"Water_Pump_Speed_Percentage_2: " + String(Water_Pump_Speed_Percentage_2),
"Water_Pump_Speed_Percentage_3: " + String(Water_Pump_Speed_Percentage_3),
"Water_Pump_Speed_Percentage_4: " + String(Water_Pump_Speed_Percentage_4),
"Water_Pump_Speed_Percentage_5: " + String(Water_Pump_Speed_Percentage_5),
"Alert_Fish_Statue: " + String(Alert_Fish_Statue),
"Alert_Hydro_Statue: " + String(Alert_Hydro_Statue),
"Alert_Soil_Statue: " + String(Alert_Soil_Statue),
"Light_Statue_Fish: " + String(Light_Statue_Fish),
"Light_Statue_Hydro: " + String(Light_Statue_Hydro),
"Light_Statue_Soil: " + String(Light_Statue_Soil),
"Hydro_Unit_Fan: " + String(Hydro_Unit_Fan),
"Soil_Unit_Fan: " + String(Soil_Unit_Fan),
"Hydro_Unit_Heater: " + String(Hydro_Unit_Heater),
"Soil_Unit_Heater: " + String(Soil_Unit_Heater),
"Manual: " + String(Manual),
"Set_Mode: " + String(Set_Mode),
"Flooding_Duration: " + String(Flooding_Duration),
"Flooding_Frequency: " + String(Flooding_Frequency),
"Full_Eastern_Date: " + String(Full_Eastern_Date),
"Full_Eastern_Time: " + String(Full_Eastern_Time),
"Fish_Level: " + String(Fish_Level),
"Hydro_Level: " + String(Hydro_Level),
"Hydro_Reservoir_Level: " + String(Hydro_Reservoir_Level),
"Soil_Level: " + String(Soil_Level),
"Soil_Reservoir_Level: " + String(Soil_Reservoir_Level),
 };

void Data_Reading()
{
  
  Wire.requestFrom(8,1);
  Wire.beginTransmission(8);
  
  for (counter; counter < 43; counter++)
  {
    Read_Arrary_Name = Arrary_Pass[counter];
    Read_Arrary_Data = Arrary_Pass[counter];
    Read_Arrary_Ref = Arrary_Pass[counter];

    Position_of_Equals = (Read_Arrary_Name.indexOf(":") + 1);
    String_Size = Read_Arrary_Name.length();

    Read_Arrary_Name.remove(Position_of_Equals - 1, String_Size);
    Read_Arrary_Data.remove(0, Position_of_Equals + 1);

    Serial.print("\n");
    Serial.print(Read_Arrary_Ref);
    Serial.print("\n");
    Serial.print(Read_Arrary_Name);
    Serial.print("\n");
    Serial.print(Read_Arrary_Data);

    delay(2000);
  }
  
}

void Transmit_Data()
{
double DirtMoisture = 100;
double DirtTank = 124;
double TempDirt = 29.1;


int Data[] = {DirtMoisture,DirtTank,TempDirt,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

  Wire.requestFrom(8,1);
  Wire.beginTransmission(8);
  for(int i=0; i<20; i++)
  {
  int MasterReceive = Wire.read();
  int MasterSend = Data[i];
  Wire.write(MasterSend);
  }
  Wire.endTransmission();
}


*/