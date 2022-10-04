#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <wiringPi.h>
#include <iostream>

int state;
int pin1 = 1;
int pin2 = 16;
int pin3 = 15;
int pin4 = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 10;
int pin8 = 11;
int pin9 = 31;

int ledSelect1(int state) {
    switch(state)
        {
        case 0:
        {
            pinMode(pin1, INPUT);
            pinMode(pin2, OUTPUT);
            pinMode(pin3, OUTPUT);
            digitalWrite (pin2, LOW);
            digitalWrite (pin3, HIGH);
        }
        break;
        case 1:
        {
            pinMode(pin1, INPUT);
            pinMode(pin2, OUTPUT);
            pinMode(pin3, OUTPUT);
            digitalWrite (pin2, HIGH);
            digitalWrite (pin3, LOW);
        }
        break;
    }
    return state;
}

int ledSelect2(int state) {
    switch(state)
    {
    case 0:
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, INPUT);
        pinMode(pin3, OUTPUT);
        digitalWrite (pin1, LOW);
        digitalWrite (pin3, HIGH);
    }
    break;
    case 1:
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, INPUT);
        pinMode(pin3, OUTPUT);
        digitalWrite (pin1, HIGH);
        digitalWrite (pin3, LOW);
    }
    break;
    }
    return state;
}

int ledSelect3(int state) {
    switch(state)
    {
    case 0:
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, INPUT);
        digitalWrite (pin1, LOW);
        digitalWrite (pin2, HIGH);
    }
    break;
    case 1:
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, INPUT);
        digitalWrite (pin1, HIGH);
        digitalWrite (pin2, LOW);
    }
    break;
    }
    return state;
}

int main(int argc, char **argv) {
  int input;
  state = 0
  wiringPiSetup();
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  pinMode(pin6, INPUT);
  pinMode(pin7, INPUT);
  pinMode(pin8, INPUT);
  pinMode(pin9, INPUT);
    do {
        ledSelect1(digitalRead(pin4));
        ledSelect2(digitalRead(pin6));
        ledSelect3(digitalRead(pin8));
    } while (state != -5);
  return 0;
}
