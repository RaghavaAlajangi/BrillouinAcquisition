#ifndef EOM_H
#define EOM_H

class EOM {
public:
    static double frequencyToVoltage(double frequency);
    static void writeVoltageToDAQ(double voltage);
};

#endif // EOM_H
