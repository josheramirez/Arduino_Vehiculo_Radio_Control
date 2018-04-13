
//modificado
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

#include <Servo.h>                    // Incluir la librería Servo
Servo servo1;                         // Crear un objeto tipo Servo llamado servo1
int servo = 90 ;

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
char mensaje1[10]="Message A";
char mensaje2[10]="Message B";
char mensaje3[10]="Message C";
char mensaje4[10]="Message D";
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

    servo1.attach(6) ;             // Conectar servo1 al pin 6
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
          Serial.print("dato leido:");
          Serial.println(dataReceived);

              
          if(strcmp(dataReceived,mensaje1)==0){
          Serial.println(dataReceived);
          Adelante ();
          }
          if(strcmp(dataReceived,mensaje2)==0){
          Serial.println(dataReceived);
          Atras ();
          }
          if(strcmp(dataReceived,mensaje3)==0){
          Serial.println(dataReceived);
          derecha ();
          }
          if(strcmp(dataReceived,mensaje4)==0){
          Serial.println(dataReceived);
          izquierda ();
          }
          
          newData = false;
          
      }
      else{parar();centrar();}
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
 analogWrite (ENA, 255); //Velocidad motor A

}

void parar()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 Serial.println("parado");
}

void centrar()
{
 servo1.write(90);
 Serial.println("centrado");
}

void izquierda()
{
 servo1.write(120);
 Serial.println("izquierda");
}
void derecha()
{
 servo1.write(60); 
 Serial.println("derecha");
}

