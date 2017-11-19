
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

void setup()
{
 SPI.begin(); 
pinMode (ssFPGA, OUTPUT);
Serial.begin(9600);

//  { {B0000001101100000, B0100000001000000, B1000000101000000,  B1100000101000000}, 
//    {B0000111000000000, B0100100000000000, B1000100000000000,  B1100100000000000}, 
//    {B0001000000000000, B0101000000000000, B1001000000000000,  B1101000000000000},
//    {B0001100000000000, B0101100100000000, B1001100100000000,  B1101100000000000}, 
//    {B0010000000000000, B0110000000000000, B1010000000000000,  B1110011000000000},
//  };
   
}


void loop() 
{
//byte data= to the information from got_data transferred
//(for now we will use a dummy)
word maze [5][4]=
  { {0x0360, 0x4000, 0x8100, 0xC100},
    {0x0E00, 0x4800, 0x8800, 0xC800},
    {0x1000, 0x5000, 0x9000, 0xD000},
    {0x1800, 0x5900, 0x9900, 0xD800},
    {0x2000, 0x6000, 0xA000, 0xE600},
  };
  
  for (int i=0; i<5; i++){
    for (int j=0; j<4; j++){
      SPI.beginTransaction(SPISettings(1000000,LSBFIRST,SPI_MODE0));
      digitalWrite(ssFPGA, HIGH);
      Serial.print(maze[i][j], HEX);
      Serial.print("\n");
      SPI.transfer16(maze[i][j]);
      digitalWrite(ssFPGA, LOW);
      SPI.endTransaction();
      delay(100);
    }
  }

}

// only a wall in the south and east borders of (0,0)
