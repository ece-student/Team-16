
  // include the SPI library:
  #include <SPI.h>

  // declare the slave pin 
  uint8_t const ssFPGA = 10;

void setup()
{
   
  // set the slaveSelectPin as an output:
  pinMode (ssFPGA, OUTPUT);
  
  // settings for SPI:
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  
  // initialize SPI:
  SPI.begin();
  
  // Serial setup:
  Serial.begin(9600);
  
  // print when it starts so we know
  Serial.println("Sending information...");  
  


 // Serial.println("Info sent!");  
}

}

void loop() 
{
    digitalWrite( ssFPGA, 0 );
    for ( uint8_t i = 0; i < 10; i++) {
        delay( 10 );
        SPI.beginTransaction( SPISettings( 4000000, MSBFIRST, SPI_MODE3 ) );
        {
            uint8_t const MISO = SPI.transfer(i == 0 ? 0xAA : 0x55 );
            Serial.println( MISO, BIN );
        }
        SPI.endTransaction();
    }
    digitalWrite( ssFPGA, 1 );
  }

}
