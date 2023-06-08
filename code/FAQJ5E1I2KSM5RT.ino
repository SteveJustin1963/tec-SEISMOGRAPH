//Based on the IoTKitSimpleExample code. This example collects anolog output from a seismometer
//sends the observed data to the Intel IoTkit Cloud

#include <IoTkit.h>    // include IoTkit.h to use the Intel IoT Kit
#include <Ethernet.h>  // must be included to use IoTkit
#include <aJSON.h>

// create an object of the IoTkit class
IoTkit iotkit; 

//Analog input pin for seismometer. The name of this variable must be exactly the same 
//as the sensor name in your IoT Analytics Dashboard. 
int seismoPin=A0;

void setup() {
  Serial.begin(115200);
  // call begin on the IoTkit object before calling any other methods
  iotkit.begin();
}

void loop() {
  seismograph= analogRead(seismoPin);
  iotkit.send(seismograph); 
  Serial.println("Temperature is ");
  Serial.print(temp);

  //send data to cloud every 1/2 hour
  delay(1800000);
}


void callback(char* json) {
  Serial.println(json);
  aJsonObject* parsed = aJson.parse(json);
  if (&parsed == NULL) {
    // invalid or empty JSON
    Serial.println("recieved invalid JSON");
    return;
  }
  aJsonObject* component = aJson.getObjectItem(parsed, "component");
  aJsonObject* command = aJson.getObjectItem(parsed, "command");
  if ((component != NULL)) {
    if (strcmp(component->valuestring, "led") == 0) {
      if ((command != NULL)) {
        if (strcmp(command->valuestring, "off") == 0) {
          pinMode(13, OUTPUT);
          digitalWrite(13, false);
        }
        if (strcmp(command->valuestring, "on") == 0) {
          pinMode(13, OUTPUT);
          digitalWrite(13, true);
        }
      }
    }
  }
}

