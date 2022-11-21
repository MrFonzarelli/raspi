// includes
#include "display.hpp"
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
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_sum.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>

using namespace boost::accumulators;

// definitions
#define PIN1 15                    // A
#define PIN2 16                    // B
#define PIN3 1                     // C
#define PIN4 4                     // D
#define PIN5 5                     // E
#define PIN6 6                     // F
#define PIN7 10                    // G
#define PIN8 11                    // DP
#define PIN9 31                    // 3 digit -- A
#define PIN10 26                   // 3 digit -- B
#define PIN11 27                   // 3 digit -- C
#define PIN12 28                   // 3 digit -- D
#define PIN13 29                   // 3 digit -- E
#define PIN14 25                   // 3 digit -- F
#define PIN15 24                   // 3 digit -- G
#define PIN16 23                   // 3 digit -- DP
#define PIN_SCROLL_RIGHT_BUTTON 12 // Scroll display right button
#define PIN_SCROLL_LEFT_BUTTON 12  // Scroll display left button
#define PIN_RESET_STAT 8           // Reset odometer button
#define PIN_CHANGE_UNITS_BUTTON 99 // Change units button
#define PIN_DIG1 0                 // 3 digit -- dig1
#define PIN_DIG2 2                 // 3 digit -- dig2
#define PIN_DIG3 3                 // 3 digit -- dig3
#define WAIT 3                     // 3 digit display -- delay per digit

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
float odometer;
float dist;
double speed;
double pressure;
double engineTemp;
double oilTemp;
double trip_odometer;
double fuelDistance;
double fuelBurnedTotal;
double fuelConsumption;
double fuelConsumption_avg;
double fuelBurned;
double displayFuelCons;
double displayFuelConsAvg;
double fuel_old;
unsigned dashLights;
unsigned dashLights_old;
bool GayUnits = false;
long long tick_counter = 0;

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
        if (GayUnits == false)
        {
            dig = lround(speed); // km/h
        }
        else
        {
            dig = lround(speed * 0.621371); // mph
        }
        break;
    }
    case DisplayState::TurboPressure:
    {
        if (GayUnits == false)
        {
            dig = lround(pressure * 10); // bar
        }
        else
        {
            dig = lround(pressure * 145.038); // psi
        }
        break;
    }
    case DisplayState::TripOdometer:
    {
        if (GayUnits == false)
        {
            dig = lround(trip_odometer * 10); // km
        }
        else
        {
            dig = lround(trip_odometer * 6.21371); // m
        }
        break;
    }
    case DisplayState::Odometer:
    {
        if (GayUnits == false)
        {
            dig = lround((odometer + trip_odometer) * 10); // km
        }
        else
        {
            dig = lround((odometer + trip_odometer) * 6.21371); // m
        }
        break;
    }
    case DisplayState::EngineTemp:
    {
        if (GayUnits == false)
        {
            dig = lround(engineTemp); // °C
        }
        else
        {
            dig = lround(engineTemp * 1.8) + 32; // °F
        }
        break;
    }
    case DisplayState::OilTemp:
    {
        if (GayUnits == false)
        {
            dig = lround(oilTemp); // °C
        }
        else
        {
            dig = lround(oilTemp * 1.8) + 32; // °F
        }
        break;
    }
    case DisplayState::CurrentFuelConsumption:
    {
        if (GayUnits == false)
        {
            dig = lround(displayFuelCons * 10); // l/100km
        }
        else
        {
            dig = lround(235.21 / (displayFuelCons / 10)); // mpg
        }
        break;
    }
    case DisplayState::AverageFuelConsumption:
    {
        if (GayUnits == false)
        {
            dig = lround(fuelConsumption_avg * 10); // l/100km
        }
        else
        {
            dig = lround(235.21 / (fuelConsumption_avg / 10)); // mpg
        }
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
    dig2 = digParser(2, state);
    dig3 = digParser(3, state);
    tripleDigitMutex.unlock();

    switch (state)
    {                                 // This decribes how to display each different displayState i.e. whether or not to use pin16(DP)
    case DisplayState::TurboPressure: // These describe the specific behaviour i.e. if the first digit going from the left is 0 skip displaying that digit
    {
        if (pressure < 0) // This can display small negative numbers with a minus sign
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
        if (dig1 == 0) // This displays two digits (up to 99) and the DP
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

void doScreenScrollRightButtonWork()
{
    int des_RightbuttonState = 0;
    int last_RightbuttonState = 0;
    while (true)
    {
        des_RightbuttonState = digitalRead(PIN_SCROLL_RIGHT_BUTTON);
        if (last_RightbuttonState != des_RightbuttonState)
        {
            if (last_RightbuttonState == 0)
            {
                tripleDigitMutex.lock();
                displayState = (DisplayState)(((int)displayState + 1) % DISPLAY_STATE_COUNT);
                tripleDigitMutex.unlock();
            }
            last_RightbuttonState = des_RightbuttonState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void doScreenScrollLeftButtonWork()
{
    int des_LeftbuttonState = 0;
    int last_LeftbuttonState = 0;
    while (true)
    {
        des_LeftbuttonState = digitalRead(PIN_SCROLL_LEFT_BUTTON);
        if (last_LeftbuttonState != des_LeftbuttonState)
        {
            if (last_LeftbuttonState == 0)
            {
                tripleDigitMutex.lock();
                displayState = (DisplayState)(((int)displayState + DISPLAY_STATE_COUNT - 1) % DISPLAY_STATE_COUNT);
                tripleDigitMutex.unlock();
            }
            last_LeftbuttonState = des_LeftbuttonState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void doResetStatButtonWork()
{
    int des_ResetStatButtonState = 0;
    int last_ResetStatButtonState = 0;
    while (true)
    {
        des_ResetStatButtonState = digitalRead(PIN_RESET_STAT);
        if (last_ResetStatButtonState != des_ResetStatButtonState)
        {
            if (last_ResetStatButtonState == 0)
            {
                tripleDigitMutex.lock();
                switch (displayState)
                {
                case DisplayState::AverageFuelConsumption:
                {
                    fuelBurnedTotal = 0;
                    fuelDistance = 0;
                    break;
                }
                case DisplayState::TripOdometer:
                {
                    odometer += trip_odometer;
                    trip_odometer = 0;
                    break;
                }
                }
                tripleDigitMutex.unlock();
            }
            last_ResetStatButtonState = des_ResetStatButtonState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void doExtremelyGayButtonWork()
{
    int des_ExtremelyGayButtonState = 0;
    int last_ExtremelyGayButtonState = 0;
    while (true)
    {
        des_ExtremelyGayButtonState = digitalRead(PIN_CHANGE_UNITS_BUTTON);
        if (last_ExtremelyGayButtonState != des_ExtremelyGayButtonState)
        {
            if (last_ExtremelyGayButtonState == 0)
            {
                tripleDigitMutex.lock();
                GayUnits = !GayUnits;
                tripleDigitMutex.unlock();
            }
            last_ExtremelyGayButtonState = des_ExtremelyGayButtonState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

double calcFuelConsumption(double fuelBurnedCalc, double distance)
{
    if (fuelBurnedCalc < 1e-4 || distance < 1e-4)
    {
        return 0;
    }
    else
    {
        return ((100 / distance) * fuelBurnedCalc);
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

    Display::initialize();

    std::thread singleDigitThread(doSingleDigitWork);
    std::thread tripleDigitThread(doTripleDigitWork);
    std::thread screenScrollRightButtonThread(doScreenScrollRightButtonWork);
    // std::thread screenScrollLeftButtonThread(doScreenScrollLeftButtonWork);
    // std::thread changeUnitsToGayButton(doExtremelyGayButtonWork);
    // std::thread resetStatButtonThread(doResetStatButtonWork);

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

    accumulator_set<double, stats<tag::rolling_mean>> accumulatorFuelConsumption(tag::rolling_window::window_size = 20);
    accumulator_set<double, stats<tag::rolling_sum>> accumulatorDistDelta(tag::rolling_window::window_size = 25);
    accumulator_set<double, stats<tag::rolling_sum>> accumulatorFuelAmount(tag::rolling_window::window_size = 25);

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

            tripleDigitMutex.lock(); // Mutex start
            singleDigitMutex.lock();
            auto new_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> tickTime = new_time - old_time;
            double speed_to_count = s->speed;

            if (speed_to_count < 0.15)
            {
                speed_to_count = 0;
            }
            if (fuel_old < 1e-6)
            {
                fuelBurned = 0;
                fuel_old = s->fuel_remaining;
            }
            else
            {
                fuelBurned = fuel_old - s->fuel_remaining;
                fuel_old = s->fuel_remaining;
            }
            if (fuelBurned > 1e-6)
            {
                fuelBurnedTotal += fuelBurned;
            }

            double distDelta = tickTime.count() * speed_to_count / 1000;
            trip_odometer += distDelta;
            fuelDistance += distDelta;
            accumulatorFuelAmount(fuelBurned);
            accumulatorDistDelta(distDelta);
            fuelConsumption = calcFuelConsumption(rolling_sum(accumulatorFuelAmount), rolling_sum(accumulatorDistDelta));
            accumulatorFuelConsumption(fuelConsumption);

            if (tick_counter % 5 == 0)
            {
                fuelConsumption_avg = calcFuelConsumption(fuelBurnedTotal, fuelDistance);
                if (tick_counter % 20 == 0)
                {
                    displayFuelCons = rolling_mean(accumulatorFuelConsumption);
                }
            }

            speed = s->speed * 3.6;
            pressure = s->turbo;
            dist = trip_odometer;
            engineTemp = s->engTemp;
            oilTemp = s->oilTemp;
            des_gear = (int)s->gear;
            singleDigitMutex.unlock();
            tripleDigitMutex.unlock(); // Mutex end

            old_time = new_time;
        }
        tick_counter++;
    }

    return 0;
}
