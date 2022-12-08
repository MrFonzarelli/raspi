#include "outgauge.hpp"

OutGauge::DashLights OutGauge::getDashLights()
{
    DashLights result;
    result.shiftLight = dashLights & 0b0000000000001;
    result.lowBeam = dashLights & 0b0000000000010;
    result.highBeam = dashLights & 0b0000000000100;
    result.parkBrake = dashLights & 0b0000000001000;
    result.fogLight = dashLights & 0b0000000010000;
    result.tractionControl = dashLights & 0b0000000100000;
    result.signalLeft = dashLights & 0b0000001000000;
    result.signalRight = dashLights & 0b0000010000000;
    result.oilWarning = dashLights & 0b0001000000000;
    result.engineRunning = dashLights & 0b0010000000000;
    result.abs = dashLights & 0b0100000000000;
    result.hazardLight = dashLights & 0b1000000000000;
    return result;
}