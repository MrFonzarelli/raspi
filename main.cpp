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
#include <time.h>
#include <iostream>
#include <thread>
#include <mutex>

int pin1 = 15;  //A
int pin2 = 16;  //B
int pin3 = 1;   //C
int pin4 = 4;   //D
int pin5 = 5;   //E
int pin6 = 6;   //F
int pin7 = 10;  //G
int pin8 = 11;  //DP
int pin9 = 31;  //3 digit A
int pin10 = 26; //3 digit B
int pin11 = 27; //3 digit C
int pin12 = 28; //3 digit D
int pin13 = 29; //3 digit E
int pin14 = 25; //3 digit F
int pin15 = 24; //3 digit G
int pin16 = 23; //3 digit DP
int pinButton = 12;
int pindig1 = 0; //7 seg 3 digit dig1
int pindig2 = 2; //7 seg 3 digit dig2
int pindig3 = 3; //7 seg 3 digit dig3
int des_gear = 1;
int cur_gear = 0;
int speed;
int pressure;
int distance;
double dist;
int displayState = 0;
int cur_buttonState = 0;
int des_buttonState = 0;
int last_buttonState = 0;
double cur_rpm = 0;
double max_rpm = 1;
int max_gear;
int sfd;
int wait = 3;

std::mutex tripleDigitMutex;
std::mutex singleDigitMutex;

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
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 0;
}

int NeutralHandler(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 1;
}

int FirstHandler(void) {
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, LOW);
    return 2;
}

int SecondHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 3;
}

int ThirdHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, HIGH);
    return 4;
}

int FourthHandler(void) { 
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 5;
}

int FifthHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 6;
}

int SixthHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, HIGH);
    return 7;
}

int SeventhHandler(void) {
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, LOW);
    digitalWrite (pin5, LOW);
    digitalWrite (pin6, LOW);
    digitalWrite (pin7, LOW);
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
    digitalWrite (pin1, HIGH);
    digitalWrite (pin2, HIGH);
    digitalWrite (pin3, HIGH);
    digitalWrite (pin4, HIGH);
    digitalWrite (pin5, HIGH);
    digitalWrite (pin6, HIGH);
    digitalWrite (pin7, LOW);
    return 11;
}

int FirstHandlerTri(void) {
    digitalWrite (pin9, LOW);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, LOW);
    digitalWrite (pin13, LOW);
    digitalWrite (pin14, LOW);
    digitalWrite (pin15, LOW);
    return 1;
}

int SecondHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, LOW);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, HIGH);
    digitalWrite (pin14, LOW);
    digitalWrite (pin15, HIGH);
    return 2;
}

int ThirdHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, LOW);
    digitalWrite (pin14, LOW);
    digitalWrite (pin15, HIGH);
    return 3;
}

int FourthHandlerTri(void) { 
    digitalWrite (pin9, LOW);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, LOW);
    digitalWrite (pin13, LOW);
    digitalWrite (pin14, HIGH);
    digitalWrite (pin15, HIGH);
    return 4;
}

int FifthHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, LOW);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, LOW);
    digitalWrite (pin14, HIGH);
    digitalWrite (pin15, HIGH);
    return 5;
}

int SixthHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, LOW);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, HIGH);
    digitalWrite (pin14, HIGH);
    digitalWrite (pin15, HIGH);
    return 6;
}

int SeventhHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, LOW);
    digitalWrite (pin13, LOW);
    digitalWrite (pin14, LOW);
    digitalWrite (pin15, LOW);
    return 7;
}

int EighthHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, HIGH);
    digitalWrite (pin14, HIGH);
    digitalWrite (pin15, HIGH);
    return 8;
}

int NinethHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, LOW);
    digitalWrite (pin14, HIGH);
    digitalWrite (pin15, HIGH);
    return 9;
}

int ZeroHandlerTri(void) {
    digitalWrite (pin9, HIGH);
    digitalWrite (pin10, HIGH);
    digitalWrite (pin11, HIGH);
    digitalWrite (pin12, HIGH);
    digitalWrite (pin13, HIGH);
    digitalWrite (pin14, HIGH);
    digitalWrite (pin15, LOW);
    return 0;
}

int singleDigitOutput(int state){
    switch(state)
        {
        case 0:
        {
            cur_gear = ReverseHandler();
        }
        break;
        case 1:
        {
            cur_gear = NeutralHandler();
        }
        break;
        case 2:
        {
            cur_gear = FirstHandler();
        }
        break;
        case 3:
        {
            cur_gear = SecondHandler();
        }
        break;
        case 4:
        {
            cur_gear = ThirdHandler();
        }
        break;
        case 5:
        {
            cur_gear = FourthHandler();
        }
        break;
        case 6:
        {
            cur_gear = FifthHandler();
        }
        break;
        case 7:
        {
            cur_gear = SixthHandler();
        }
        break;
        case 8:
        {            
            cur_gear = SeventhHandler();
        }
        break;
        case 9:
        {
            cur_gear = EighthHandler();
        }
        break;
        case 10:
        {
            cur_gear = NinethHandler();
        }
        break;
        default:
        {
            ZeroHandler();
            cur_gear = des_gear;
        }
        break;
    }
    return cur_gear;
}

int digitSelect(int num) {
    switch(num)
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
        break;
    }
    return num;
}

int digParser(int num, int state) {
    int dig;
    switch(state) {
        case 0:
        {
            dig = speed;
        }
        break;
        case 1:
        {
            dig = pressure;
        }
        break;
        case 2:
        {
            dig = distance;
        }
        break;
    }
    switch(num) {
        case 1:
        {
            int dig1;
            dig1 = dig / 100 % 10;
            return dig1;
        }
        break;
        case 2:
        {
            int dig2;
            dig2 = dig / 10 % 10;
            return dig2;
        }
        break;
        case 3:
        {
            int dig3;
            dig3 = dig % 10;
            return dig3;
        }
        break;
    }
    return 0;
}

void tripleDigitOutput() {
    int dig1;
    int dig2;
    int dig3;
    int state;

    tripleDigitMutex.lock();
    state = displayState;
    dig1 = digParser(1, state);
    dig2 = digParser(2, state);
    dig3 = digParser(3, state);
    tripleDigitMutex.unlock();

    switch(state) {
        case 0:
        {
            if (dig1 == 0) {
                if (dig2 == 0) {
                    digitalWrite(pindig3, LOW);   
                    digitSelect(dig3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                    digitalWrite(pindig3, HIGH);
                } else {
                    digitalWrite(pindig3, LOW);   
                    digitSelect(dig3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                    digitalWrite(pindig3, HIGH);           
                    digitalWrite(pindig2, LOW);
                    digitSelect(dig2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                    digitalWrite(pindig2, HIGH);            
                }
            } else {
                digitalWrite(pindig3, LOW);   
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig3, HIGH);       
                digitalWrite(pindig2, LOW);   
                digitSelect(dig2);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig2, HIGH);       
                digitalWrite(pindig1, LOW);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig1, HIGH);                
            }
        }
        break;
        case 1:
        {
            if (dig1 == 0) {
                digitalWrite(pindig3, LOW);   
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig3, HIGH);           
                digitalWrite(pindig2, LOW);
                digitSelect(dig2);
                digitalWrite(pin16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig2, HIGH);  
                digitalWrite(pin16, LOW);          
            } else {
                digitalWrite(pindig3, LOW);   
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig3, HIGH);       
                digitalWrite(pindig2, LOW);   
                digitSelect(dig2);
                digitalWrite(pin16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig2, HIGH); 
                digitalWrite(pin16, LOW);      
                digitalWrite(pindig1, LOW);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig1, HIGH);                
            }
        }
        break;
        case 2:
        {
            if (dig1 == 0) {
                digitalWrite(pindig3, LOW);   
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig3, HIGH);           
                digitalWrite(pindig2, LOW);
                digitSelect(dig2);
                digitalWrite(pin16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig2, HIGH);  
                digitalWrite(pin16, LOW);          
            } else {
                digitalWrite(pindig3, LOW);   
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig3, HIGH);       
                digitalWrite(pindig2, LOW);   
                digitSelect(dig2);
                digitalWrite(pin16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig2, HIGH); 
                digitalWrite(pin16, LOW);      
                digitalWrite(pindig1, LOW);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
                digitalWrite(pindig1, HIGH);                
            }
        }
        break;
    }
}

void doSingleDigitWork() {
        while (true) {
            singleDigitMutex.lock();
            int gear = des_gear;
            float cur = cur_rpm;
            float max = max_rpm;
            singleDigitMutex.unlock();
            singleDigitOutput(gear);
            if (cur/max >= 0.8) {
                if (gear == max_g) {
                } else {
                    if (cur/max >= 0.9) {
                       std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        digitalWrite (pin1, LOW);
                        digitalWrite (pin2, LOW);
                        digitalWrite (pin3, LOW);
                        digitalWrite (pin4, LOW);
                        digitalWrite (pin5, LOW);
                        digitalWrite (pin6, LOW);
                        digitalWrite (pin7, LOW);
                        ::this_thread::sleep_for(std::chrono::milliseconds(100)); 
                    } else {
                        std::this_thread::sleep_for(std::chrono::milliseconds(150));
                        digitalWrite (pin1, LOW);
                        digitalWrite (pin2, LOW);
                        digitalWrite (pin3, LOW);
                        digitalWrite (pin4, LOW);
                        digitalWrite (pin5, LOW);
                        digitalWrite (pin6, LOW);
                        digitalWrite (pin7, LOW);
                        std::this_thread::sleep_for(std::chrono::milliseconds(150));
                    }
                }
            }
        }
}

void doTripleDigitWork() {
    while (true) {
        tripleDigitOutput();
    }
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
  pinMode(pindig1, OUTPUT);
  pinMode(pindig2, OUTPUT);
  pinMode(pindig3, OUTPUT);
  pinMode(pinButton, INPUT);
  digitalWrite(pindig1, HIGH);
  digitalWrite(pindig2, HIGH);
  digitalWrite(pindig3, HIGH);
   
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

  std::thread singleDigitThread(doSingleDigitWork);
  std::thread tripleDigitThread(doTripleDigitWork);
    
  auto old_time = std::chrono::high_resolution_clock::now();
    
  while (true) {
    int res = recvfrom(sfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientaddr, (socklen_t*) &addr_len);
    if (res == -1) {
        printf("recv err \n");
        return 0;
    } else {
        des_buttonState = digitalRead(pinButton);
        if (last_buttonState != des_buttonState) {
            if (last_buttonState == 0) {
                if (cur_buttonState == 0) {
                    tripleDigitMutex.lock();
                    if (displayState == 2){
                        displayState = 0;
                    } else {
                        displayState += 1;
                    }
                    tripleDigitMutex.unlock();
                } else {
                    cur_buttonState = 0;
                }
            } else {
                last_buttonState = 0;
            }
            last_buttonState = des_buttonState;
        }
        outGauge *s = (outGauge *)buffer;
        des_gear = (int)s->gear;
        cur_rpm = s->rpm;
        if (max_gear <= des_gear) {
            if (max_rpm <= cur_rpm) {
                max_rpm = cur_rpm;
            }
            max_gear = des_gear;
        }
        double speed_to_count = s->speed;
        if (speed_to_count < 0.15) {
            speed_to_count = 0;
        }
        auto new_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_delta = new_time - old_time;
        dist += time_delta.count() * speed_to_count / 100;
        tripleDigitMutex.lock();
        singleDigitMutex.lock();
        speed = s->speed * 3.6;
        pressure = s->turbo * 10;
        distance = dist;
        singleDigitMutex.unlock();
        tripleDigitMutex.unlock();
        old_time = new_time;
    }
  }
  
  return 0;
  
}
