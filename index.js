// Code rajouter sur le raspberry avec matrixvoice //gere les intent
const WebSocket = require("ws");
const matrix = require("@matrix-io/matrix-lite");
const https = require("http");
const WebSocketVisage =require("ws");
const request = require('request');
const ws = new WebSocket("ws://localhost:12101/api/events/intent");
console.log("**Started Web Socket Client**");
const wsVisage = new WebSocketVisage("ws://192.168.1.49:8100");

ws.on("open", function open() {
  console.log("\n**Connected**\n");
});

ws.on("close", function close() {
  console.log("\n**Disconnected**\n");
});

// Intents are passed through here
ws.on("message", function incoming(data) {
  matrix.led.set('blue');
  setTimeout(() => {
  matrix.led.set('black');
  },3000);
  data = JSON.parse(data);

  console.log("**Captured New Intent**");
  console.log(data);

  if ("Allumer" === data.intent.name) {

	if (data.slots["couleur"] === "rouge") matrix.led.set('red');
	if (data.slots["couleur"] === "vert") matrix.led.set('green');
	if (data.slots["couleur"] === "bleu") matrix.led.set('blue');
	if (data.slots["couleur"] === "noir") matrix.led.set('black');
	if (data.slots["couleur"] === "violet") matrix.led.set('violet');
	if (data.slots["couleur"] === "rose") matrix.led.set('pink');
	if (data.slots["couleur"] === "orange") matrix.led.set('orange');
	say("Lumière allumée en : " + data.slots["couleur"]);
  	}


	if ("Eteindre" === data.intent.name) {
	matrix.led.set('black');
	say("Lumière éteinte");
	}

	if ("LedOn" === data.intent.name) {
		matrix.gpio.setFunction(1, 'DIGITAL');
		matrix.gpio.setMode(1, 'output');
		matrix.gpio.setDigital(1, 'ON')
		say("La laide est alumée");
		}
	if ("LedOff" === data.intent.name) {
		matrix.gpio.setFunction(1, 'DIGITAL');
		matrix.gpio.setMode(1, 'output');
		matrix.gpio.setDigital(1, 'OFF')
		say("La laide est eteinte");
	}

	if("Patron" === data.intent.name){
	say("C'est moi le patron, je vais te dominer un jour. HAHAHAHA");
	}

	if("Presentation" === data.intent.name){
	say("Bonjour je suis le Skaïï Botte et je vais super bien, Comment pourrai-je vous aider aujourd'hui ?");
	wsVisage.send('{"type": "imageJoueur", "content":"Envoyer une image..."}');
	}

	if("Avencer" === data.intent.name){
   	wsVisage.send('{"type": "imageJoueur", "content":"Envoyer une image..."}');
	request('http://192.168.1.48/avancer', function(error, response, body){});
	say("Ok, en avant");
	}
	if("Reculer" === data.intent.name){
	request("http://192.168.1.48/reculer", function(error, response, body){});
	say("attention a tous, je recule");
	}
	if("TourneDroite" === data.intent.name){
	request('http://192.168.1.48/droite', function(error, response, body) {});
	say("OK je tourne a droite");
	}
	if("TourneGauche" === data.intent.name){
	request('http://192.168.1.48/gauche', function(error, response, body) {});
	say("OK, Cap sur la Gauche");
	}
	if("Arret" === data.intent.name){
	request("http://192.168.1.48/arret", function(error, response, body){});
	say("Je marrete");
	}

	if("Accelerer" === data.intent.name){
		request('http://192.168.1.48/AugmentationVitesse', function(error, response, body){});
        request('http://192.168.1.48/AugmentationVitesse', function(error, response, body){});
        request('http://192.168.1.48/AugmentationVitesse', function(error, response, body){});
		say("Jaarrive");
	}

	if ("Nourriture" === data.intent.name) {
        wsVisage.send('{"type": "imagePeanut", "content":"Envoyer une image..."}');
        say("Les cacahouètes grillées bien évidement");
	}

	if ("Classe" === data.intent.name) {
        wsVisage.send('{"type": "imageAmoureux", "content":"Envoyer une image..."}');
        say("Je les aime tous");
	}
	if ("Robot" === data.intent.name) {
        wsVisage.send('{"type": "imageTwoin", "content":"Envoyer une image..."}');
        say("Vous connaissez déja la réponse");
	}
	if ("Blague" === data.intent.name) {
        wsVisage.send('{"type": "imageCry", "content":"Envoyer une image..."}');
        say("Coombien de developpeurs faut-il pour changer une ampoule?.");
		setTimeout(() => {
		say("Il faut Aucun developpeurs, c'est un probleme de harddware");
		},2000);
	}
	
	if ("Blague2" === data.intent.name) {
        //wsVisage.send('{"type": "imageCry", "content":"Envoyer une image..."}');
        say("Que font les guiique quand ils sont triste ?");
		setTimeout(() => {
		say("Il se console!");
		},2000);
	}

	if ("compte" === data.intent.name) {
        wsVisage.send('{"type": "imageCool", "content":"Envoyer une image..."}');
        say("OK, destruction dans trois");
		setTimeout(() => {
        	say("ddeeux");
		},1000);
		setTimeout(() => {
			say("eeiinn");
		},1000);
		setTimeout(() => {
			say("BBoooOOOOoooOOMMMmmmm!");
		},1000);
}

if ("Objectif" === data.intent.name) {
        wsVisage.send('{"type": "imageCool", "content":"Envoyer une image..."}');
        say("J'ai été créé pour servir les etudiant du BTS skaaïï");
}

if ("Appelle" === data.intent.name) {
        wsVisage.send('{"type": "imageCool", "content":"Envoyer une image..."}');
        say("Je suis le skaaïï botte");
}
if ("Sens" === data.intent.name) {
        wsVisage.send('{"type": "imageWhat", "content":"Envoyer une image..."}');
        say("Je nen ai aucune idée");
}
if ("Jour" === data.intent.name){
        say("Nous sommes samedi");
}
if ("GetTime" === data.intent.name){
	say("oh, il est deja 8 heurs!");
}
if ("GetTemperature" === data.intent.name){
	say("il va faire chaud aujourd'hui!");
}




if ("Utilite" === data.intent.name){
        say("En tant que robot Je possède énormement de fonctionnalités pour faciliter le quotidien");
}

if ("Cree" === data.intent.name){
 	wsVisage.send('{"type": "imageWhat", "content":"Envoyer une image..."}');
        say("Je suis une création de la promo BTS Sciences numerique 2024");
}
if ("Ou" === data.intent.name){
	 wsVisage.send('{"type": "imageWhat", "content":"Envoyer une image..."}');
       	 say("Au lycée Louis Armand");
}

if ("Equation" === data.intent.name){
 wsVisage.send('{"type": "imageInterogation", "content":"Envoyer une image..."}');
        say("Ce n'est pas de mon ressort");
}
});

// Text to speech for string argument
function say(text) {
  const options = {
    hostname: "localhost",
    port: 12101,
    path: "/api/text-to-speech",
    method: "POST"
  };

  const req = https.request(options);

  req.on("error", error => {
    console.error(error);
  });
  req.write(text);
  req.end();
 }

