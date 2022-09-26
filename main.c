
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <wiringPi.h>

int pin1 = 15;
int pin2 = 16;
int pin3 = 1;
int pin4 = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 10;
int pin8 = 11;

struct outGauge{
    unsigned time;
    char car[4];
    unsigned short flags;
    char gear;
    char plid;
    float speed;
    float rpm;
    float turbo;
    float engTemp;
    float fuel;
    float oilPressure;
    float oilTemp;
    unsigned dashLights;
    unsigned showLights;
    float throttle;
    float brake;
    float clutch;
    char display1[16];
    char display2[16];
    int id;
};

int ReverseHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, LOW);
    return 0;
}

int NeutralHandler(void)
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

int FirstHandler(void)
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

int SecondHandler(void)
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

int ThirdHandler(void)
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

int FourthHandler(void)
{ 
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 5;
}

int FifthHandler(void)
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

int SixthHandler(void)
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

int SeventhHandler(void)
{
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 8;
}

int EighthHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 9;
}

int NinethHandler(void)
{
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 10;
}

int ZeroHandler(void)
{
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 11;
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
    
  int des_state = 1;
  int cur_state = 0;
  char message[96];
  char target_addr = inet_addr("169.254.105.216");
    
  printf("7 segment matrix test \n");
  printf("Gears indexed from reverse upwards (Index 0 - 7) \n");
  
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
  if (sockfd == -1)
  {
    printf("socket err \n");
  }
  int res = bind(sockfd, (struct sockaddr *)&target_addr, sizeof(target_addr));
  if (res == -1)
  {
    printf("bind err \n");
    close(sockfd);
  }
    
  do {
    int res = recvfrom(sockfd, message, 96, 0, (struct sockaddr *)&target_addr, sizeof(target_addr));
    if (res == -1){
        printf("recvfrom err \n");
    } else {
        outGauge *s = (outGauge *)message;
        des_state = (int)s->gear;
        if (des_state != cur_state){
            switch(des_state)
                {
                case 0:
                {
                    cur_state = ReverseHandler();
                }
                break;
                case 1:
                {
                    cur_state = NeutralHandler();
                }
                break;
                case 2:
                {
                    cur_state = FirstHandler();
                }
                break;
                case 3:
                {
                    cur_state = SecondHandler();
                }
                break;
                case 4:
                {
                    cur_state = ThirdHandler();
                }
                break;
                case 5:
                {
                    cur_state = FourthHandler();
                }
                break;
                case 6:
                {
                    cur_state = FifthHandler();
                }
                break;
                case 7:
                {
                    cur_state = SixthHandler();
                }
                break;
                case 8:
                {
                    cur_state = SeventhHandler();
                }
                break;
                case 9:
                {
                    cur_state = EighthHandler();
                }
                break;
                case 10:
                {
                    cur_state = NinethHandler();
                }
                break;
                default:
                    {
                        ZeroHandler();
                        cur_state = des_state;
                    }
                    break;
                }
        printf("State changed to %d", cur_state);
        printf("\n");
        }
    }
  } while(curr_state !=-1);
  
  close(sockfd);
  return 0;
  
}
