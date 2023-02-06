#ifndef OUTGAUGE_HPP
#define OUTGAUGE_HPP

struct OutGauge
{
    struct DashLights
    {
        bool shiftLight;
        bool lowBeam;
        bool highBeam;
        bool parkBrake;
        bool fogLight;
        bool tractionControl;
        bool signalLeft;
        bool signalRight;
        bool oilWarning;
        bool engineRunning;
        bool abs;
        bool hazardLight;
    };

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

    DashLights getDashLights();
};

struct RTCarInfo
{
    char identifier;
    int size;

    float speed_Kmh;
    float speed_Mph;
    float speed_Ms;

    bool isAbsEnabled;
    bool isAbsInAction;
    bool isTcInAction;
    bool isTcEnabled;
    bool isInPit;
    bool isEngineLimiterOn;

    float accG_vertical;
    float accG_horizontal;
    float accG_frontal;

    int lapTime;
    int lastLap;
    int bestLap;
    int lapCount;

    float gas;
    float brake;
    float clutch;
    float engineRPM;
    float steer;
    int gear;
    float cgHeight;
    float wheelAngularSpeed[4];
    float slipAngle[4];
    float slipAngle_ContactPatch[4];
    float slipRatio[4];
    float tyreSlip[4];
    float ndSlip[4];
    float load[4];
    float Dy[4];
    float Mz[4];
    float tyreDirtyLevel[4];
    float camberRAD[4];
    float tyreRadius[4];
    float tyreLoadedRadius[4];
    float suspensionHeight[4];
    float carPositionNormalized;
    float carSlope;
    float carCoordinates[3];
};

#endif