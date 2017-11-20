//ADDED RECEIVER CODE STARTS
unsigned char got_maze[5][4];
bool done = false;
while (!done)
{ 
  // Fetch the payload.
  done = radio.read( got_maze, sizeof(got_maze) );

  // Print the maze
  for (int i=0; i < 5; i++) {
    for (int j=0; j < 4; j++) {
      printf("%d ", got_maze[i][j]);
    }
    printf("\n");
  }

  // Delay just a little bit to let the other unit
  // make the transition to receiver
  delay(20);

}
      }
