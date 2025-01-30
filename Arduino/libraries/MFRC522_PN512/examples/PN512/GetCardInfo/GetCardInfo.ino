#include <PN512.h>
#include <SPI.h>

#define RST     3                   //set RST     pin to be pin 3
#define SS      2                  //set SS      pin to be pin 2

PN512 reader(SS,RST);             //create reader instace
byte serialCounter;                 //init counter for first boot
int rstCounter = 1;                 //rstCounter is used if PN self-test is unknown 

void setup() {
  Serial.begin(9600);                //init Serial
  SPI.begin();                       //init SPI
  reader.PCD_Init();                 //init PN512
  reader.PCD_AntennaOn();            //turn antenna on
  pinMode(LED_BUILTIN, OUTPUT);      //set builtin LED to output
}

void loop() {
  //first loop counter just so that it prints out the version and message on first boot/reset
  if(Serial && serialCounter == 0) {
    serialCounter = 1;
    while(rstCounter){
      rstCounter = reader.PCD_DumpVersionToSerial();		//PN does self-test and returns 0 if OK
      delay(50);
    }
    Serial.println("Reader is ready, scan card or tag");
  }

  if(!reader.PICC_IsNewCardPresent()) return;   //wait for new card to be present
  if(!reader.PICC_ReadCardSerial())   return;   //read that new card 
  reader.ledBlink(5,LED_BUILTIN);                                  //indicator when the card is read

  reader.PICC_DumpDetailsToSerial(&(reader.uid));   //write to serial card details, card UID, card SAK, and card TYPE

  delay(50);                                    //optional delay
}

