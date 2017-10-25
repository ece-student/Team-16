
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t ssFPGA = 10;

unsigned int pack_payload(char x, char y) {
  // Top 4 bits are y and bottom 4 bits are x
  return (y << 4) | x;
}

void digitalFPGAWrite(unsigned char value) {
  digitalWrite(FPGA_SS, LOW);
  SPI.transfer(value); // send a byte over SPI
  digitalWrite(FPGA_SS, HIGH);
}

void setup()
{
   
  // set the slaveSelectPin as an output:
  pinMode (ssFPGA, OUTPUT);
  
// settings for SPI:
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
// or   SPI.beginTransaction(SPISettings(8000000,MSBFIRST,SPI_MODE0));
  
  // initialize SPI:
  digitalWrite(ssFPGA, HIGH);
  SPI.begin();
  
  // Serial setup:
  Serial.begin(9600);
  
  // print when it starts so we know
  Serial.println("Sending information...");  
   
}

}

void loop() 
{
//byte data= to the information from got_data transferred
//(for now we will use a dummy)

/* 
  byte data;
  SPI.beginTransaction() 
  digitalWrite(ssFPGA, LOW);
  SPI.transfer(data);
  digitalWrite(ssFPGA, HIGH);
*/  
  
unsigned char x, y;
unsigned char payload;
/*
  // Send the same packet every second.
  payload = pack_payload(1, 3);
  digitalFPGAWrite(payload);
  delay(3000);
*/
  // Iterate over all maze positions, sending a new one every second.
  Serial.println("Iterating through maze positions.\n");
  for (x = 0; x < 4; x++) {
    for (y = 0; y < 5; y++) {
      // Construct and send a test payload.
      // Note that this only works because the dimensionality of our maze restricts
      // x and y to be less than 4 bits.
      payload = pack_payload(x, y);
      Serial.println(payload); // print payload to serial
      digitalFPGAWrite(payload);
      delay(1000);
    }     
  }

}
