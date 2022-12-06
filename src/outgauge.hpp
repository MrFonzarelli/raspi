#ifndef OUTGAUGE_HPP
#define OUTGAUGE_HPP

struct OutGauge
{
    unsigned time;
    char car[4];
    unsigned short flags;
    char gear;
    char plid;
    float speed;    // m/s or a thousandth of a mile/s
    float airspeed; // m/s or a thousandth of a mile/s
    float rpm;
    float turbo;
    float engTemp;
    float fuel;
    float fuel_remaining;
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

#endif