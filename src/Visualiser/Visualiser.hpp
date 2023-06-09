#include "../SynaesthetiQ-LED-Library/src/SynaesthetiQ/synaesthetiq.hpp"
#include "../SynaesthetiQ-audiocapture/src/AudioCapture/AudioCapture.h"
#include "../SynaesthetiQ-audiocapture/src/GenreClassification/GenreClassifier.h"
#include "../SynaesthetiQ-audiocapture/src/FFTProcessor.h"
#include "../EnvelopeFollowing/src/EnvelopeFollower.hpp"

class Visualiser {
    private:
    AudioCapture audioCapture; 
    FFTProcessor fftProcessor;
    GenreClassifier genreClassifier;
    SynaesthetiQ synaesthetiQ;
    EnvelopeFollower envelopeFollower;

    static std::vector<std::pair<std::string, float>> predictions;
    static std::vector<double> fft_data;
    static std::vector<short> envelope_data;

    // Keeps predictions vector up-to-date with latest predictions
    static void genre_prediction_callback(const std::vector<std::pair<std::string, float>>& predictions){
        Visualiser::predictions = predictions;
    }

    static void fft_callback(const std::vector<double> & fft_data){
        Visualiser::fft_data = fft_data;
    }

    static void envelope_callback(const std::vector<short> & envelope_data){
        Visualiser::envelope_data = envelope_data;
    }

    public:
    Visualiser();

    void visualise();
};