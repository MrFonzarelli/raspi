
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>

#define BUFSIZE 96

int pin1 = 15;
int pin2 = 16;
int pin3 = 1;
int pin4 = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 10;
int pin8 = 11;

enum eSystemEvent
{
    Reverse_Event,
    Neutral_Event,
    First_Event,
    Second_Event,
    Third_Event,
    Fourth_Event,
    Fifth_Event,
    Sixth_Event
};

ReverseHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, LOW);
    return 0;
}

NeutralHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 1;
}

FirstHandler(void)
{
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 2;
}

SecondHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, LOW);
    return 3;
}

ThirdHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 4;
}

FourthHandler(void)
{ 
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 5;
}

FifthHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 6;
}

SixthHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 7;
}

int main(int argc, char **argv)
{
  wiringPiSetup();
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
    
  int c;
  
  while(TRUE){
  printf("7 segment matrix test");
  printf("Gears indexed from reverse upwards (Index 0 - 7)");
  printf("Gear to display: ");
  
  c = getchar();
  while(c < 0 || c > 7) {
    printf("Gears indexed from reverse upwards (Index 0 - 7)");
    printf("Gear to display: ");
    c = getchar();
  }
     
    switch(c)
        {
        case 0:
        {
            ReverseHandler();
        }
        break;
        case 1:
        {
            NeutralHandler();
        }
        break;
        case 2:
        {
            FirstHandler();
        }
        break;
        case 3:
        {
            SecondHandler();
        }
        break;
        case 4:
        {
            ThirdHandler();
        }
        break;
        case 5:
        {
            FourthHandler();
        }
        break;
        case 6:
        {
            FifthHandler();
        }
        break;
        case 7:
        {
            SixthHandler();
        }
        break;
        default:
            break;
        }
  
  }
  return EXIT_SUCCESS;
  
}
