#include "EnvelopeFollower.hpp"
#include <Iir.h>
#include <stdio.h>
#include <cmath>
#include <vector>

EnvelopeFollower* EnvelopeFollower::singleton;

EnvelopeFollower::EnvelopeFollower(int fs, int fc = 10){
    // Initialising the Envelope Follower object, including starting the thread.
    this->fs = fs;
    this->fc = fc;

    // setup lowpass filter
    filter.setup(fs, fc);
    singleton = this;
}

EnvelopeFollower::~EnvelopeFollower(){
}

void EnvelopeFollower::registerCallback(DataProcessed cb){
    callback = cb;
}

void EnvelopeFollower::audio_callback(const std::vector<short>& buffer){

    std::vector<short> out;

    for (auto sample : buffer){

        // Full-wave recitifier
        sample = abs(sample);

        // Low-pass filter
        out.push_back(singleton->filter.filter(sample));
    }

    if (singleton->callback) {
        singleton->callback(out);
    }
}