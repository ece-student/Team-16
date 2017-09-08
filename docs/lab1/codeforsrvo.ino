#include <Servo.h>
Servo myservo;
int LED= 9; 
int PINNAME = A1; 
int VAL=0;
int Y=0;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  myservo.attach(LED); 
}
// the loop function runs over and over again forever
void loop() {
 
  VAL=analogRead(PINNAME); // potentiometer reading
  analogWrite(LED,VAL);
  Y = map(VAL, 0, 1023, 0, 180);//map 0-1023 to 0-180 range
  myservo.write(Y);
  delay(500);
  Serial.print("pot reading  ");
  Serial.print(VAL);
  Serial.print(" : ");
  Serial.print(" speed and direction ");
  Serial.println(Y);
}
