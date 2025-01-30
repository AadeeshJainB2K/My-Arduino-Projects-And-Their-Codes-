#include <PN512.h>
#include <SPI.h>
#include <Keyboard.h>

#define RST     3                   //set RST     pin to be pin 3
#define SS      2                  //set SS      pin to be pin 2

PN512 reader(SS,RST);             //create reader instace
byte serialCounter;					//init counter for first boot
int rstCounter = 1;                 //rstCounter is used if PN self-test is unknown 

void setup() {
  Serial.begin(9600);                //init Serial
  SPI.begin();                       //init SPI
  Keyboard.begin();                  //init keyboard, if no arguments are set the default keyboard layout is EN_keyboard
  reader.PCD_Init();                 //init PN512
  reader.PCD_AntennaOn();            //turn antenna on
  pinMode(LED_BUILTIN, OUTPUT);      //set builtin LED to output
}

void loop() {
   if(Serial && serialCounter == 0) {
    serialCounter = 1;
    while(rstCounter){
      rstCounter = reader.PCD_DumpVersionToSerial();
      delay(50);
    }
    Serial.println("Reader is ready, scan card or tag");
  }
  if(!reader.PICC_IsNewCardPresent()) return;   //wait for new card to be present
  if(!reader.PICC_ReadCardSerial())   return;   //read that new card 
  reader.ledBlink(5,LED_BUILTIN);                                  //indicator when the card is read

  byte cardUID[reader.uid.size];
  byte cardSAK;
  byte cardType;

  for(byte i = 0; i < reader.uid.size; i++){
    cardUID[i] = reader.uid.uidByte[i];
  }    

  cardSAK = reader.uid.sak;

  cardType = reader.PICC_GetType(reader.uid.sak);
  

  //write info to USB/Keyboard
  Keyboard.print("Card UID: ");
  for(byte i = 0; i < reader.uid.size; i++){
    Keyboard.print(cardUID[i] < 0x10 ? "0" : "");//if byte[i] is less then 10h then print 0 else print nothing 
    Keyboard.print(cardUID[i],HEX);              //print byte[i]
  }
  Keyboard.write(0x0A);                     //press ENTER key for new line

  Keyboard.print("Card SAK: ");
  Keyboard.print(cardSAK, HEX);
  Keyboard.write(0x0A);

  Keyboard.print("Card Type: ");
  Keyboard.print(reader.PICC_GetTypeName(cardType));
  Keyboard.write(0x0A);
  //done writing info 

  delay(50);                                //optional delay
}


