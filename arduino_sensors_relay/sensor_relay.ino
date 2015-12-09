#include <OneWire.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(2);  // on pin 10 (a 4.7K resistor is necessary)

int RELAY1 = 4;                       
int RELAY2 = 7;
int RELAY3 = 8;
int RELAY4 = 12;

void setup(void) {
  //set Relays as Output
  pinMode(RELAY1, OUTPUT);    
  pinMode(RELAY2, OUTPUT);   
  pinMode(RELAY3, OUTPUT);   
  pinMode(RELAY4, OUTPUT);   
  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  
   digitalWrite(RELAY1,HIGH);  // Turns ON Led1
   delay(1000);                // Wait 1 seconds
   digitalWrite(RELAY2,HIGH);  // Turns ON Led2
   delay(1000);                // Wait 1 seconds
  if ( !ds.search(addr)) {
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  


  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      //Serial.println("Device is not a DS18x20 family device.");
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  //Serial.print("  Temperature = ");
  Serial.println(celsius);
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print(" {'temp': ");
  Serial.print(celsius);
  Serial.print(",'ph': ");
  Serial.print(mq4_value);
  Serial.print(",'density': ");
  Serial.print(sensorValue);
  Serial.print(",'oxygen': ");
  Serial.print(mq3_value);
  Serial.print(",'coo': ");
  Serial.print(mq7_value);
  Serial.print(",'ethanol': ");
  Serial.print(mq2_value);
  Serial.println("}");
  
}

