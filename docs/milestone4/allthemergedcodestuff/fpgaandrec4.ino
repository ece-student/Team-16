
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

int donePin=7;

word maze [5][4]=
  { {0x0640, 0x4000, 0x8000, 0xC000},
    {0x0800, 0x4800, 0x8800, 0xC800},
    {0x1000, 0x5000, 0x9000, 0xD000},
    {0x1800, 0x5800, 0x9800, 0xD800},
    {0x2000, 0x6000, 0xA000, 0xE000},
  };



void doneSignal(){
   for (int i=0; i<5; i++){
    for (int j=0; j<4; j++){
      if (bitRead(maze[i][j],0)==1){
        digitalWrite(donePin, HIGH);
      }
   }
   }
};

RF24 radio(9,10);
const uint64_t pipes[2] = { 0x0000000038LL, 0x0000000039LL };
typedef enum { role_ping_out = 1, role_pong_back } role_e;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

role_e role = role_pong_back;
// declare the slave pin 
uint8_t ssFPGA = 10;

void setup()
{
  pinMode (donePin,OUTPUT);
  SPI.begin(); 
  pinMode (ssFPGA, OUTPUT);
  Serial.begin(9600);
  // declare the slave pin 
  uint8_t ssFPGA = 6;
  
 for (int i=0; i<5; i++){
    for (int j=0; j<4; j++){
      SPI.beginTransaction(SPISettings(900000,LSBFIRST,SPI_MODE0));
      digitalWrite(ssFPGA, HIGH);
      SPI.transfer16(maze[i][j]);
      digitalWrite(ssFPGA, LOW);
      SPI.endTransaction();
      Serial.println(maze[i][j],BIN);
    }
  }

//RADIO STUFF

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  radio.begin();


  radio.setRetries(15,15);
  radio.setAutoAck(true);
  radio.setChannel(0x50);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  radio.startListening();
  radio.printDetails();
}



void loop() 
{
//pingout
  if (role == role_ping_out)
  {
    radio.stopListening();
    unsigned long time = millis();
    printf("Now sending %lu...",time);
    bool ok = radio.write( &time, sizeof(unsigned long) );

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    radio.startListening();
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }
    delay(1000);
  }

  // Pong back role.  Receive each packet, dump it out, and send it back
  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned long got_time;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );

        // Spew it
        printf("Got payload %lu...",got_time);
        printf("\n");
        // Delay just a little bit to let the other unit
        // make the transition to receiver
        delay(20);

        
//ADDED RECEIVER CODE STARTS
bool done = false;
while (!done)
{ 
  done = radio.read( maze, sizeof(word) );
  for (int i=0; i < 5; i++) {
    for (int j=0; j < 4; j++) {
      printf("%d ", maze[i][j]);
    }
    printf("\n");
  }

  delay(20);

}
      }
      radio.stopListening();
      radio.write( &got_time, sizeof(unsigned long) );
      printf("Sent response.\n\r");
      radio.startListening();
    }
  }
  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }


  
  for (int i=0; i<5; i++){
    for (int j=0; j<4; j++){
      SPI.beginTransaction(SPISettings(900000,LSBFIRST,SPI_MODE0));
      digitalWrite(ssFPGA, HIGH);
      SPI.transfer16(maze[i][j]);
      digitalWrite(ssFPGA, LOW);
      SPI.endTransaction();
      Serial.println(maze[i][j],BIN);
    }

  doneSignal();
 
  delay(750);
  }
}
      

