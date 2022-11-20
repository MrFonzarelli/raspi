#ifndef FUNCTIONS_H
#define FUNCTIONS_H
int ReverseHandler(void);
int NeutralHandler(void);
int FirstHandler();
int SecondHandler();
int ThirdHandler();
int FourthHandler();
int FifthHandler();
int SixthHandler();
int SeventhHandler();
int EighthHandler();
int NinethHandler();
int ZeroHandler();
int FirstHandlerTri();
int SecondHandlerTri();
int ThirdHandlerTri();
int FourthHandlerTri();
int FifthHandlerTri();
int SixthHandlerTri();
int SeventhHandlerTri();
int EighthHandlerTri();
int NinethHandlerTri();
int ZeroHandlerTri();
int MinusHandlerTri();
int singleDigitOutput(int state);
int digitSelect(int num);
int digParser(int num, DisplayState state);
void tripleDigitOutput();
void doSingleDigitWork();
void doTripleDigitWork();
void read_odometer();
void write_odometer();
void doScreenScrollRightButtonWork();
void doScreenScrollLeftButtonWork();
void doResetStatButtonWork();
void doExtremelyGayButtonWork();
double calcFuelConsumption(double fuelBurnedCalc, double distance);
void odo_signal_handler(int);
#endif