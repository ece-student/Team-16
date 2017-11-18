
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

void setup()
{
 SPI.begin(); 
pinMode (ssFPGA, OUTPUT);
Serial.begin(9600);

  unsigned int maze [5][4]=
  { {B0000000100000000, B0100000000000000, B1000000100000000,  B1100000000000000}, 
    {B0000100000000000, B0100100000000000, B1000100000000000,  B1100100000000000}, 
    {B0001000000000000, B0101000000000000, B1001000000000000,  B1101000000000000},
    {B0001100000000000, B0101100000000000, B1001100000000000,  B1101100000000000}, 
    {B0010000000000000, B0110000000000000, B1010000000000000,  B1110011000000000},
  };
  
  for (int i=0; i<5; i++){
    for (int j=0; j<4; j++){
      SPI.beginTransaction(SPISettings(250000,LSBFIRST,SPI_MODE0));
      digitalWrite(ssFPGA, HIGH);
      Serial.print(maze[i][j]);
      Serial.print("\n");
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


