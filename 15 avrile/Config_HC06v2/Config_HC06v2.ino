/* Programme Arduino permettant de configurer la communication bluetooth entre la carte Arduino équipée du module HC-06 et un appareil équipé de l'application Config_bluetooth*/ 
/* Ce programme réalise l'affchage des caratères "R" lors de l'appui sur le bouton "Relâcher" et "S" lors de l'appui sur le bouton "Saisir" */ 

/********** Définition des librairies **********/ 
#include <SoftwareSerial.h>                 //Déclaration de la librairie SoftwareSerial.h permettant de mettre en place une communication série sur les broches numériques de la carte Arduino 

/********** Définition des variables globales **********/
//Les 3 variables suivantes peutvent être modifiées ou non par E5
int Baudrate=9600;                          //Déclaration d'une variable de type entier, nommé Baudrate et de valeur 9600
//int RxHC06=9;                               //Déclaration d'une variable de type entier, nommé RxHC06 et de valeur 9           
//int TxHC06=10; 
const int M1_dir = 4;// installation de la direction du moteur M1 pin 4
const int M1_speed = 3;// installation de la de vitesse du moteur M1 pin 3 
const int M2_dir = 12;// installation de la direction du moteur M2 pin 12
const int M2_speed = 11;// installation de la de vitesse du moteur M2 pin 11
const int M3_dir = 8;// installation de la direction du moteur M3 pin 8
const int M3_speed = 5;// installation de la de vitesse du moteur M3 pin 5

//Déclaration d'une variable de type entier, nommé TxHC06 et de valeur 10

int  result=0;                              //Déclaration d'une variable de type byte (=octet), nommé result et de valeur 0
SoftwareSerial mySerial(9, 10);    //Déclaration de la liaison série entre la carte Arduino et le module Bluetooth HC-06 (RxArduino=TxHC-06 et TxArduino=RxHC-06)

/********** Initialisation carte et I/O **********/
void setup(){
  pinMode(4, OUTPUT);// declaration de pin 
   pinMode(12, OUTPUT);// declaration de pin 
    pinMode(8, OUTPUT);// declaration de pin
     pinMode(7, INPUT);// declaration de pin
       pinMode(3, OUTPUT);// declaration de pin 
   pinMode(11, OUTPUT);// declaration de pin 
    pinMode(5, OUTPUT);// declaration de pin
     pinMode(6, OUTPUT);// declaration de pin
  Serial.begin(Baudrate);                   //Début de la communication série (avec moniteur série) et définition de la vitesse de transmission
  mySerial.begin(Baudrate);                 //Début de la communication série (avec module HC-06) et définition de la vitesse de transmission
  Serial.println("Connected:");     //Ouvrir le moniteur série (Outils -> Moniteur série) puis taper AT pour vérifier si com OK
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
 if( result == 1)// si le resulta est égalle a 0  
Serial.println ("avant");// aficher commende dans moniteur série
 digitalWrite(M1_dir,LOW);//  moteur m1 en mode avent
 
 analogWrite(M1_speed, 255);// moteur m1 vitesse 200
  digitalWrite(M2_dir, HIGH);//  moteur m1 en mode avent
 analogWrite(M2_speed, 255);// moteur m1 vitesse 200
  }

 else if( result == 2)// si le resultat est égal a 2  
Serial.println ("arriere");// afficher commande dans moniteur série
 digitalWrite(M1_dir,HIGH);//  moteur m1 en mode avant
 analogWrite(M1_speed, 255);// moteur m1 vitesse 200
  digitalWrite(M2_dir, LOW);//  moteur m1 en mode avant
 analogWrite(M2_speed, 255);// moteur m1 vitesse 200
  }
