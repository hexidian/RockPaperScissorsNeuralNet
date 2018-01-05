#include <stdio.h>
#include <string.h>

void outputMove(int index){
  const char *moves[] = {"rock","paper","scissors"};
  printf("%s\n", moves[index]);

}

int makeMove(int values[3][3][3], int pastMoves[3]){
  int decidingValues[3] = {0,0,0};
  for (int i = 0; i < 3; i++){
    int pieceMoved = pastMoves[i];
    for (int j = 0; j < 3; j++){
      decidingValues[j] += values[i][pieceMoved][j];
    }
  }
  return maxIndex(decidingValues);
}

int maxIndex(int array[]){
  int length = sizeof(array)/sizeof(array[0]);
  int best[2] = {0,array[0]};
  for (int i = 1; i < length; i++){
    if (array[i] > best[1]) {
      best[0] = i;
      best[1] = array[i];
    }
  }
  //printf("the top value was %d\n", best[1]);
  return best[0];
}

void updateArray(int array[], int newElement) {
  int length = sizeof(array)/sizeof(array[0]);
  for (int i = 0; i < length - 1; i ++) {
    array[i] = array[i+1];
  }
  array[length-1] = newElement;
}

void print(int array[]){
  int length = sizeof(array)/sizeof(array[0]);
  printf("length is: %d",length);
  for (int i = 0; i < length; i ++) {
    printf("%d\n", array[i]);
  }
  printf("\n");
}

int main(){
  int goForAnother = 1;

  /*  the elements in evaluateRecentMoves correspond to:
   *  move
   *  pieceMoved
   *  value to change for piece
   */
  int evaluateRecentMoves[3][3][3] = {
    {
      {5,0,0},
      {0,5,0},
      {0,0,5}
    },
    {
      {10,0,0},
      {0,10,0},
      {0,0,10}
    },
    {
      {20,0,0},
      {0,20,0},
      {0,0,20}
    }
  };
  int pastMoves[3] = {0,1,2};
  char userMove[1];
  int userMoveInt;
  while (goForAnother) {
    int move = makeMove(evaluateRecentMoves,pastMoves);
    outputMove(move);
    printf("what was your move? (r/p/s)\n");
    scanf("%s",userMove);
    printf("\n");

    //now we need to convert the input to an integer
    if (strcmp(userMove,"r")==0) {
      userMoveInt = 0;
      printf("it's a rock\n");
    } else if (strcmp(userMove,"p")==0) {
      printf("it's a paper\n");
      userMoveInt = 1;
    } else if (strcmp(userMove,"s")==0) {
      userMoveInt = 2;
      printf("it's a scissors\n");
    } else {return 1;}//this closes the program because it has gotten an invalid input error

    updateArray(pastMoves,userMoveInt);
    printf("pastMoves is:\n");
    print(pastMoves);
  }
  return 0;
}
