/*
fft_adc.pde
guest openmusiclabs.com 8.18.12
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.  there is a pure data patch for
visualizing the data.
*/

// do #defines BEFORE #includes
#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter - delay() and millis() killed
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // do fft signal for mic once
  
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ;  i < 512 ; i+= 2) { // save 256 samples
      fft_input[i] = analogRead(analogPin); // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei();
    Serial.println("start mic");
    for (byte i = 0 ; i < FFT_N/2 ; i++) { 
      Serial.println(fft_log_out[i]); // send out the data
      if (fft_input[38] > 60)
        digitalWrite(LED_BUILTIN, HIGH);      
    }
    
    Serial.println("end mic")
    
     
    // do fft for treasure sensor continuously
    while(1) { // reduces jitter
    cli();  
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    // window data, then reorder, then run, then take output
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei(); // turn interrupts back on
    
    int range7 = 0;
    int range12 = 0;
    int range17 = 0;
  
    Serial.println(" opt start")
    
    for(int i = 10; i < 128; i++){
      if(fft_log_out[i]>60){
        Serial.print(fft_log_out[i]);
        if(i>=45 && i<=47){
          range7++;
        }
        if(i>=79 && i<=81){
          range12++;
        }
        if(i>=113 && i<=115){
          range17++;
        }
      } 
      Serial.print(" ");
    }
    
    if(range7>0 && range7>range12 &&range7>range17){
      Serial.println("7 kHz");
    }
    else if(range12>0 && range12>range7 &&range12>range17){
      Serial.println("12 kHz");
    }
    else if(range17>0 && range17>range12 &&range17>range7){
      Serial.println("17 kHz");
    }
    else{
      Serial.println("none");
    }
    Serial.println("opt end")
    Serial.println("");
  }
}
