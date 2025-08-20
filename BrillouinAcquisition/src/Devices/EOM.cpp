#include "stdafx.h" 
#include "EOM.h"
#include <cmath>
#include <iostream>

double EOM::frequencyToVoltage(double frequency)
{
    // Polynomial coefficients
    double p0 = -4.19117e-6;
    double p1 = 0.000168553;
    double p2 = 0.00273963;
    double p3 = 0.0228064;
    double p4 = -0.106149;
    double p5 = 0.596645;
    double p6 = 3.40049;

    // Polynomial (degree 6)
    double voltage = (p0 * std::pow(frequency, 6)) +
                     (p1 * std::pow(frequency, 5)) +
                     (p2 * std::pow(frequency, 4)) +
                     (p3 * std::pow(frequency, 3)) +
                     (p4 * std::pow(frequency, 2)) +
                     (p5 * frequency) +
                     p6;

    return std::round(voltage * 100.0) / 100.0;
}

void EOM::writeVoltage(const std::string& channel, double voltage) {
    TaskHandle taskHandle = nullptr;

    int32 error = DAQmxCreateTask("", &taskHandle);
    if (error) { std::cerr << "Error creating task: " << error << std::endl; return; }

    error = DAQmxCreateAOVoltageChan(taskHandle, channel.c_str(), "", 0.0, 10.0, DAQmx_Val_Volts, nullptr);
    if (error) { std::cerr << "Error creating channel: " << error << std::endl; DAQmxClearTask(taskHandle); return; }

    error = DAQmxWriteAnalogScalarF64(taskHandle, true, 10.0, voltage, nullptr);
    if (error) { std::cerr << "Error writing voltage: " << error << std::endl; }

    DAQmxStopTask(taskHandle);
    DAQmxClearTask(taskHandle);
}

void EOM::writeVoltageToDAQ(double voltage) {
    writeVoltage("Dev2/ao0", voltage);
}

void EOM::writeAttenuationVoltageToDAQ(double voltage) {
    writeVoltage("Dev2/ao1", voltage);
}