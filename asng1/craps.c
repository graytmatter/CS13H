#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// #include <ctype.h>
#define SIDES 6
#define BUF_SIZE 20


int rollDie() { return random() % 6+1; }

int main(int argc, char const *argv[])
{
  int bank = 1000;
  int bet;
  char buffer[BUF_SIZE];
  int pass = 1;
  int die1;
  int die2;
  int roll;
  int point;
  char words[11][7] = {"Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve"};
  printf("%s\n", "Roll them bones! ");
  do
  {
    printf("%s $%i %s\n", "You have",bank,"in the bank.");
    printf("%s", "What's your bet? ");
    fgets(buffer, 10, stdin);
    bet = atoi(buffer);
    if(bet > 0 && bet <= bank){
      die1 = rollDie();
      die2 = rollDie();
      roll = die1+die2;
      printf("Easy %s (%i,%i) ... ",words[roll-2],die1,die2);
      if(pass){ //if they are making a pass no pass roll
        if(roll == 7 || roll == 11){
          printf("%s\n", "Pass Win!!");
          bank += bet;
        } else if(roll == 1 || roll == 2 || roll == 12){
          printf("%s\n", "Pass Loss!!");
          bank -= bet;
        } else {
          printf("%s\n", "Point Set!!");
          pass = 0; //now they are making point rolls
          point = roll;
        }
      }else{ //if they are making a point roll
        if(roll == point){
          printf("%s\n", "Point Win!!");
          bank += bet;
          pass= 1; //make another pass roll.
        }else if(roll == 7){
          printf("%s\n", "Point Loss!!");
          bank -= bet;
          pass = 1;
        }else{
          printf("%s\n","Roll again!!");
        }
      }
    }else if(bet != 0){
      printf("%s\n", "You can't bet that much!" );
    }
    if(bank == 0){
      printf("%s $%i %s\n", "You have",bank,"in the bank.");
      printf("%s\n", "Fat Tony's gonna have to ask you to come to the back room with him.");
      bet = 0;
    }
  }while(bet > 0);
  return 0;
}