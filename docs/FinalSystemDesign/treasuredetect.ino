
volatile int IRQcount;
int pin = 2;
int pin_irq = 0; //IRQ that matches to pin 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  attachInterrupt(pin_irq, IRQcounter, RISING);
}

void IRQcounter() {
  IRQcount++;
}

void loop() {
  // put your main code here, to run repeatedly:

  cli();//disable interrupts
  IRQcount = 0;
  sei();//enable interrupts

  delay(25);

  cli();//disable interrupts
  int result = IRQcount;
  sei();//enable interrupts

  Serial.print(F("Counted = "));
  Serial.println(result);

  if(result> 175 && result < 179) {
      Serial.println("7 kHz");
    }
    else if(result> 304 && result < 310){
      Serial.println("12 kHz");
    }
    else if(result> 425 && result < 429){
      Serial.println("17 kHz");
    }
    else{
      Serial.println("none");
    }
    Serial.println("");
}
