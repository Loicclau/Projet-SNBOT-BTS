#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
/*Code utilisant une esp32 et un serveur web pour faire les lampe controlable a distance via wifi*/

const char* ssid = "BTS-SN";  // Galaxy A54 5G
const char* password = "ECIR1234"; //   12345678
// Set LED GPIO
const byte ledPins[] = {15, 2, 4};    //define red, green, blue led pins
const byte chns[] = {0, 1, 2};        //define the pwm channels
int red, green, blue; // For ramdom

// Stores LED state
String ledState;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String processor(const String& var){
  Serial.println(var);
    if(var == "STATE"){
      Serial.print(ledState);
      return ledState;
    }
return String("éteinte");
}

void setColor(byte r, byte g, byte b) {
  ledcWrite(chns[0], 255 - r); //Common anode LED, low level to turn on the led.
  ledcWrite(chns[1], 255 - g);
  ledcWrite(chns[2], 255 - b);
}

void setup(){
  Serial.begin(115200);
    for (int i = 0; i < 3; i++) {  
    ledcSetup(chns[i], 1000, 8);
    ledcAttachPin(ledPins[i], chns[i]);
  }
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
  }
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(3000);
  Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(SPIFFS, "/style.css", "text/css");
  });
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(255, 255, 255); // Définit la couleur à Blanc
  ledState = "allumée";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(0, 0, 0); // Définit la couleur à Noir
  ledState = "éteinte";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(0, 0, 255); // Définit la couleur à red
  ledState = "allumée en rouge";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
    server.on("/green", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(0, 255, 0);// Définit la couleur à verte 
  ledState = "allumée en vert";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/blue", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(255, 0, 0); // Définit la couleur à bleu
  ledState = "allumée en bleu";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/jaune", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(0, 255, 255); // Définit la couleur à jaune
  ledState = "allumée en jaune";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/cyan", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(255, 255, 0); // Définit la couleur à cyan
  ledState = "allumée en cyan";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/maginta", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(255, 0, 255); // Définit la couleur à majinta
  ledState = "allumée en maginta";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/orange", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(37, 184, 247); // Définit la couleur à orange
  ledState = "allumée en orange";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/violet", HTTP_GET, [](AsyncWebServerRequest *request){
  setColor(173, 5, 93); // Définit la couleur à violet
  ledState = "allumée en violet";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/random", HTTP_GET, [](AsyncWebServerRequest *request){
  red = random(0, 256);
  green = random(0, 256);
  blue = random(0, 256);
  setColor(red, green, blue); // couleur au pif
  ledState = "allumée";
  request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}
void loop(){
}