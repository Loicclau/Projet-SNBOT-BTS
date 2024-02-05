/*
code destiné à une carte Arduino qui vise à transférer des caractères 
d'une connexion série à une autre connexion série. Il s'agit d'un programme 
simple qui lit le port série standard de l'Arduino à une vitesse de 9600 bauds. 
Si le programme détecte une touche valide ('z', 's', 'q', 'd', 'r', 'f', ou 'x') 
envoyée via la connexion série, il l'affiche dans la console série, puis l'envoie 
à une autre connexion série sur les broches 16 et 17 avec une vitesse de 19200 bauds. 
*/
#include <Arduino.h>
#include <string>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>


const char *ssid = "BTS_SN"; //BTS_SN  Galaxy A54 5G
const char *password = "ECIR1234";  //12345678
String RobotState;
AsyncWebServer server(80);
// Replaces placeholder with LED state value
String processor(const String& variable){
    if(variable == "STATE"){
    Serial.print(RobotState);
    return RobotState;
    }
return String("est éteint");
}


void setup() {

    Serial1.begin(19200, SERIAL_8N1, 16,17); //Envoi des informations vers l'arduino
    Serial.begin(9600); // Initialiser la connexion série à 9600 bauds
    //Serial.begin(115200);

 // controle /
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
  }
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  

 // Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "est éteint";
request->send(SPIFFS, "/index.html", String(), false, processor);
});
// Route to load style.css file
server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(SPIFFS, "/style.css", "text/css");
});

server.on("/avancer", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "avance !";
Serial.println("Avancer");
Serial1.print('z');
request->send(SPIFFS, "/index.html", String(), false, processor);
});

server.on("/reculer", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "recule";
Serial.println("Reculer");
Serial1.print('s');
request->send(SPIFFS, "/index.html", String(), false, processor);
});

server.on("/droite", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "tourne a droite";
Serial.println("Rotation Droite");
Serial1.print('d'); // Envoyer le caractère vers l'Arduino via Serial1
request->send(SPIFFS, "/index.html", String(), false, processor);
});

server.on("/gauche", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "tourne a gauche";
Serial.println("Rotation Gauche");
Serial1.print('q'); // Envoyer le caractère vers l'Arduino via Serial1
request->send(SPIFFS, "/index.html", String(), false, processor);
});

server.on("/arret", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "est a l'arrêt";
Serial.println("Arrêt");
Serial1.print('x'); // Envoyer le caractère vers l'Arduino via Serial1
request->send(SPIFFS, "/index.html", String(), false, processor);
});

server.on("/AugmentationVitesse", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "accélère !";
Serial.println("Augmentation Vitesse");
Serial1.print('r');
request->send(SPIFFS, "/index.html", String(), false, processor);
});

server.on("/RéductionVitesse", HTTP_GET, [](AsyncWebServerRequest *request){
RobotState = "freine";
Serial.println("Réduction Vitesse");
Serial1.print('f');
request->send(SPIFFS, "/index.html", String(), false, processor);
});
// Start server
server.begin();


}

void loop() {
  if (Serial.available() > 0) { // Vérifier si des données sont disponibles sur la connexion série
   char val = Serial.read(); // Lire le caractère envoyé 

      if (val == 'z') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Avancer");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 's') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Reculer");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 'q') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Rotation Gauche");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 'd') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Rotation Droite");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 'r') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Augmentation Vitesse");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 'f') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Réduction Vitesse");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 'x') {
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Arrêt");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1

    } else if (val == 'h'){
        Serial.println("Pour controler le robot vous pouvez faire : ");
        Serial.println("Taper z pour Avancer");//Avancer
        Serial.println("Taper s pour Reculer");//Reculer
        Serial.println("Taper q pour faire une Rotation Gauche");//Rotation Gauche
        Serial.println("Taper d pour faire une Rotation Droite");//Rotation Droite
        Serial.println("Taper r pour Augmenter la Vitesse"); //Augmentation Vitesse
        Serial.println("Taper f pour Augmenter la Vitesse");//Augmentation Vitesse
        Serial.println("Taper x pour L'Arrêt");//Arrêt
    }else {
        Serial.print("Cette touche n'est pas disponible.");
        Serial.print("\n");
    }
    }
}