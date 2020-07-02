#include "MQTTmy.h"

IPAddress ip (109, 121, 141, 188);
WiFiClient espClient;
PubSubClient mqttClient(espClient);
static MQTTmy * instance;
void MQTTmy::init(Externalmy external) {
  ext = external;
   mqttClient.setServer(ip, 1884);
  instance = this;

  if (mqttClient.connect("SmartSocketID"))
  {
    Serial.println("Success");
     mqttClient.setCallback(callback);
  }
  else
  {
    Serial.println("Fail");
  }
 }

int wifiConnected = 1;
unsigned int previousWifiTime = 0;
int cmd;


void MQTTmy::cmdt() {
 
    if (mqttClient.subscribe("/smartsocket1/ctrl")) {
      Serial.println("Subscribed");
    }
    else {
      Serial.println("Not subscribed");
    }
    switch (cmd) {
      case 'N': {
          ext.power(1);
          break;
        }
      case 'F': {
          ext.power(0);
          break;
        }
      default: {
        //TO DO Message
          break;
        }
        }


  

}


static void callback (char* topic, unsigned char* payload, unsigned int lenght) {
  Serial.print("Command: ");
  for (int i = 0; i < lenght; i++)
  {
    cmd = char(payload[i]);
  }
 
  Serial.println("");

}
