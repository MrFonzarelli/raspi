// includes
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
#include <fstream>
#include <thread>
#include <mutex>
#include <cmath>
#include <signal.h>

// definitions
#define PIN1 15         // A
#define PIN2 16         // B
#define PIN3 1          // C
#define PIN4 4          // D
#define PIN5 5          // E
#define PIN6 6          // F
#define PIN7 10         // G
#define PIN8 11         // DP
#define PIN9 31         // 3 digit -- A
#define PIN10 26        // 3 digit -- B
#define PIN11 27        // 3 digit -- C
#define PIN12 28        // 3 digit -- D
#define PIN13 29        // 3 digit -- E
#define PIN14 25        // 3 digit -- F
#define PIN15 24        // 3 digit -- G
#define PIN16 23        // 3 digit -- DP
#define PIN_BUTTON 12   // Cycle display button
#define PIN_RESET_ODO 8 // Reset odometer button
#define PIN_DIG1 0      // 3 digit -- dig1
#define PIN_DIG2 2      // 3 digit -- dig2
#define PIN_DIG3 3      // 3 digit -- dig3
#define WAIT 3          // 3 digit display -- delay per digit

#define ODOMETER_FILENAME "delete-to-reset-odometer"

#define DISPLAY_STATE_COUNT 8

// classes
enum class DisplayState
{
    Speed = 0,
    TurboPressure = 1,
    CurrentFuelConsumption = 2,
    AverageFuelConsumption = 3,
    TripOdometer = 4,
    Odometer = 5,
    EngineTemp = 6,
    OilTemp = 7
};

struct outGauge
{
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

std::mutex tripleDigitMutex;
std::mutex singleDigitMutex;

int des_gear = 1;
int cur_gear = 0;
int speed;
int pressure;
int engineTemp;
int oilTemp;
int oilPressure;
float trip_odometer;
int odometer;
double fuelConsumption;
double fuelConsumption_avg;
double fuel_burned;
int dist;
double fuel_old;
unsigned dashLights;
unsigned dashLights_old;
DisplayState displayState = DisplayState::Speed;

void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int ReverseHandler(void)
{
    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN3, LOW);
    digitalWrite(PIN4, LOW);
    digitalWrite(PIN5, HIGH);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, HIGH);
    return 0;
}

int NeutralHandler(void)
{
    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, LOW);
    digitalWrite(PIN5, HIGH);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, HIGH);
    return 1;
}

int FirstHandler(void)
{
    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, LOW);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, LOW);
    return 2;
}

int SecondHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, LOW);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, HIGH);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, HIGH);
    return 3;
}

int ThirdHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, HIGH);
    return 4;
}

int FourthHandler(void)
{
    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, LOW);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, HIGH);
    digitalWrite(PIN7, HIGH);
    return 5;
}

int FifthHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, HIGH);
    digitalWrite(PIN7, HIGH);
    return 6;
}

int SixthHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, HIGH);
    digitalWrite(PIN6, HIGH);
    digitalWrite(PIN7, HIGH);
    return 7;
}

int SeventhHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, LOW);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, LOW);
    return 8;
}

int EighthHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, HIGH);
    digitalWrite(PIN6, HIGH);
    digitalWrite(PIN7, HIGH);
    return 9;
}

int NinethHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, HIGH);
    digitalWrite(PIN7, HIGH);
    return 10;
}

int ZeroHandler(void)
{
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN3, HIGH);
    digitalWrite(PIN4, HIGH);
    digitalWrite(PIN5, HIGH);
    digitalWrite(PIN6, HIGH);
    digitalWrite(PIN7, LOW);
    return 11;
}

int FirstHandlerTri(void)
{
    digitalWrite(PIN9, LOW);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, LOW);
    return 1;
}

int SecondHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, HIGH);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, HIGH);
    return 2;
}

int ThirdHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, HIGH);
    return 3;
}

int FourthHandlerTri(void)
{
    digitalWrite(PIN9, LOW);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN15, HIGH);
    return 4;
}

int FifthHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, LOW);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN15, HIGH);
    return 5;
}

int SixthHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, LOW);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, HIGH);
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN15, HIGH);
    return 6;
}

int SeventhHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, LOW);
    return 7;
}

int EighthHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, HIGH);
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN15, HIGH);
    return 8;
}

int NinethHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN15, HIGH);
    return 9;
}

int ZeroHandlerTri(void)
{
    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN13, HIGH);
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN15, LOW);
    return 0;
}

int MinusHandlerTri(void)
{
    digitalWrite(PIN9, LOW);
    digitalWrite(PIN10, LOW);
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, HIGH);
    return 0;
}

int singleDigitOutput(int state)
{
    switch (state)
    {
    case 0:
    {
        cur_gear = ReverseHandler();
        break;
    }
    case 1:
    {
        cur_gear = NeutralHandler();
        break;
    }
    case 2:
    {
        cur_gear = FirstHandler();
        break;
    }
    case 3:
    {
        cur_gear = SecondHandler();
        break;
    }
    case 4:
    {
        cur_gear = ThirdHandler();
        break;
    }
    case 5:
    {
        cur_gear = FourthHandler();
        break;
    }
    case 6:
    {
        cur_gear = FifthHandler();
        break;
    }
    case 7:
    {
        cur_gear = SixthHandler();
        break;
    }
    case 8:
    {
        cur_gear = SeventhHandler();
        break;
    }
    case 9:
    {
        cur_gear = EighthHandler();
        break;
    }
    case 10:
    {
        cur_gear = NinethHandler();
        break;
    }
    default:
    {
        ZeroHandler();
        cur_gear = des_gear;
        break;
    }
    }
    return cur_gear;
}

int digitSelect(int num)
{
    switch (num)
    {
    case 0:
    {
        num = ZeroHandlerTri();
        break;
    }
    case 1:
    {
        num = FirstHandlerTri();
        break;
    }
    case 2:
    {
        num = SecondHandlerTri();
        break;
    }
    case 3:
    {
        num = ThirdHandlerTri();
        break;
    }
    case 4:
    {
        num = FourthHandlerTri();
        break;
    }
    case 5:
    {
        num = FifthHandlerTri();
        break;
    }
    case 6:
    {
        num = SixthHandlerTri();
        break;
    }
    case 7:
    {
        num = SeventhHandlerTri();
        break;
    }
    case 8:
    {
        num = EighthHandlerTri();
        break;
    }
    case 9:
    {
        num = NinethHandlerTri();
        break;
    }
    case 10:
    {
        num = MinusHandlerTri();
        break;
    }
    default:
    {
        num = NinethHandlerTri();
        break;
    }
    }
    return num;
}

int digParser(int num, DisplayState state)
{
    int dig;
    switch (state)
    {
    case DisplayState::Speed:
    {
        dig = speed;
        break;
    }
    case DisplayState::TurboPressure:
    {
        dig = pressure * 10;
        break;
    }
    case DisplayState::TripOdometer:
    {
        dig = trip_odometer * 10;
        break;
    }
    case DisplayState::Odometer:
    {
        dig = (odometer + trip_odometer) * 10;
        break;
    }
    case DisplayState::EngineTemp:
    {
        dig = engineTemp;
        break;
    }
    case DisplayState::OilTemp:
    {
        dig = oilTemp;
        break;
    }
    case DisplayState::CurrentFuelConsumption:
    {
        dig = fuelConsumption * 10;
        break;
    }
    case DisplayState::AverageFuelConsumption:
    {
        dig = fuelConsumption_avg * 10;
        break;
    }
    }

    switch (num)
    {
    case 1:
    {
        int dig1;
        dig1 = abs(dig) / 100 % 10;
        return dig1;
        break;
    }
    case 2:
    {
        int dig2;
        dig2 = abs(dig) / 10 % 10;
        return dig2;
        break;
    }
    case 3:
    {
        int dig3;
        dig3 = abs(dig) % 10;
        return dig3;
        break;
    }
    }
    return 0;
}

void tripleDigitOutput()
{
    int dig1;
    int dig2;
    int dig3;

    tripleDigitMutex.lock();
    DisplayState state = displayState;
    dig1 = digParser(1, state);
    dig2 = digParser(2, state); // lol
    dig3 = digParser(3, state);
    tripleDigitMutex.unlock();

    switch (state)
    {                                 // This decribes how to display each different displayState i.e. whether or not to use pin16(DP)
    case DisplayState::TurboPressure: // These describe the specific behaviour i.e. if the first digit going from the left is 0 skip displaying that digit
    {
        if (pressure < 0)
        {
            digitalWrite(PIN_DIG3, LOW);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG3, HIGH);
            digitalWrite(PIN_DIG2, LOW);
            digitSelect(dig2);
            digitalWrite(PIN16, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG2, HIGH);
            digitalWrite(PIN16, LOW);
            digitalWrite(PIN_DIG1, LOW);
            digitSelect(10);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG1, HIGH);
        }
        else
        {
            if (dig1 == 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                digitalWrite(PIN16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG2, HIGH);
                digitalWrite(PIN16, LOW);
            }
            else
            {
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                digitalWrite(PIN16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG2, HIGH);
                digitalWrite(PIN16, LOW);
                digitalWrite(PIN_DIG1, LOW);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG1, HIGH);
            }
        }
        break;
    }
    case DisplayState::TripOdometer:
    case DisplayState::Odometer:
    case DisplayState::CurrentFuelConsumption:
    case DisplayState::AverageFuelConsumption:
    {
        if (dig1 == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG3, LOW);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG3, HIGH);
            digitalWrite(PIN_DIG2, LOW);
            digitSelect(dig2);
            digitalWrite(PIN16, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG2, HIGH);
            digitalWrite(PIN16, LOW);
        }
        else
        {
            digitalWrite(PIN_DIG3, LOW);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG3, HIGH);
            digitalWrite(PIN_DIG2, LOW);
            digitSelect(dig2);
            digitalWrite(PIN16, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG2, HIGH);
            digitalWrite(PIN16, LOW);
            digitalWrite(PIN_DIG1, LOW);
            digitSelect(dig1);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG1, HIGH);
        }
        break;
    }
    default: // Anything that will be using all three digits without the DP pin should stay on default
    {
        if (dig1 == 0)
        {
            if (dig2 == 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, HIGH);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
                digitalWrite(PIN_DIG2, HIGH);
            }
        }
        else
        {
            digitalWrite(PIN_DIG3, LOW);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG3, HIGH);
            digitalWrite(PIN_DIG2, LOW);
            digitSelect(dig2);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG2, HIGH);
            digitalWrite(PIN_DIG1, LOW);
            digitSelect(dig1);
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT));
            digitalWrite(PIN_DIG1, HIGH);
        }
        break;
    }
    }
}

void doSingleDigitWork()
{
    while (true)
    {
        singleDigitMutex.lock();
        int gear = des_gear;
        singleDigitMutex.unlock();
        singleDigitOutput(gear);
    }
}

void doTripleDigitWork()
{
    while (true)
    {
        tripleDigitOutput();
    }
}

void read_odometer()
{
    std::ifstream odo_file(ODOMETER_FILENAME);
    if (odo_file.good())
    {
        odo_file >> odometer;
    }
    else
    {
        odometer = 0;
    }
    odo_file.close();
}

void write_odometer()
{
    std::ofstream odo_file(ODOMETER_FILENAME);
    odo_file << trip_odometer + odometer;
    odo_file.close();
}

void doButtonWork()
{
    int des_buttonState = 0;
    int last_buttonState = 0;
    while (true)
    {
        des_buttonState = digitalRead(PIN_BUTTON);
        if (last_buttonState != des_buttonState)
        {
            if (last_buttonState == 0)
            {
                tripleDigitMutex.lock();
                displayState = (DisplayState)(((int)displayState + 1) % DISPLAY_STATE_COUNT);
                tripleDigitMutex.unlock();
            }
            last_buttonState = des_buttonState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void doResetOdoButtonWork()
{
    int des_ResetOdoButtonState = 0;
    int last_ResetOdoButtonState = 0;
    while (true)
    {
        des_ResetOdoButtonState = digitalRead(PIN_RESET_ODO);
        if (last_ResetOdoButtonState != des_ResetOdoButtonState)
        {
            if (last_ResetOdoButtonState == 0)
            {
                tripleDigitMutex.lock();
                printf("trip_odometer: %d\n", trip_odometer);
                printf("odometer: %d\n", odometer);
                odometer += trip_odometer;
                printf("new_odometer: %d\n", odometer);
                trip_odometer = 0;
                printf("new_trip_odometer: %d\n", trip_odometer);
                write_odometer();
                tripleDigitMutex.unlock();
            }
            last_ResetOdoButtonState = des_ResetOdoButtonState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

double calcFuelConsumption(double fuelAmount, double fuelAmount_old, double distance)
{
    if (fuelAmount_old < fuelAmount || distance == 0)
    {
        fuel_old = fuelAmount;
        return 0;
    }
    else
    {
        double res = (100 / distance) * (fuelAmount_old - fuelAmount);
        fuel_old = fuelAmount;
        return res;
    }
}

double calcAverageFuelConsumption(double fuelAmount, double fuelAmount_old, double fuelBurnedForConsumption, double distance)
{
    if (fuelAmount_old < fuelAmount || distance == 0)
    {
        fuel_burned = 0;
        return 0;
    }
    else
    {
        double res = (100 / distance) * (fuelBurnedForConsumption + fuelAmount_old - fuelAmount);
        fuel_burned += fuelAmount_old - fuelAmount;
        return res;
    }
}

void odo_signal_handler(int)
{
    write_odometer();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    signal(SIGINT, odo_signal_handler);
    signal(SIGTERM, odo_signal_handler);
    signal(SIGHUP, odo_signal_handler);
    read_odometer();

    struct sockaddr_in myaddr, clientaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    wiringPiSetup();
    pinMode(PIN1, OUTPUT);
    pinMode(PIN2, OUTPUT);
    pinMode(PIN3, OUTPUT);
    pinMode(PIN4, OUTPUT);
    pinMode(PIN5, OUTPUT);
    pinMode(PIN6, OUTPUT);
    pinMode(PIN7, OUTPUT);
    pinMode(PIN8, OUTPUT);
    pinMode(PIN9, OUTPUT);
    pinMode(PIN10, OUTPUT);
    pinMode(PIN11, OUTPUT);
    pinMode(PIN12, OUTPUT);
    pinMode(PIN13, OUTPUT);
    pinMode(PIN14, OUTPUT);
    pinMode(PIN15, OUTPUT);
    pinMode(PIN16, OUTPUT);
    pinMode(PIN_DIG1, OUTPUT);
    pinMode(PIN_DIG2, OUTPUT);
    pinMode(PIN_DIG3, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RESET_ODO, INPUT);
    digitalWrite(PIN_DIG1, HIGH);
    digitalWrite(PIN_DIG2, HIGH);
    digitalWrite(PIN_DIG3, HIGH);

    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN3, LOW);
    digitalWrite(PIN4, LOW);
    digitalWrite(PIN5, LOW);
    digitalWrite(PIN6, LOW);
    digitalWrite(PIN7, LOW);
    digitalWrite(PIN8, LOW);

    digitalWrite(PIN9, LOW);
    digitalWrite(PIN10, LOW);
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, LOW);
    digitalWrite(PIN16, LOW);

    digitalWrite(PIN_DIG1, LOW);
    digitalWrite(PIN_DIG2, LOW);
    digitalWrite(PIN_DIG3, LOW);

    digitalWrite(PIN9, HIGH);
    digitalWrite(PIN1, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN10, HIGH);
    digitalWrite(PIN2, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN11, HIGH);
    digitalWrite(PIN3, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN12, HIGH);
    digitalWrite(PIN4, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN13, HIGH);
    digitalWrite(PIN5, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN14, HIGH);
    digitalWrite(PIN6, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    digitalWrite(PIN9, LOW);
    digitalWrite(PIN1, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN10, LOW);
    digitalWrite(PIN2, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN3, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN4, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN5, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN6, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    digitalWrite(PIN_DIG1, HIGH);
    digitalWrite(PIN_DIG2, HIGH);
    digitalWrite(PIN_DIG3, HIGH);

    for (int i = 0; i < 70; i++)
    {
        digitalWrite(PIN_DIG2, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_DIG2, HIGH);

        digitalWrite(PIN_DIG1, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_DIG1, HIGH);
    }

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(PIN_DIG3, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        digitalWrite(PIN_DIG3, HIGH);

        digitalWrite(PIN_DIG2, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        digitalWrite(PIN_DIG2, HIGH);

        digitalWrite(PIN_DIG1, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        digitalWrite(PIN_DIG1, HIGH);
    }

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(PIN_DIG3, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_DIG3, HIGH);

        digitalWrite(PIN_DIG2, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_DIG2, HIGH);
    }

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(PIN_DIG3, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_DIG3, HIGH);

        digitalWrite(PIN_DIG2, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_DIG2, HIGH);
    }

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(PIN_DIG3, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        digitalWrite(PIN_DIG3, HIGH);
    }

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(PIN_DIG3, LOW);
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        digitalWrite(PIN_DIG3, HIGH);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    digitalWrite(PIN9, LOW);
    digitalWrite(PIN10, LOW);
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN12, LOW);
    digitalWrite(PIN13, LOW);
    digitalWrite(PIN14, LOW);
    digitalWrite(PIN15, LOW);

    std::thread singleDigitThread(doSingleDigitWork);
    std::thread tripleDigitThread(doTripleDigitWork);
    std::thread buttonThread(doButtonWork);
    // std::thread resetOdoButtonThread(doResetOdoButtonWork);

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(4444);
    addr_len = sizeof(myaddr);
    int sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sfd == -1)
    {
        printf("socket err \n");
        return 0;
    }
    int resu = bind(sfd, (struct sockaddr *)&myaddr, sizeof(struct sockaddr));
    if (resu == -1)
    {
        printf("bind err \n");
        return 0;
    }

    auto old_time = std::chrono::high_resolution_clock::now();

    while (true)
    {
        int res = recvfrom(sfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&addr_len);
        if (res == -1)
        {
            printf("recv err \n");
            return 0;
        }
        else
        {
            outGauge *s = (outGauge *)buffer;
            dashLights = s->showLights;
            if (dashLights != dashLights_old)
            {
                printBits(sizeof(dashLights), &dashLights);
                dashLights_old = dashLights;
            }

            double speed_to_count = s->speed;
            if (speed_to_count < 0.15)
            {
                speed_to_count = 0;
            }
            tripleDigitMutex.lock();
            singleDigitMutex.lock();
            auto new_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_delta = new_time - old_time;
            trip_odometer += time_delta.count() * speed_to_count / 1000;
            fuelConsumption = calcFuelConsumption(s->fuel_remaining, fuel_old, (trip_odometer - dist));
            fuelConsumption_avg = calcAverageFuelConsumption(s->fuel_remaining, fuel_old, fuel_burned, trip_odometer);
            speed = lround(s->speed * 3.6);
            pressure = lround(s->turbo);
            dist = trip_odometer;
            engineTemp = lround(s->engTemp);
            oilTemp = lround(s->oilTemp);
            des_gear = (int)s->gear;
            printf("Fuel cons: %f\n", fuelConsumption);
            printf("Fuel cons_avg: %f\n", fuelConsumption_avg);
            singleDigitMutex.unlock();
            tripleDigitMutex.unlock();
            old_time = new_time;
        }
    }

    return 0;
}
