
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

void setup()
{
   
  // set the slaveSelectPin as an output:
  pinMode (ssFPGA, OUTPUT);
  
// settings for SPI:
  //SPI.setBitOrder(MSBFIRST);
  //SPI.setDataMode(SPI_MODE0);
  //SPI.setClockDivider(SPI_CLOCK_DIV32);

  
  // initialize SPI:
  SPI.begin();
  digitalWrite(ssFPGA, HIGH);
  
  // Serial setup:
  Serial.begin(9600);
  
  // print when it starts so we know
  Serial.println("Sending information...");  
   
}


void loop() 
{
//byte data= to the information from got_data transferred
//(for now we will use a dummy)


byte data = 10010010;
SPI.beginTransaction(SPISettings(8000000,MSBFIRST,SPI_MODE0));
digitalWrite(ssFPGA, HIGH);
SPI.transfer(data);
digitalWrite(ssFPGA, LOW);

SPI.endTransaction();
}
