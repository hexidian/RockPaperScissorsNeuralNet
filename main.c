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
  int length = (sizeof(array)/sizeof(array[0]))+1;
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
  int length = (sizeof(array)/sizeof(array[0]))+1;
  for (int i = 0; i < length - 1; i ++) {
    array[i] = array[i+1];
  }
  array[length-1] = newElement;
}

void print(int array[]){
  int length = (sizeof(array)/sizeof(array[0]))+1;
  for (int i = 0; i < length; i ++) {
    printf("%d\n", array[i]);
  }
  printf("\n");
}

void hillClimb(int values[3][3][3],int pastData[20]){

  int best[2] = [evaluateValues(values,pastData),0];

}

int main(){
  int goForAnother = 1;

  /*  evaluateRecentMoves is:
   *  [move][pieceMoved][valueForPiece] to change for piece
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
  int extendedPastMoves[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2};
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
    } else if (strcmp(userMove,"p")==0) {
      userMoveInt = 1;
    } else if (strcmp(userMove,"s")==0) {
      userMoveInt = 2;
    } else {return 1;}//this closes the program because it has gotten an invalid input error

    updateArray(pastMoves,userMoveInt);
    updateArray(extendedPastMoves,userMoveInt);

    hillClimb(evaluateRecentMoves,extendedPastMoves);

  }
  return 0;
}
