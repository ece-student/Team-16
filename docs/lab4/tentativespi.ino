
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

void setup()
{
   
  // set the slaveSelectPin as an output:
  pinMode (ssFPGA, OUTPUT);
  
  // settings for SPI:
//  SPI.setBitOrder(MSBFIRST);
//  SPI.setDataMode(SPI_MODE0);
//  SPI.setClockDivider(SPI_CLOCK_DIV32);

  
  
  // initialize SPI:
  SPI.begin();
  
  // Serial setup:
  Serial.begin(9600);
  //set the pin high
  digitalWrite(ssFPGA,HIGH);
  // print when it starts so we know
  Serial.println("Sending information...");  
  


 // Serial.println("Info sent!");  
}

}

void loop() 
{
//byte data= to the information from got_data transferred
//(for now we will use a dummy)

digitalWrite (ssFPGA,LOW);
byte data;
SPI.transfer(data);
digitalWrite(ssFPGA,HIGH);

  }

}
