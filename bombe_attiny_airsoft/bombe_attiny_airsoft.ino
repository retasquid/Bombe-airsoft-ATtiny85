/*
les boutonts sont associer en pont diviseur 
pour utiliser seulement 1 pin sur l'ATtiny
650<btn_gauche<700
475<btn_centre<550
0<btn_droite<50
*/
#include <TinyOzOLED.h>
#include <TinyWireM.h>
#define pinBoutons 3  
#define buzzer 1

int temp = 0;
int tmpdesa = 0;
int min = 0;
int sec = 0;

void setup() {
  OzOled.init();
  OzOled.sendCommand(0xA1);        // set Orientation
  OzOled.sendCommand(0xC8);
  OzOled.printString("TEMPS DE",3);
  OzOled.printString("DESAMORCAGE:",1,1);
  OzOled.printNumber((long)tmpdesa,0,3);
  pinMode(pinBoutons,INPUT);
}
void loop() {
  if(analogRead(pinBoutons) <= 50){ //bouton incrément  //temps desamorcage
    tmpdesa+=5;
    OzOled.printString("              ",0,3); //clear line
    OzOled.printNumber((long)tmpdesa,0,3);
    OzOled.printString("sec",4,3);
    delay(5);
  }
  if(analogRead(pinBoutons)>=650 & analogRead(pinBoutons)<=700 & tmpdesa>0){ //bouton décrement
    tmpdesa-=5;
    OzOled.printString("               ",0,3); //clear line
    OzOled.printNumber((long)tmpdesa,0,3);
    OzOled.printString("sec",4,3);
    delay(5);
  }
  if(analogRead(pinBoutons)<=550 & analogRead(pinBoutons)>=475){  //debut temps voulut
    OzOled.printString("               ",0,1); //clear line
    OzOled.printString("               ",0,3); //clear line
    OzOled.printString("TEMPS EXPLOSION",0,0);
    OzOled.printNumber((long)min,0,2);
    OzOled.printString("min",5,2);
    OzOled.printNumber((long)sec,0,4);
    OzOled.printString("sec",5,4);

    while(1){
      if(analogRead(pinBoutons) <= 50){ //temps avant explosion
        temp+=30;
        OzOled.printString("     ",0,2);
        OzOled.printString("     ",0,4);
        min=int(temp/60);
        sec=temp-(60*min);
        OzOled.printNumber((long)min,0,2);
        OzOled.printNumber((long)sec,0,4);
      }
      if(analogRead(pinBoutons)>=675 & analogRead(pinBoutons)<=690 & temp>0){ 
        temp-=30;
        OzOled.printString("     ",0,2);
        OzOled.printString("     ",0,4);
        min=int(temp/60);
        sec=temp-(60*min);
        OzOled.printNumber((long)min,0,2);
        OzOled.printNumber((long)sec,0,4);
      }
      if(analogRead(pinBoutons)<=525 & analogRead(pinBoutons)>=500){  //debut chrono
        while(temp >=0){
          OzOled.printString("     ",0,2);
          OzOled.printString("     ",0,4);
          OzOled.printString("TEMPS RESTANT :",0,0);
          min=int(temp/60);
          sec=temp-(60*min);
          OzOled.printNumber((long)min,0,2);
          OzOled.printNumber((long)sec,0,4);
          delay(34);  //1sec en prenant les instruction du dessus
          temp--;
          if(analogRead(pinBoutons)<=550 & analogRead(pinBoutons)>=475){   //debut desamorcage
            while(tmpdesa>0){
              if(analogRead(pinBoutons)<=550 & analogRead(pinBoutons)>=475){
                tmpdesa-=1;
                delay(100);
              }
              else{
                break;
              }
            }
            if(tmpdesa==0){
              OzOled.printString("DESAMORCE      ",0,0);
              OzOled.printString("Partie Termine ",0,2);
              OzOled.printString("               ",0,4);
              while(1){
                digitalWrite(buzzer,HIGH);   
                delay(50);
                digitalWrite(buzzer,LOW); 
                delay(50);
              }           //fin desamorcage
            }
          }               //fin chrono
        } 
        OzOled.printString("BOOOOOM        ",0,0);
        OzOled.printString("Partie Termine ",0,2);
        OzOled.printString("               ",0,4);
        while(1){
          digitalWrite(buzzer,HIGH);   
        }
      }
    }
  }
}