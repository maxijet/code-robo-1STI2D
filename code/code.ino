/*
Contrôle de deux moteurs DC avec Arduino et un Joystick 
*/

//Inclusion de librairies //Inclusion bibliothèques
#include <L298N.h>#include <L298N.h>
#include <Bounce2.h>#include <Bounce2.h>

const int ledEnable = 13; // la led à bord nous montrera l'état d'activation des moteurs const int ledEnable = 13 ; // la led à bord nous montrera l'état d'activation des moteurs
const int pinSwEnable = 2;  // le bouton présent dans le module joystick qui active ou désactive le contrôle const int pinSwEnable = 2 ; // le bouton présent dans le module joystick qui active ou désactive le contrôle 

unsigned long debounceDelay = 10;// millisecondes pour le debonuce du bouton unsigned long debounceDelay = 10 ; 
//Les boutons-poussoirs génèrent souvent de fausses transitions ouverture/fermeture lorsqu'ils sont enfoncés,
//en raison de problèmes mécaniques et physiques : ces transitions peuvent être lues comme plusieurs pressions en très peu de temps,ce qui trompe le programme.
//Cet exemple montre comment debounce une entrée, ce qui signifie vérifier deux fois dans un court laps de temps pour s'assurer que le bouton-poussoir est bien enfoncé. 
//Sans debounce, appuyer une fois sur le bouton peut entraîner des résultats imprévisibles. 
//Cette esquisse utilise la millis()fonction pour garder une trace du temps écoulé depuis que le bouton a été enfoncé.

const int jX = A0;  //broche analogique lisant les valeurs pour les Xconst int jX = A0 ; //broche analogique lisant les valeurs pour les X
const int EN_X = 3;const int EN_X = 3;
const int IN1_X = 4;const int IN1_X = 4;
const int IN2_X = 5;const int IN2_X = 5;
long speedX, valX, mapX;  //variables pour la gestion des mouvements moteurs Xlong speedX, valX, mapX ; //variables pour la gestion des mouvements moteurs X
unsigned int direzioneX;unsigned int direzioneX;

const int jY = A1;  //valeurs de lecture de la broche analogique pour Yconst int jY = A1 ; //valeurs de lecture de la broche analogique pour Y 
const int EN_Y = 6;const int EN_Y = 6;
const int IN1_Y = 7;const int IN1_Y = 7;
const int IN2_Y = 8;const int IN2_Y = 8;
long speedY, valY, mapY;  //variables pour la gestion des mouvements moteurs Ylong speedY, valY, mapY ; //variables pour la gestion des mouvements moteurs Y
unsigned int direzioneY;unsigned int direzioneY;

const int maxSpeed = 255; //Vitesse maximale réglable pour le moteurconst int maxSpeed = 255 ; //Vitesse maximale réglable pour le moteur
const int minSpeed = 0; //vitesse minimale qui peut être définie pour le moteurconst int minSpeed = 0 ; //vitesse minimale qui peut être définie pour le moteur

const int treshold = 30;  //la lecture du potentiomètre n'est jamais fiable à 100%, cette valeur aide à déterminer le point à considérer comme "Stand still" dans les mouvements. int treshold = 30 ; //la lecture du potentiomètre n'est jamais fiable à 100%, cette valeur aide à déterminer le point à considérer comme "Stand still" dans les mouvements.
long tresholdUp, tresholdDown;  //des variables de service pour effectuer la tâche décrite ci-dessus tresholdUp, tresholdDown ; //des variables de service pour effectuer la tâche décrite ci-dessus

boolean abilitato, muoviX, muoviY, enable;  //variables de gestion du mouvementibooléen enabled, moveX, moveY, enable ; //variables de gestion du mouvement

const uint8_t AVANTI = L298N::FORWARD;const uint8_t AVANTI = L298N::FORWARD;
const uint8_t DIETRO = L298N::BACKWARD;const uint8_t DIETRO = L298N::BACKWARD;

Bounce btnEnable = Bounce();  //instanciez un bouton de la bibliothèque BounceBounce btnEnable = Bounce() ; //instanciez un bouton de la bibliothèque Bounce.

//installation des moteurs//installation des moteurs
L298N motoreX(EN_X, IN1_X, IN2_X);(EN_X, IN1_X, IN2_X);
L298N motoreY(EN_Y, IN1_Y, IN2_Y);(EN_Y, IN1_Y, IN2_Y);

void setup() {void setup() {
  //initialiser les valeurs //initialiser les valeurs
  speedX = speedY = 0;= speedY = 0;
  enable = false;= false;

  //définition du mode pin//définition du mode pin
  pinMode(ledEnable, OUTPUT);(ledEnable, OUTPUT);

  pinMode(pinSwEnable, INPUT_PULLUP); //l'entrée du commutateur doit être définie comme INPUT_PULLUP(pinSwEnable, INPUT_PULLUP) ; //l'entrée du commutateur doit être définie comme INPUT_PULLUP

  digitalWrite(ledEnable, enable);(ledEnable, enable);

  //configurer le bouton du joystick en utilisant la bibliothèque Bounce//configurer le bouton du joystick en utilisant la bibliothèque Bounce
  btnEnable.attach(pinSwEnable);.attach(pinSwEnable);
  btnEnable.interval(debounceDelay);.interval(debounceDelay);

  //calculer la plage de valeurs dans laquelle la position du joystick doit être considérée comme "Stand still"//calculer la plage de valeurs dans laquelle la position du joystick doit être considérée comme "Stand still".
  tresholdDown = (maxSpeed / 2) - treshold;= (maxSpeed / 2) - treshold;
  tresholdUp = (maxSpeed / 2) + treshold;= (maxSpeed / 2) + treshold;

  //configurer les paramètres du moteur//configurer les paramètres du moteur
  motoreX.setSpeed(minSpeed);.setSpeed(minSpeed);
  motoreY.setSpeed(minSpeed);.setSpeed(minSpeed);
}}

void loop() {void loop() {
  //exécuter la fonction de vérification et de lecture du bouton déterminant l'état activé//exécuter la fonction de vérification et de lecture du bouton déterminant l'état activé.
   checkEnable();();

  digitalWrite(ledEnable, enable);  //affiche l'état d'activation via la led sur la broche 13(ledEnable, enable) ; //affiche l'état d'activation via la led sur la broche 13

  //réaliser une lecture analogique des valeurs provenant des potentiomètres du joystick/réaliser une lecture analogique des valeurs provenant des potentiomètres du joystick
  valX = analogRead(jX);= analogRead(jX);
  valY = analogRead(jY);= analogRead(jY);

  //maps valeurs lues selon la vitesse minimale et maximale//maps valeurs lues selon la vitesse minimale et maximale
  mapX = map(valX, 0, 1023, minSpeed, maxSpeed);= map(valX, 0, 1023, minSpeed, maxSpeed);
  mapY = map(valY, 0, 1023, minSpeed, maxSpeed);= map(valY, 0, 1023, minSpeed, maxSpeed);

  //exécuter la fonction de contrôle du moteur//exécuter la fonction de contrôle du moteur
  pilotaMotori(mapX, mapY);(mapX, mapY);
}}

void pilotaMotori(long mapX, long mapY) {void pilotaMotori(long mapX, long mapY) {

  if (mapX <= tresholdDown) {if (mapX <= tresholdDown) {
    // x remonte // x remonte
    speedX = map(mapX, tresholdDown, minSpeed,   minSpeed, maxSpeed);= map(mapX, tresholdDown, minSpeed,   minSpeed, maxSpeed);
    muoviX = true;= true;
    direzioneX = DIETRO;= DIETRO;
  } else if (mapX >= tresholdUp) {} else if (mapX >= tresholdUp) {
    // x continue // x continue
    speedX = map(mapX,  maxSpeed, tresholdUp,  maxSpeed, minSpeed);= map(mapX,  maxSpeed, tresholdUp,  maxSpeed, minSpeed);
    muoviX = true;= true;
    direzioneX = AVANTI;= AVANTI;
  } else {} else {
    // x reste immobile // x reste immobile
    speedX = 0;= 0;
    muoviX = false;= false;
  }}

  if (mapY <= tresholdDown) {if (mapY <= tresholdDown) {
    //y va giù//y va giù
    speedY = map(mapY, tresholdDown, minSpeed,   minSpeed, maxSpeed);= map(mapY, tresholdDown, minSpeed,   minSpeed, maxSpeed);
    muoviY = true;= true;
    direzioneY = DIETRO;= DIETRO;
  } else if (mapY >= tresholdUp) {} else if (mapY >= tresholdUp) {
    //y va su//y va su
    speedY = map(mapY,  maxSpeed, tresholdUp,  maxSpeed, minSpeed);= map(mapY,  maxSpeed, tresholdUp,  maxSpeed, minSpeed);
    muoviY = true;= true;
    direzioneY = AVANTI;= AVANTI;
  } else {} else {
    //y sta fermo//y sta fermo
    speedY = 0;= 0;
    muoviY = false;= false;
  }}

  if (enable) {if (enable) {
    if (muoviX) {if (muoviX) {
      motoreX.setSpeed(speedX);.setSpeed(speedX);
      motoreX.run(direzioneX);.run(direzioneX);
    } else {} else {
      motoreX.stop();.stop();
    }}

    if (muoviY) {if (muoviY) {
      motoreY.setSpeed(speedY);.setSpeed(speedY);
      motoreY.run(direzioneY);.run(direzioneY);
    } else {} else {
      motoreY.stop();.stop();
    }}
  } else {} else {
    motoreX.stop();.stop();
    motoreY.stop();.stop();
  }}
}}

void checkEnable() {void checkEnable() {

  btnEnable.update();.update();

  if (btnEnable.fell()) {if (btnEnable.fell()) {
    enable = !enable;= !enable;
  }}

}}
