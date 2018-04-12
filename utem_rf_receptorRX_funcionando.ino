
//RECEPTOR_RX_RF

// SimpleRx - the slave or the receiver
//https://forum.arduino.cc/index.php?topic=421081.0

/*
ARDUINO->RF
13->SK5(5)
12->MISO(7)
11->MOSI(6)
10->CSN(4)
9->CE(3)

RF->FUENTE EXTERNA
VCC(2)->3.3V
GND(1)->GND

ARDUINO->PROTOBOARD
5->LED
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

int ENA = 4;
int IN1 = 5;
int IN2 = 6;

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;

int led=5;
//===========

void setup() {
 pinMode (ENA, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);

    Serial.begin(9600);
pinMode(led,OUTPUT);
    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//=============

void loop() {
    getData();
    showData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        //Serial.print("Data received ");
        Serial.println(dataReceived);
        newData = false;
         Adelante ();
 delay (5000);
 Parar();
        if(dataReceived=="Message A"){
        Serial.println(dataReceived);
        newData = false;
         Adelante ();
 delay (5000);
 Parar();
        digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
          }
         if(dataReceived=="Message B"){
        Serial.println(dataReceived);
        newData = false;
         Atras ();
 delay (5000);
 Parar();
        digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
          }
 
        
    }
}


void Adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A

}

void Atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 128); //Velocidad motor A

}

void Parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A

}
