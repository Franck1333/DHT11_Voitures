//AIDES: http://recitmst.qc.ca/arduino/capteur-humidite-et-temperature-ambiante/

//---DHT11----
#include <dht.h>        //Lib utilise pour le capteur DHT11
//#define dht_apin A5   //Capteur connecté à A5 pour analogique
#define dht_apin 7      //Capteur connecté à 8 pour numérique
dht DHT;                //Objet dht de type DHT
//----DHT11---

//---Ecran_OLED----
#include "U8glib.h"     //Lib pour la gestion de l'affichage de l'ecran OLED
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //Constructeur de mon ecran a moi --> https://amzn.to/2GuxYdT
//---Ecran_OLED----

//---LED_Activite---
const int LED = 2;     //Enregistrement de la localisation de la led sur l'Arduino
//---LED_Activite---

void setup(void) {
pinMode(LED,OUTPUT);                            //Indication que he ou est connecte la LED est une broche de sortie (+)
u8g.setColorIndex(1);                           //Demarrage des Pixels de l'ecran OLED
Serial.begin(9600);                             //Initialisation de la communication serie pour la console
Serial.println("Demarrage du Programme...");    //Message dans la console Serie
delay(2048);                                    //Delay de demarrage pour permettre au capteur d'humidite/Temperature de lancer sa capture correctement
}

void loop(void) {
// picture loop
u8g.firstPage();
do {
draw();                                         //Appel de la fonction effectuant l'affichage sur l'ecran OLED
} while( u8g.nextPage() );

// rebuild the picture after some delay of 1 seconde
delay(1024);
}

//FONCTION DE TRAITEMENT ET D'AFFICHAGE SUR LECRAN OLED+CONSOLE SERIE
void draw() {
// graphic commands to redraw the complete screen should be placed here
u8g.setFont(u8g_font_7x13);                                 //Police d'affichage compacte

digitalWrite(LED,LOW);                                      //Désactivation de la LED, indiquant l'activiter du programme

DHT.read11(dht_apin);                                       //Lecture du Pin Analogique A5 ou est connecte le catpeur
Serial.print("Humidite = ");                                //Affichage dans la console serie
Serial.print(DHT.humidity);                                 //Affichage dans la console serie de l'humidite via l'objet DHT
Serial.print(" % ");                                        //Affichage dans la console serie
Serial.print("temperature = ");                             //Affichage dans la console serie
Serial.print(DHT.temperature);                              //Affichage dans la console serie de la Temperature via l'objet DHT
Serial.println(" °C ");
delay(1024);                                                //Attendre 1s avant la prochaine lecture

u8g.drawStr(0, 10, "Valeurs du Capteur:");                  //Affichage sur l'ecran OLED d'une chaine de caractere
//---Humidite---
u8g.setPrintPos(0,25);                                      //Positionnement du curseur pour afficher autre chose... u8g.setPrintPos(COLONNES, LIGNES);  
u8g.print("Humidite:");                                     //Affichage sur l'ecran OLED     
u8g.setPrintPos(65,25);                                     //Prise de Nouvelle position du curseur u8g.setPrintPos(COLONNES, LIGNES);
u8g.print(DHT.humidity);                                    //Affichage sur l'ecran OLED de la valeur de l'humidite
u8g.setPrintPos(100,25);                                    //Nouvelle Position du curseur
u8g.print(" %");                                            //Affichage sur l'ecran OLED
//---Humidite---

//---Temperature---
u8g.setPrintPos(0,50);                                       //Positionnement du curseur pour afficher autre chose... u8g.setPrintPos(COLONNES, LIGNES);  
u8g.print("Temperature:");                                   //Affichage sur l'ecran OLED          
u8g.setPrintPos(85,50);                                      //Nouvelle Position du curseur
u8g.print(DHT.temperature);                                  //Affichage sur l'ecran OLED de la valeur de la Temperature
u8g.setPrintPos(120,50);                                     //Nouvelle Position du curseur
u8g.print("C");                                              //Affichage sur l'ecran OLED  
//---Temperature---

digitalWrite(LED,HIGH);                                      //Activation de la LED, indiquant l'activiter du programme
}
