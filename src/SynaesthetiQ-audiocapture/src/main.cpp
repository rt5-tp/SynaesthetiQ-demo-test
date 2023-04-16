#include <iostream>
#include <alsa/asoundlib.h>
#include <fstream>
#include <vector>
#include <climits>
#include <thread>
#include <string>
#include <signal.h>
#include <fftw3.h>
#include <cstring>
#include <cmath>
#include <algorithm>


#include "AudioCapture.h"
#include "FFTProcessor.h"
#include "GenreClassifier.h"


FFTProcessor fftProcessor; //create instance of fftprocessor class

void genre_prediction_callback(const std::vector<std::pair<std::string, float>>& predictions){
    std::cout << "\nGenre Predictions callback: \n";
    for(auto prediction : predictions){
        std::cout << prediction.first << " : " << prediction.second << std::endl;
    }
    std::cout << std::endl;
}

// FFT callback function
void onFFTDataAvailable(const std::vector<double> &data) {
    std::cout << "FFT DATA AVAILABLE" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "Initialising!" << std::endl;
    std::string device_name = "";
    
    
    GenreClassifier classifier;

    try {
        
        classifier.register_genre_callback(&genre_prediction_callback);

        AudioCapture audioCapture(device_name);
        audioCapture.register_callback(classifier.audio_callback);
        audioCapture.register_callback(fftProcessor.audio_callback);

        //update callbacks for consistency
        fftProcessor.registerCallback(onFFTDataAvailable);

        std::cout << "Starting" << std::endl;
        std::cout << "Waiting...\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Done.\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    std::cout << "Complete" << std::endl;
    return 0;
}
