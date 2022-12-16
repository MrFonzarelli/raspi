#include "outgauge.hpp"

OutGauge::DashLights OutGauge::getDashLights()
{
    DashLights result;
    result.shiftLight = showLights & 0b0000000000001;
    result.lowBeam = showLights & 0b0000000000010;
    result.highBeam = showLights & 0b0000000000100;
    result.parkBrake = showLights & 0b0000000001000;
    result.fogLight = showLights & 0b0000000010000;
    result.tractionControl = showLights & 0b0000000100000;
    result.signalLeft = showLights & 0b0000001000000;
    result.signalRight = showLights & 0b0000010000000;
    result.oilWarning = showLights & 0b0001000000000;
    result.engineRunning = showLights & 0b0010000000000;
    result.abs = showLights & 0b0100000000000;
    result.hazardLight = showLights & 0b1000000000000;
    return result;
}