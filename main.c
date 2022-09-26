
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

typedef enum
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7
} eSystemState;

typedef enum
{
    Reverse_Event,
    Neutral_Event,
    First_Event,
    Second_Event,
    Third_Event,
    Fourth_Event,
    Fifth_Event,
    Sixth_Event
} eSystemEvent;

eSystemState ReverseHandler(void)
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

eSystemState NeutralHandler(void)
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

eSystemState FirstHandler(void)
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

eSystemState SecondHandler(void)
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

eSystemState ThirdHandler(void)
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

eSystemState FourthHandler(void)
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

eSystemState FifthHandler(void)
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

eSystemState SixthHandler(void)
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
  pinmode(pin1, OUTPUT);
  pinmode(pin2, OUTPUT);
  pinmode(pin3, OUTPUT);
  pinmode(pin4, OUTPUT);
  pinmode(pin5, OUTPUT);
  pinmode(pin6, OUTPUT);
  pinmode(pin7, OUTPUT);
  pinmode(pin8, OUTPUT);
    
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
   
    eSystemState eNextState = c;
    eSystemEvent eNewEvent;
  
    switch(eNextState)
        {
        case 0:
        {
            if(Reverse_event == eNewEvent)
            {
                eNextState = ReverseHandler();
            }
        }
        break;
        case 1:
        {
            if(Neutral_event == eNewEvent)
            {
                eNextState = NeutralHandler();
            }
        }
        break;
        case 2:
        {
            if(First_Event == eNewEvent)
            {
                eNextState = FirstHandler();
            }
        }
        break;
        case 3:
        {
            if(Second_Event == eNewEvent)
            {
                eNextState = SecondHandler();
            }
        }
        break;
        case 4:
        {
            if(Third_Event == eNewEvent)
            {
                eNextState = ThirdHandler();
            }
        }
        break;
        case 5:
        {
            if(Fourth_Event == eNewEvent)
            {
                eNextState = FourthHandler();
            }
        }
        break;
        case 6:
        {
            if(Fifth_Event == eNewEvent)
            {
                eNextState = FifthHandler();
            }
        }
        break;
        case 7:
        {
            if(Sixth_Event == eNewEvent)
            {
                eNextState = SixthHandler();
            }
        }
        break;
        default:
            break;
        }
  
  }
  return EXIT_SUCCESS;
  
}
