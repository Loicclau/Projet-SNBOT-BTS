/*
code destiné à une carte Arduino qui vise à transférer des caractères 
d'une connexion série à une autre connexion série. Il s'agit d'un programme 
simple qui lit le port série standard de l'Arduino à une vitesse de 9600 bauds. 
Si le programme détecte une touche valide ('z', 's', 'q', 'd', 'r', 'f', ou 'x') 
envoyée via la connexion série, il l'affiche dans la console série, puis l'envoie 
à une autre connexion série sur les broches 16 et 17 avec une vitesse de 19200 bauds. 
Si une touche non valide est détectée, le programme affiche un message indiquant 
que cette touche n'est pas disponible
*/
#include <Arduino.h>
#include <string>

void setup() {
  Serial1.begin(19200, SERIAL_8N1, 16,17); //Envoi des informations vers l'arduino
  Serial.begin(9600); // Initialiser la connexion série à 9600 bauds

Serial.println("\n");
Serial.println("       &&%%%&&%##%&&");
Serial.println("      /&&%%%&&%##%&&");
Serial.println("   /((((((((((((((((((((((");
Serial.println("   /((((((((((((((((((((((");
Serial.println("   /((((((((((((((((((((((");
Serial.println("   /(((((  SNBOT   ((((((( ,@@@");
Serial.println("  @%((((( DE  LOIC (((((((/@@#/@");
Serial.println(" @@(((((((((((((((((((((((#@@(/#");
Serial.println("#@@/((((((((((((((((((((((%@@%//");
Serial.println(" /@########################@@/(.");
Serial.println("  @###%%%%%%%%%%%%%%%%%####@@/#/");
Serial.println("   @@@@@@                  %@@(@");
Serial.println("\n");
Serial.println("Taper h pour voir les commandes disponibles");
  
}

void loop() {
  if (Serial.available() > 0) { // Vérifier si des données sont disponibles sur la connexion série
   char val = Serial.read(); // Lire le caractère envoyé

      if (val == 'z') {
        //Serial.print("La touche tapée est : ");
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Avancer");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1
    } else if (val == 's') {
        //Serial.print("La touche tapée est : ");
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Reculer");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1
    } else if (val == 'q') {
        //Serial.print("La touche tapée est : ");
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Rotation Gauche");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1
    } else if (val == 'd') {
        //Serial.print("La touche tapée est : ");
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Rotation Droite");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1
    } else if (val == 'r') {
        //Serial.print("La touche tapée est : ");
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Augmentation Vitesse");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1
    } else if (val == 'f') {
        //Serial.print("La touche tapée est : ");
        //Serial.println(val); // Afficher la touche acceptée
        Serial.println("Réduction Vitesse");
        Serial1.print(val); // Envoyer le caractère vers l'Arduino via Serial1
    } else if (val == 'x') {
        //Serial.print("La touche tapée est : ");
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
    
    








