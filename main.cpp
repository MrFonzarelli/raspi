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

int pin1 = 15;
int pin2 = 16;
int pin3 = 1;
int pin4 = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 10;
int pin8 = 11;
int pin9 = 31;
int pin10 = 26;
int pin11 = 27;
int pin12 = 28;
int pin13 = 29;
int pin14 = 25;
int pin15 = 24;
int pin16 = 23;
int pin17 = 22;
int pindig1 = 14;
int pindig2 = 13;
int pindig3 = 12;
int des_state = 1;
int cur_state = 0;
int des_speed = 0;
int cur_speed;
int sfd;

struct outGauge {
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

int ReverseHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, LOW);
    return 0;
}

int NeutralHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 1;
}

int FirstHandler(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 2;
}

int SecondHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, LOW);
    return 3;
}

int ThirdHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 4;
}

int FourthHandler(void) { 
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 5;
}

int FifthHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 6;
}

int SixthHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 7;
}

int SeventhHandler(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 8;
}

int EighthHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 9;
}

int NinethHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 10;
}

int ZeroHandler(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 11;
}

int FirstHandlerTri(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 1;
}

int SecondHandlerTri(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, LOW);
    return 2;
}

int ThirdHandlerTri(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 3;
}

int FourthHandlerTri(void) { 
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 4;
}

int FifthHandlerTri(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 5;
}

int SixthHandlerTri(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 6;
}

int SeventhHandlerTri(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 7;
}

int EighthHandlerTri(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 8;
}

int NinethHandlerTri(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 9;
}

int ZeroHandlerTri(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 0;
}

int singleDigitOutput(int state){
    switch(state)
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
    return cur_state;
}

int tripleDigitOutput(int num) {
    int dig1;
    int dig2;
    int dig3;
    dig1 = num / 100 % 10;
    dig2 = num / 10 % 10;
    dig3 = num % 10;
    digitalWrite(pindig3, LOW);
    digitSelect(dig1);
    digitalWrite(pindig1, HIGH);
    digitalWrite(pindig1, LOW);
    digitSelect(dig2);
    digitalWrite(pindig2, HIGH);
    digitalWrite(pindig2, LOW);
    digitSelect(dig3);
    digitalWrite(pindig3, HIGH);
    cur_speed = des_speed;
    //printf("Speed: %d hundreds %d tens %d units\n", dig1, dig2, dig3);
    return cur_speed;
}

void digitSelect(int num) {
    switch(num) {
        {
        case 0:
        {
            num = ZeroHandlerTri();
        }
        break;
        case 1:
        {
            num = FirstHandlerTri();
        }
        break;
        case 2:
        {
            num = SecondHandlerTri();
        }
        break;
        case 3:
        {
            num = ThirdHandlerTri();
        }
        break;
        case 4:
        {
            num = FourthHandlerTri();
        }
        break;
        case 5:
        {
            num = FifthHandlerTri();
        }
        break;
        case 6:
        {
            num = SixthHandlerTri();
        }
        break;
        case 7:
        {
            num = SeventhHandlerTri();
        }
        break;
        case 8:
        {
            num = EighthHandlerTri();
        }
        break;
        case 9:
        {
            num = NinethHandlerTri();
        }
        break;
        default:
        {
            num = NinethHandlerTri();
        }
    }
    return num;
}

int main(int argc, char **argv) {
  struct sockaddr_in myaddr, clientaddr;
  memset(&myaddr, 0, sizeof(struct sockaddr_in));
  memset(&clientaddr, 0, sizeof(struct sockaddr_in));
  socklen_t addr_len = sizeof(struct sockaddr_in);
  char buffer[128];
  memset(buffer, 0, sizeof(buffer));
    
  wiringPiSetup();
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);
  pinMode(pin12, OUTPUT);
  pinMode(pin13, OUTPUT);
  pinMode(pin14, OUTPUT);
  pinMode(pin15, OUTPUT);
  pinMode(pin16, OUTPUT);
  pinMode(pin17, OUTPUT);
  pinMode(pindig1, OUTPUT);
  pinMode(pindig2, OUTPUT);
  pinMode(pindig3, OUTPUT);
   
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(4444);
  addr_len = sizeof(myaddr);
  sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sfd == -1) {
      printf("socket err \n");
      return 0;
  }
  int resu = bind(sfd, (struct sockaddr *) &myaddr, sizeof(struct sockaddr));
  if (resu == -1) {
    printf("connect err \n");
    return 0;
  }
    
  double distance_traveled = 0;
  auto old_time = std::chrono::high_resolution_clock::now();
    
  do {
    int res = recvfrom(sfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientaddr, (socklen_t*) &addr_len);
    if (res == -1) {
        printf("recv err \n");
        return 0;
    } else {
        outGauge *s = (outGauge *)buffer;
        des_state = (int)s->gear;
        des_speed = s->speed * 3.6;
        auto new_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_delta = new_time - old_time;
        double speed_to_count = s->speed;
        if (speed_to_count < 0.15) {
            speed_to_count = 0;
        }
        distance_traveled += time_delta.count() * speed_to_count / 1000;
        //printf("Distance traveled: %06.1lf km\n", distance_traveled);
        //if (des_state != cur_state) {
            //singleDigitOutput(des_state);
        //}
        //if (des_speed != cur_speed) {
            tripleDigitOutput(des_speed);    
        //}
        old_time = new_time;
    }
  } while(cur_state !=-1);
  
  return 0;
  
}
