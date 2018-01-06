#include <stdio.h>
#include <string.h>

#define pastLooking 10

int compare1dArrays(int arrayA[], int arrayB[], int length){
  for (int i = 0; i < length; i++){
    if (arrayA[i] != arrayB[i]){ return 0; }
  }
  return 1;
}

void copyChangeCode(int newArray[9], int oldArray[9]){
  for (int i = 0; i < 9; i++){
    newArray[i] = oldArray[i];
  }
}

void printValues(int values[3][3][3]){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      for (int k = 0; k < 3; k++){
        printf("%d\n", values[i][j][k]);
      }
      printf(">\n");
    }
    printf(">>\n");
  }
}

void copyValues(int newArray[3][3][3], int oldArray[3][3][3]){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      for (int k = 0; k < 3; k++){
        newArray[i][j][k] = oldArray[i][j][k];
      }
    }
  }
}

void applyChange(int values[3][3][3], int changeCode[9]){

  for (int a = 0; a < 9; a++){
    changeCode[a] --;
  }

  for (int i = 0; i < 3; i++){
    for (int k = 0; k < 3; k++){
      values[i][k][ (0+k) % 3 ] += changeCode[ (3*i) + 0];
      values[i][k][ (1+k) % 3 ] += changeCode[ (3*i) + 1];
      values[i][k][ (2+k) % 3 ] += changeCode[ (3*i) + 2];
    }
  }

  for (int a = 0; a < 9; a++){//we need this so that we don't mess up changeCode in the upper stack frame
    changeCode[a] ++;
  }

}

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

void updateArray(int array[], int newElement, int length) {
  for (int i = 0; i < length - 1; i ++) {
    array[i] = array[i+1];
  }
  array[length-1] = newElement;
}

void print(int array[], int length){
  for (int i = 0; i < length; i ++) {
    printf("%d\n", array[i]);
  }
  printf("\n");
}

void hillClimb(int values[3][3][3],int pastData[pastLooking]){

  int bestVal = evaluateValues(values,pastData);
  int bestCode[9] = {0,0,0,0,0,0,0,0,0};

  int valueChangeCode[9] = {0,0,0,0,0,0,0,0,0};
  int valuesCopy[3][3][3];
  //copyValues(valuesCopy,values);
  int i = 0;
  while (incrementBaseThree(valueChangeCode,9)){
    copyValues(valuesCopy,values);
    applyChange(valuesCopy,valueChangeCode);
    int evaluation = evaluateValues(valuesCopy,pastData);
    if (evaluation > bestVal) {
      bestVal = evaluation;
      copyChangeCode(bestCode,valueChangeCode);
    }
    i++;
  }
  applyChange(values,bestCode);
  //printf("the best values I found had a score of: %d\n", bestVal);
}

int evaluateValues(int values[3][3][3], int data[pastLooking]){

  int score = 0;
  int wouldBeMove;
  for (int i = 0; i < 17; i++){
    int tempMoves[3] = {data[i], data[i+1], data[i+2]};
    wouldBeMove = makeMove(values, tempMoves);
    if ( wouldBeMove == (data[i+3] + 1) % 3 ){//if the computer move would have beaten the user move
      score++;
    } else {//this method does not like ties. Maybe not the best. TODO test having ties be worth nothing
      score --;
    }
  }
  return score;

}

int incrementBaseThree(int number[], int length){//the return value is 1 if successfull, and 0 if not. this happens when you try and increment an all two's array

  //NOTE: number[0] is the least significant digit
  int i = 0;
  int carry = 1;
  while (carry) {
    number[i]++;
    if (number[i]==3){
      number[i] = 0;
    } else {
      carry = 0;
    }
    i++;
    if (i == length) {
      if (carry) return 0;
    }
  }
  return 1;
}

int main(){
  int goForAnother = 1;

  /*  evaluateRecentMoves is:
   *  [move][pieceMoved][valueForPiece]
   */
  int evaluateRecentMoves[3][3][3] = {
    {
      {0,0,0},
      {0,0,0},
      {0,0,0}
    },
    {
      {0,0,0},
      {0,0,0},
      {0,0,0}
    },
    {
      {0,0,0},
      {0,0,0},
      {0,0,0}
    }
  };
  int pastMoves[3] = {0,1,2};
  int extendedPastMoves[pastLooking];
  char userMove[1];
  int userMoveInt;

  int userMovesTaken = 0;

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

    updateArray(pastMoves,userMoveInt,3);
    updateArray(extendedPastMoves,userMoveInt,pastLooking);

    if (userMovesTaken > pastLooking){
      hillClimb(evaluateRecentMoves,extendedPastMoves);
    }

    userMovesTaken++;
  }
  return 0;
}
