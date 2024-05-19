#pragma once
#include <iostream>
#include <cmath>
#include <thread>


class volumeAdjust {

    private:
        double volumeLevel;
    public:
        volumeAdjust();
        volumeAdjust(int const);
        void setVolume(int const);
        double getVolume() const;
        double getVolLevel() const;
        void setVolLevel(double const);
        double sigmoid(double, double, double);
        double adjustVolume(double , double , double , double , double );


};