/********** Définition des librairies **********/
//A compléter par E4 (inclure les librairies utiles, l'une pour l'utilisation de servomoteurs et la seconde pour la communication série)


/********** Définition des variables globales **********/
//Création de variables liées à la communication Bluetooth
int Baudrate=9600;                          //Définition de la vitesse de transmission (valeur en Bauds)
int RxHC06=9;                               //Définition de la broche connectée à la borne Rx du HC-06      
int TxHC06=10;                              //Définition de la broche connectée à la borne Tx du HC-06
byte input=0;                               //Définition d'une variable qui recevra les données sous forme d'octet de la communication série avec HC-06

const int M1_dir = 4;// 
const int M1_speed = 3;

int nb_montee=0;                            //Définition d'une variable qui va s'incrémenter à chaque appui sur le bouton "Monter" ==> Sécurité pour éviter que le bras bute contre la coque 



/********** Initialisation carte et I/O **********/
void setup() {
//A compléter par E4

}


/********** Définition fonctions de déplacements du robot **********/
 void loop() {
 //marche_avant()
  digitalWrite(M1_dir, LOW);// 
  analogWrite(M1_speed, 200);
  
}

void marche_arriere()
{ //A compléter par E4
    
}

void tourner_droite()
{ //A compléter par E4
  
}

void tourner_gauche()
{ //A compléter par E4
    
}

/********** Définition fonctions de déplacements de la pince **********/
void attraper_objet()
{ //A compléter par E4
   
}

void relacher_objet()
{ //A compléter par E4
   
}

/********** Définition fonctions de déplacements du bras **********/
void monter_bras()
{ //A compléter par E4
  
}

void baisser_bras()
{ //A compléter par E4
  
}
/*****************************************/
/********** Programme principal **********/
/*****************************************/
