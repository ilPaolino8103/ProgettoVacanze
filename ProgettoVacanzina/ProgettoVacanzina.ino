#include <IRremote.h>


// defines pins numbers
const int trigPin = 11;
const int echoPin = 10;
const int buzzer = 13;
const int ledPin = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int motorePin = 5;
const int ir = 12;

IRrecv irc(ir);
decode_results results;
// defines variables
long duration=0;
int distance=0;
int distanzaRossa=20;
int distanzaGialla=50;
int distanzaVerde=100;
bool stato=false;
bool porta=false;
int timer=0;
bool motore;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
  irc.enableIRIn();
}


void loop() {
 if(irc.decode(&results)){
    irc.resume();
   // Serial.println(results.value, HEX);
  }
  if(results.value == 0xFD50AF && porta==false) {
    analogWrite(motorePin, 20);
   timer=millis();
      porta=true;
    motore=true;
    Serial.println("porta in apertura");
   
   
  }
 
   if(timer==millis()-5000&& motore==true) {
    analogWrite(motorePin,0);
     motore=false;
     Serial.println("porta ferma");
  }
  
   if(results.value == 0xFD10EF&& porta==true) {
   analogWrite(motorePin, -20);
     motore=true;
     timer=millis();
      porta=false;
     Serial.println("porta in chiusura");
  }
   if(results.value == 0xFD00FF) {
   stato= !stato;
   
  }
  
  if(stato==true){
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance = duration*0.034*0.5;
  
  
  
  if (distance > distanzaVerde){
  digitalWrite(buzzer, LOW);
 
  digitalWrite(ledPin3, LOW);
     digitalWrite(ledPin2, LOW);
     digitalWrite(ledPin, LOW);
}

if (distance > distanzaRossa && distance > distanzaGialla && distance <= distanzaVerde){
  digitalWrite(buzzer, HIGH);
   digitalWrite(ledPin2, LOW);
     digitalWrite(ledPin, LOW);
  digitalWrite(ledPin, HIGH);
}
  if (distance > distanzaRossa && distance <= distanzaGialla){
  digitalWrite(buzzer, HIGH);
 digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin2, HIGH);
     digitalWrite(ledPin, HIGH);
}
if (distance <= distanzaRossa){
  digitalWrite(buzzer, HIGH);
  
  digitalWrite(ledPin3, HIGH);
 
  
}
}
  if(stato==false){
    digitalWrite(buzzer, LOW);
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
  }
  results.value=0;

 
}
