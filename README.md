# Smart-blinds Intro:

This project was made possible by Sinric Pro, the smart home IOT API.

# Librarys Needed:
Library name:             Version:        By:
- ArduinoJson             -6.19.4         by Benoit Blanchon
- ArduinoWebSocket        -2.3.5
- AsyncElegantOTA         -2.2.6          by Ayush Sharma
- AsyncElegantOTA-master
- AsyncHTTPRequest_Generic-master-1.8.1 by Khoi Hoang
- Button                  -1.0.0          by Michael Adams
- ESPAsyncTCP-master
- ESPAsyncWebServer-master
- Servo                   -1.1.8          by Arduino
- SinricPro               -2.9.16         by Boris Jaeger
- WebSockets              -2.3.6          by Markus Sattler


# Parts List:
- NodeESP8266 <br/>
- Servo motor <br/>
- Custom Adapter - servo to blinds rod <br/>
- USB to micro USB cable <br/>
- Push button switch x2 <br/>
- 3 female breadboard cables or an ethernet cable can be used <br/>

# The build:
**Step 1.** Create a [sinric pro](https://sinric.pro/) account then add a new device. <br/>
**Step 2.** Edit the arduino code in the arduino IDE software, the sections that will need to be edited are WIFI username and password, Sinric pro app key, Sinric pro app secret, and the device ID. <br/>
**Step 3.** Plug in the ESP8266 with the USB cable to your computer and upload the code to the ESP8266 from the arduino IDE. <br/>
**Step 4.** Find a place to attach the servo motor to the blinds, remember to connect the adapter to the servo motor before you attach the motor to the blinds rod located at the top of the blinds. <br/>
**Step 5.** Place the ESP8266 into a case to protect it. The case can be 3d printed or a small tupperware box with some holes made can be used. <br/>
**Step 6.** Connect the servo motor and buttons to the ESP8266 as labled in the diagram below. <br/>
**Step 7.** Connect the USB power cable to the ESP8266. <br/>
**Step 8.** Open the Alexa or Google home APP then add the skill sinric pro, once you have signed in to the sinric pro skill search for device in the Alexa or Google home app and add it to your devices list. <br/>


# Diagrams & Screenshots:
The screenshot below shows the sinric pro interface where you are able to control the blinds if you do not have Alexa or Google home.
![sinric pro interface](interface.PNG)

Wireing diagram:
![wireing diagram](diagram.png)

