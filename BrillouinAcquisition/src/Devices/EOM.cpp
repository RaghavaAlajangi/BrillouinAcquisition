#include "EOM.h"
#include <cmath>
#include <NIDAQmx.h>

double EOM::frequencyToVoltage(double frequency)
{
    // Polynomial coefficients
    double p1 = 0.002255, p2 = -0.1066, p3 = 1.786, p4 = -13.79, p5 = 53.31, p6 = -81.53;

    double voltage = (p1 * pow(frequency, 5)) +
                     (p2 * pow(frequency, 4)) +
                     (p3 * pow(frequency, 3)) +
                     (p4 * pow(frequency, 2)) +
                     (p5 * frequency) +
                     p6;

    return std::round(voltage * 100.0) / 100.0;
}

void EOM::writeVoltageToDAQ(double voltage)
{
    TaskHandle taskHandle = nullptr;

    // Create and configure DAQ task
    DAQmxCreateTask("", &taskHandle);
    DAQmxCreateAOVoltageChan(taskHandle, "Dev2/ao0", "", 0.0, 10.0, DAQmx_Val_Volts, nullptr);

    // Write voltage
    DAQmxWriteAnalogScalarF64(taskHandle, true, 10.0, voltage, nullptr);

    // Cleanup
    DAQmxStopTask(taskHandle);
    DAQmxClearTask(taskHandle);
}
