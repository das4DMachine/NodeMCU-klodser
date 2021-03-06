#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//WiFi informationer
const char* ssid     = "Mark's iPhone";
const char* password = "LOLl0l69";

String ID = "4"; //SHould be assigned by reader initialisation can be preserved here
boolean stacked = false;


void setup() {
  Serial.begin(115200);
  delay(10);
  wifiConnect();
      
}


void loop() {
  wifiCheck(); //Maintain wifi connection
  yield(); //Let the ESPcore handle background tasks

  if(stacked == false) {

    stacked = true;
    //post("klods_id=" + ID + "&stacked_rfid=" + "25", "/3dserver/arduino/stack");
    post("klods_id=" + ID, "/3dserver/arduino/unstack");
    

    
  }


  
  
}

void wifiConnect() {
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void wifiCheck()
{
  if (WiFi.status() != WL_CONNECTED) //if wifi is connected: do nothing.
  {
    int tickCount = 0;
    Serial.println("Wifi dropped. Retry in 60 seconds.");
    delay(60000); //wait 60 seconds
    Serial.println("Connecting");
    WiFi.begin(ssid, password); //reconnect

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println(".");
      tickCount++;
      if (tickCount > 100) //after awaiting reconnection for 50 seconds
      {
        Serial.println("Wifi fail...");
        //This is where you end up if the connection was lost and unrecoverable
        while (1); //Endless loop...
      }
    }

    //This is the place to do something in case the connection was lost but fixed.

  }
}



void post(String payload, String url) {
  
        HTTPClient http;

        Serial.println("[HTTP] begin...");
        // configure traged server and url
        //http.begin("192.168.1.12", 443, "/test.html", true, "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin("graungaard.com", 80, url); //HTTP


        int response = http.POST(payload);

        Serial.println(response);
        
        
  
}


