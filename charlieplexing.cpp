#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <wiringPi.h>

int state;
int pin1 = 1;
int pin2 = 16;
int pin3 = 15;

int ledSelect(int state) {
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
        case 2:
        {
            pinMode(pin1, OUTPUT);
            pinMode(pin2, INPUT);
            pinMode(pin3, OUTPUT);
            digitalWrite (pin1, LOW);
            digitalWrite (pin3, HIGH);
        }
        break;
        case 3:
        {
            pinMode(pin1, OUTPUT);
            pinMode(pin2, INPUT);
            pinMode(pin3, OUTPUT);
            digitalWrite (pin1, HIGH);
            digitalWrite (pin3, LOW);
        }
        break;
        case 4:
        {
            pinMode(pin1, OUTPUT);
            pinMode(pin2, OUTPUT);
            pinMode(pin3, INPUT);
            digitalWrite (pin1, LOW);
            digitalWrite (pin2, HIGH);
        }
        break;
        case 5:
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
  wiringPiSetup();
  state = 1;
  do {
    ledSelect(state);
    if (state == 5) {
      state = 0;
    } else {
      state = state + 2;
    }
  } while (state < 6);
  return 0;
}
