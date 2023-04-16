#include "Visualiser.hpp"

std::vector<std::pair<std::string, float>> Visualiser::predictions;
std::vector<double> Visualiser::fft_data;
std::vector<short> Visualiser::envelope_data;

std::vector<std::vector<bool>> Visualiser::fftLED_data;

/* 
 * @brief Sets up callbacks
 * 
 *        ||=> genreClassifier  =||
 * audio =||=> envelopeFollower =||=> Visualiser
 *        ||=> fftProcessor     =||
*/
Visualiser::Visualiser() : audioCapture(""), synaesthetiQ(), genreClassifier(), fftProcessor(), envelopeFollower(44100,10){
    
    // data flowing into visualiser, which can be accessed in visualise()
    // genreClassifier.register_genre_callback(&Visualiser::genre_prediction_callback);
    fftProcessor.registerCallback(&Visualiser::fft_callback);
    fftProcessor.registerLEDCallback(&Visualiser::fft_LEDcallback);

    envelopeFollower.registerCallback(&Visualiser::envelope_callback);
    
    // data flowing from audio into genreClassifer, fftProcessor
    //        ||=> genreClassifier
    // audio =|| 
    //        ||=> fftProcessor     
    // audioCapture.register_callback(genreClassifier.audio_callback);
    audioCapture.register_callback(fftProcessor.audio_callback);
    audioCapture.register_callback(envelopeFollower.audio_callback);
}

void Visualiser::visualise()
{
    Colour on_colour(10, 10, 10);
    Colour off_colour(0, 0, 0);


    // Read values from FFT LED Matrix callback

    if (fftLED_data.size() > 0)
    {
        // std::cout << "y size = " << fftLED_data.size() << std::endl;
        // std::cout << "x size = " << fftLED_data[0].size() << std::endl;
        for (int y = 0; y < fftLED_data.size(); y++)
        {
            for (int x = 0; x < fftLED_data[y].size(); x++)
            {
                // bool status = fftLED_data[i][j];
                if (fftLED_data[y][x] == true) // should be: if (fftLED_data[x][y] == true)
                {   
                    std::cout << "x";
                    // std::cout << "Element (" << i << ", " << j << ") = " << status << std::endl;
                    synaesthetiQ.setMatrixPixelColour(x, y, on_colour);
                }
                else
                {
                    std::cout << "0";
                    synaesthetiQ.setMatrixPixelColour(x, y, off_colour);
                }
                // bool status = fftLED_data[i][j];
                // std::cout << "Element (" << i << ", " << j << ") = " << status << std::endl;
            }
            std::cout << std::endl;
        }
    }
    synaesthetiQ.render();
}