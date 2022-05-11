/* Programme Arduino permettant de configurer la communication bluetooth entre la carte Arduino équipée du module HC-06 et un appareil équipé de l'application Config_bluetooth*/ 
/* Ce programme réalise l'affchage des caratères "R" lors de l'appui sur le bouton "Relâcher" et "S" lors de l'appui sur le bouton "Saisir" */ 

/********** Définition des librairies **********/ 
#include <SoftwareSerial.h>                 //Déclaration de la librairie SoftwareSerial.h permettant de mettre en place une communication série sur les broches numériques de la carte Arduino 

/********** Définition des variables globales **********/
//Les 3 variables suivantes peutvent être modifiées ou non par E5
int Baudrate=9600;                          //Déclaration d'une variable de type entier, nommé Baudrate et de valeur 9600
int RxHC06=9;                               //Déclaration d'une variable de type entier, nommé RxHC06 et de valeur 9           
int TxHC06=10; 
int avant;
//Déclaration d'une variable de type entier, nommé TxHC06 et de valeur 10

byte result=0;                              //Déclaration d'une variable de type byte (=octet), nommé result et de valeur 0
SoftwareSerial mySerial(TxHC06, RxHC06);    //Déclaration de la liaison série entre la carte Arduino et le module Bluetooth HC-06 (RxArduino=TxHC-06 et TxArduino=RxHC-06)

/********** Initialisation carte et I/O **********/
void setup(){
  Serial.begin(Baudrate);                   //Début de la communication série (avec moniteur série) et définition de la vitesse de transmission
  mySerial.begin(Baudrate);                 //Début de la communication série (avec module HC-06) et définition de la vitesse de transmission
  Serial.println("ENTER AT Commands:");     //Ouvrir le moniteur série (Outils -> Moniteur série) puis taper AT pour vérifier si com OK
}                                           //Renommer module Bluetooth: AT+NAMEnom
                                            //Définition du Baud Rate: AT+BAUDx (x=1->1200, x=2->2400, x=3->4800, x=4 -> 9600 (défaut), ..., x=8 -> 115200)
/*****************************************/
/********** Programme principal **********/
/*****************************************/
void loop(){
  if (mySerial.available())                 //Si données entrantes (entre HC-06 et Arduino) sont non nulles
  {
    result=mySerial.read(); //Lecture des données reçues
    Serial.println (result);
    Serial.write(result);  //Envoie des données reçues sur moniteur série
 if( result == 0)
Serial.println ("avant");
  }
 if (Serial.available())                   //Si données entrantes (entre PC et Arduino) sont non nulles
  {
   mySerial.write(Serial.read());          //Envoie des données reçues à HC-06
  } 
}
