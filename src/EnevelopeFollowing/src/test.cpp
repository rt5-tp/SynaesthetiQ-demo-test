#include <Iir.h>
#include "AudioFile.h"
#include <stdio.h>
#include <cmath>
#include "EnvelopeFollower.hpp"

FILE *finput;
FILE *foutput;

short floatToShort(float x)
{
    return (short) x;
}

void writeOutput(std::vector<short> buffer)
{
    for (auto sample : buffer){
        fprintf(foutput, "%d\n", sample);
    }
}

int main()
{
    // Load audio file
    AudioFile<float> audio;
    bool loadedOK = audio.load("test-audio.wav");
    assert(loadedOK);

    int no_frames = audio.getNumSamplesPerChannel();
    int fs = audio.getSampleRate();

    finput = fopen("Input.txt", "wt");
    foutput = fopen("Envelope.txt", "wt");

    EnvelopeFollower follower(fs,10);

    follower.registerCallback((DataProcessed) writeOutput);

    std::vector<short> buffer;

    for (int i = 0; i < no_frames; i++)
    {
        short sample = floatToShort(audio.samples[0][i]*10000);
        buffer.push_back(sample);

        fprintf(finput, "%d\n", sample);

        if (buffer.size() == 4096) {

            follower.audio_callback(buffer);

            buffer.clear();
        }
    }

    fclose(foutput);
    fclose(finput);

    return 0;
}