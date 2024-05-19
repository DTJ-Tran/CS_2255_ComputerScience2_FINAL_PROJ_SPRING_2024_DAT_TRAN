#include"VolumeAdjust.h"


volumeAdjust::volumeAdjust() {
    setVolume(0);
};

volumeAdjust::volumeAdjust(int const inputVolume) {
    setVolume(inputVolume);
};

void volumeAdjust::setVolume(int const inputVolume) {
    this->volumeLevel = inputVolume;
    return;
};

double volumeAdjust::getVolume() const {
    return this->volumeLevel;
};


// Sigmoid function with thresholds for rounding to zero and one
double volumeAdjust::sigmoid(double x, double zeroThreshold, double oneThreshold) {
    double result = 1 / (1 + exp(-x));
    if (result <= zeroThreshold) {
        return 0.0; // If result is below zero threshold, round it up to zero
    }
    if (result >= 1.0 - oneThreshold) {
        return 1.0; // If result is above one threshold, round it down to one
    }
    return result;
};

// Adjust volume using sigmoid function
double volumeAdjust::adjustVolume(double currentVolume, double targetVolume, double smoothingFactor, double zeroThreshold, double oneThreshold) {
    // Calculate the difference between current and target volumes
    double volumeDifference = targetVolume - currentVolume;
    
    // Apply sigmoid function to smoothly adjust volume
    double adjustedVolume = currentVolume + volumeDifference * sigmoid(smoothingFactor * volumeDifference, zeroThreshold, oneThreshold);
    
    return adjustedVolume;
};


double volumeAdjust::getVolLevel() const {
    return this->volumeLevel;
};

void volumeAdjust::setVolLevel(double const inputLevel) {
    this->volumeLevel = inputLevel;
    return;
};
