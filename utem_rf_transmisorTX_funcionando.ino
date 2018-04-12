//TRANSMISOR_TX_RF

// SimpleTx - the master or the transmitter
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
5->BTN1
7->LED
8->BTN2

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[10] = "Message 0";
char txNum = '0';


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

int btn=5;
int led=7;
bool estado;

int btn2=8;
bool estado2;

const int timeThreshold = 250;
volatile int ISRCounter = 0;
int counter = 0;
volatile int ISRCounter2 = 0;
int counter2 = 0;
long timeCounter = 0;

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");
pinMode(btn,INPUT);
pinMode(led,OUTPUT);
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {

  digitalWrite(led,LOW);
//    currentMillis = millis();
//    if (currentMillis - prevMillis >= txIntervalMillis) {
//        send();
//        prevMillis = millis();
//    }
if(digitalRead(btn)){debounceCount();}
if(digitalRead(btn2)){debounceCount2();}

   if (counter != ISRCounter)
   {
    send(); digitalWrite(led,HIGH);
    counter = ISRCounter;
    //Serial.println(counter);
   }


      if (counter2 != ISRCounter2)
   {
    send2(); digitalWrite(led,HIGH);
    counter2 = ISRCounter2;
    //Serial.println(counter);
   }
if(estado2==HIGH){send2(); digitalWrite(led,HIGH);delay(50);}
}

//====================

void send2() {

    bool rslt;
dataToSend[8] = 'B';
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        Serial.println("  Acknowledge received");
        //updateMessage();
    }
    else {
        Serial.println("  Tx failed");
    }
}
void send() {

    bool rslt;
dataToSend[8] = 'A';
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        Serial.println("  Acknowledge received");
        //updateMessage();
    }
    else {
        Serial.println("  Tx failed");
    }
}

//================

void updateMessage() {
        // so you can see that new data is being sent
    txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }
    dataToSend[8] = txNum;
}

void debounceCount()
{
   if (millis() > timeCounter + timeThreshold)
   {
      ISRCounter++;
      timeCounter = millis();
   }
}

void debounceCount2()
{
   if (millis() > timeCounter + timeThreshold)
   {
      ISRCounter2++;
      timeCounter = millis();
   }
}
