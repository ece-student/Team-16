
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

void setup()
{
 SPI.begin(); 
pinMode (ssFPGA, OUTPUT);

  unsigned maze [5][4]=
  { {00000000, 01000000, 10000001,  11000000}, 
    {00001000, 01001000, 10001000,  11001000}, 
    {00010000, 01010000, 10010000,  11010000},
    {00011000, 01011000, 10011000,  11011000}, 
    {00100000, 01100000, 10100000,  11100110},
  };
  
  for (int i=0; i<5; i++){
    for (int j=0; j<4; j++){
      SPI.beginTransaction(SPISettings(8000000,LSBFIRST,SPI_MODE0));
      digitalWrite(ssFPGA, HIGH);
      SPI.transfer(maze[i][j]);
      digitalWrite(ssFPGA, LOW);
      SPI.endTransaction();
      delay(100);
    }
  }
   
  // set the slaveSelectPin as an output:
  
  
//  // initialize SPI:
//  SPI.begin();
//  digitalWrite(ssFPGA, HIGH);
//  
//  // Serial setup:
  Serial.begin(9600);
//  
//  // print when it starts so we know
//  Serial.println("Sending information...");  
   
}


void loop() 
{
//byte data= to the information from got_data transferred
//(for now we will use a dummy)

/*
byte data = 10010010;
SPI.beginTransaction(SPISettings(8000000,LSBFIRST,SPI_MODE0));
digitalWrite(ssFPGA, HIGH);
SPI.transfer(data);
digitalWrite(ssFPGA, LOW);

SPI.endTransaction();*/
}

