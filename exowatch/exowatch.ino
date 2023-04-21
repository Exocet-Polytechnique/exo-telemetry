/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/fd930658-1c11-4738-aaab-931075b70aa0 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  - No variables have been created, add cloud variables on the Thing Setup page
    to see them declared here

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <ArduinoJson.h>

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  // initProperties();

  // Connect to Arduino IoT Cloud
  //ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  //ArduinoCloud.printDebugInfo();
}

String readSerial() {
  /*
  Read serial line until stop char is met
  */
  char lastChar;
  String serialData = "";
  while(Serial.available() && lastChar != '!'){ // ! is a special character for EOL
    delay(3);
    if (Serial.available() > 0) {
      lastChar = Serial.read();
      serialData += lastChar;
    }
  }
  return serialData;
}


void updateVariables(String serialData) {
  int separator_index = serialData.indexOf(' ');
  String name = serialData.substring(0, separator_index);
  String jsonString = serialData.substring(separator_index);
  if (jsonString == "{}") {
    return;
  }

  StaticJsonDocument<512> doc;
  deserializeJson(doc, jsonString);
  Serial.println(name);
  if (name == "GPS") {
    const char* world = doc["nmea_time"];
    Serial.println(world);

  } else if (name == "FUELCELL_A") {

  } else if (name == "FUELCELL_B") {

  } else if (name == "IMU") {
    
  } else {
    
  }
}


void loop() {
 // ArduinoCloud.update();
  // Your code here 
  String serialData = readSerial();
  Serial.println(serialData);
  updateVariables(serialData);
  delay(1000);
  
}

