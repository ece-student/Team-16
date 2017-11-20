
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

void setup()
{
 SPI.begin(); 
pinMode (ssFPGA, OUTPUT);
Serial.begin(9600);

//  { {B0000001101100000, B0100000011100000, B1000000111100000,  B1100000111000000}, 
//    {B0000111001110000, B0100100011110000, B1000100011110000,  B1100100011010000}, 
//    {B0001000001110000, B0101000011110000, B1001000011110000,  B1101000011010000},
//    {B0001100001110000, B0101100111110000, B1001100111110000,  B1101100011010000}, 
//    {B0010000000110000, B0110000010110000, B1010000010110000,  B1110011010010000},
//  };
   
}


void loop() 
{
//byte data= to the information from got_data transferred
//(for now we will use a dummy)
word maze [5][4]=
  { {0x0360, 0x40E0, 0x81E0, 0xC1C0},
    {0x0E70, 0x48F0, 0x88F0, 0xC8D0},
    {0x1070, 0x50F0, 0x90F0, 0xD0D0},
    {0x1870, 0x59F0, 0x99F0, 0xD8D0},
    {0x2030, 0x60B0, 0xA0B0, 0xE690},
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
