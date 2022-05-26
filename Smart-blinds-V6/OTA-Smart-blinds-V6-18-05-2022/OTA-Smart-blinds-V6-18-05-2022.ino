//Smart-blinds-V6-18-05-2022.
//OTA updates with Sinric pro.
//bug fixes: includes 10% - 90% position adjustments.
//Manual buttons for open and closeing the blinds.


#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#ifdef ESP8266 
       #include <ESP8266WiFi.h>
#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

#include <Arduino.h>
#include "SinricPro.h"
#include "SinricProBlinds.h"
#include <Servo.h>
//OTA Updates//
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <Button.h>


#define WIFI_SSID         "SSID"    
#define WIFI_PASS         "PASSWORD"
#define APP_KEY           "APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "674e36a9-d352-43a8-98b7-32b24e09fce9-531aa2bf-993f-477e-8d6f-5bc7ae7dba76"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define BLINDS_ID         "62813158a6872f3639285502" //Should look like "62813158a6872f3639285502, this is the test-blinds ID."
#define BAUD_RATE         9600                // Change baudrate to your need


int blindsPosition = 0;
bool powerState = false;
Servo myservo;
int pos = 0;
//OTA Updates//
AsyncWebServer server(80);

//Manual buttons//
Button buttonOpen(12); //ESP8266 pin D6
Button buttonClose(13); //ESP8266 pin D7

//Blinds paramiters//
int A = (140);
int B = (100);
int C = (10);
float updown = float(A) / float(B);
int base = (updown * C);

int updownRange = (100);  //button pin//


bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s power turned %s \r\n", deviceId.c_str(), state?"on":"off");
  powerState = state;
  Serial.println(powerState);
  if (powerState == 0)
  {
    Servo myservo;
    myservo.attach(15);
    int posInverted = (-40);
    for (pos = pos; pos >= posInverted; pos-=1){
    myservo.write(pos);
    Serial.print("blinds are Inverted: ");
    Serial.println(pos);
    delay(10);
    }
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    myservo.detach();
  }
  return true; // request handled properly
}


bool onRangeValue(const String &deviceId, int &position) {
  Serial.printf("Device %s set position to %d\r\n", deviceId.c_str(), position);
  int updownpos = (updown * position);
 
   if (position == 100) // Device ID of first device
  { 
    Servo myservo;
    myservo.attach(15);
    int pos100 = (base * 0);
    for (pos = pos; pos >= pos100; pos-=1){
    myservo.write(pos);
    Serial.print("blinds are max open: ");
    Serial.println(pos);
    delay(10);
    }
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    myservo.detach();
  }
  
  else if (position == 0) // Device ID of first device
   {  
    myservo.attach(15);
    int pos0 = (base * 10);
    for (pos = pos; pos <= pos0; pos+=1) {
    myservo.write(pos);
    Serial.print("blinds are max closed: ");
    Serial.println(pos);
    delay(10);
    }
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    myservo.detach();
   }

//Tilt position adjustments//
   if (position == 10 && pos >= 126) // Device ID of first device
   {  
    myservo.attach(15);
    int pos10 = (base * 9);
    for (pos = pos; pos >= pos10; pos -=1){
      myservo.write(pos);
      Serial.print("blinds are moving to pos: ");
      Serial.println(pos);
      delay(10);
      }
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    myservo.detach();

    Serial.print("position below: ");
    Serial.println(position);
    Serial.print("pos below: ");
    Serial.println(pos);
     
    Serial.print("updown: ");
    Serial.println(updown);
    Serial.print("updownpos: ");
    Serial.println(updownpos); 
   }
   else if (position == 10 && pos <= 126)
   {  
    myservo.attach(15);
    int pos10 = (base * 9); 
    for (pos = pos; pos <= pos10; pos +=1){
      myservo.write(pos);
      Serial.print("blinds are moving to pos: ");
      Serial.println(pos);
      delay(10);
      }
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    myservo.detach(); 
   }
    
   else if (position == 20 && pos >= 112) // Device ID of first device
   {  
    myservo.attach(15);
    int pos20 = (base * 8);
    for (pos = pos; pos >= pos20; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
    else if (position == 20 && pos <= 112) // Device ID of first device
   {  
    myservo.attach(15);
    int pos20 = (base * 8);
    for (pos = pos; pos <= pos20; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   
   else if (position == 30 && pos >= 98) // Device ID of first device
   {  
    myservo.attach(15);
    int pos30 = (base * 7);
    for (pos = pos; pos >= pos30; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   else if (position == 30 && pos <= 98) // Device ID of first device
   {  
    myservo.attach(15);
    int pos30 = (base * 7);
    for (pos = pos; pos <= pos30; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   
   else if (position == 40 && pos >= 84) // Device ID of first device
   {  
    myservo.attach(15);
    int pos40 = (base * 6);
    for (pos = pos; pos >= pos40; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
    else if (position == 40 && pos <= 84) // Device ID of first device
   {  
    myservo.attach(15);
    int pos40 = (base * 6);
    for (pos = pos; pos <= pos40; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   
   else if (position == 50 && pos >= 70)
   {  
    myservo.attach(15);
    int pos50 = (base * 5);
    for (pos = pos; pos >= pos50; pos -=1) 
    {
      myservo.write(pos);
      Serial.print("blinds are moving to pos: ");
      Serial.println(pos);
      delay(10);
    }
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    myservo.detach(); 
   }
   else if (position == 50 && pos <= 70)
   {  
    myservo.attach(15);
    int pos50 = (base * 5);
    for (pos = pos; pos <= pos50; pos +=1) 
    {
      myservo.write(pos);
      Serial.print("blinds are moving to pos: ");
      Serial.println(pos);
      delay(10);
    }
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    myservo.detach(); 
   }
   
   else if (position == 60 && pos >= 56) // Device ID of first device
   {
    myservo.attach(15);
    int pos60 = (base * 4);
    for (pos = pos; pos >= pos60; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   else if (position == 60 && pos <= 56) // Device ID of first device
   {
    myservo.attach(15);
    int pos60 = (base * 4);
    for (pos = pos; pos <= pos60; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
      
   else if (position == 70 && pos >= 42) // Device ID of first device
   {  
    myservo.attach(15);
    int pos70 = (base * 3);
    for (pos = pos; pos >= pos70; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   else if (position == 70 && pos <= 42) // Device ID of first device
   {  
    myservo.attach(15);
    int pos70 = (base * 3);
    for (pos = pos; pos <= pos70; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }  
   
   else if (position == 80 && pos >= 28) // Device ID of first device
   {  
    myservo.attach(15);
    int pos80 = (base * 2);
    for (pos = pos; pos >= pos80; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   else if (position == 80 && pos <= 28) // Device ID of first device
   {  
    myservo.attach(15);
    int pos80 = (base * 2);
    for (pos = pos; pos <= pos80; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   
   else if (position == 90 && pos >= 14) // Device ID of first device
   {  
    myservo.attach(15);
    int pos90 = (base * 1);
    for (pos = pos; pos >= pos90; pos -=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
    else if (position == 90 && pos <= 14) // Device ID of first device
   {  
    myservo.attach(15);
    int pos90 = (base * 1);
    for (pos = pos; pos <= pos90; pos +=1) {
    myservo.write(pos);
    Serial.print("blinds are moving to pos: ");
    Serial.println(pos);
    delay(10);
    }
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     myservo.detach();
   }
   
 
  return true; // request handled properly
}


bool onAdjustRangeValue(const String &deviceId, int &positionDelta) {
  blindsPosition += positionDelta;
  Serial.printf("Device %s position changed about %i to %d\r\n", deviceId.c_str(), positionDelta, blindsPosition);
  positionDelta = blindsPosition; // calculate and return absolute position
  Serial.print("adjustrangevalue changed");
  return true; // request handled properly
}


// setup function for WiFi connection
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

void setupSinricPro() {
  // get a new Blinds device from SinricPro
  SinricProBlinds &myBlinds = SinricPro[BLINDS_ID];
  myBlinds.onPowerState(onPowerState);
  myBlinds.onRangeValue(onRangeValue);
  myBlinds.onAdjustRangeValue(onAdjustRangeValue);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro and online.\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();

  Serial.begin(115200);
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  
  //OTA Updates//
  //Serial.begin(115200);
  WiFi.mode(WIFI_STA);
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266 Jonathan's Smart Blinds. To update go to <ip/update>. Please allow 5 minutes for the updates once the file has been uploaded.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  //Serial.println("HTTP server started");

  //Manual Button control//
  buttonOpen.begin();
  buttonClose.begin();
}

void loop() {
  SinricPro.handle();
  AsyncElegantOTA.loop();

  if (buttonOpen.pressed()) //checks the open button state.
  {
    Servo myservo;
    myservo.attach(15);
    for (pos = pos; pos >= 0; pos -=1){
      myservo.write(pos);
      Serial.print("blinds are max open: ");
      Serial.println(pos);
      delay(10);
    }
   myservo.detach();
   Serial.println("Open button was pressed.");
  }

  if (buttonClose.pressed()) //checks the open button state.
  {
    Servo myservo;
    myservo.attach(15);
    for (pos = pos; pos <= 140; pos +=1){
      myservo.write(pos);
      Serial.print("blinds are max closed: ");
      Serial.println(pos);
      delay(10);
    }
   myservo.detach();
   Serial.println("Close button was pressed.");
  }
  
}
