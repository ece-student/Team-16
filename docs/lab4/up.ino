#include "printf.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  printf_begin();
}

void loop() {

  unsigned char maze[5][4] =
{
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
};


  // put your main code here, to run repeatedly:
unsigned char x_coord = 3;
unsigned char y_coord = 2;
unsigned char pos_data = 3;

// Use bit shifting to pack the bits
// For deployment with a robot, something like this should be factored out into
// a function, along with the code to unpack the bitsnew_data = x_coord << 5 | y_coord << 2 | pos_data;
// For the test case of (5, 5, 3) the byte shoud look like: 10010011
// In decimal this is 147

    for (int i = 0; i<5; i++) {
      printf("\n");
      for (int j = 0; j <4; j++) {
        printf("%d", maze[i][j]);
      }
    }

maze[x_coord][y_coord] = pos_data;
printf("\n New updated maze \n");
    for (int i = 0; i<5; i++) {
      printf("\n");
      for (int j = 0; j <4; j++) {
        printf("%d", maze[i][j]);
      }
    }
    printf("\n old maze \n");

}
