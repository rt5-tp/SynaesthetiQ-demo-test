#include <Iir.h>
#include <stdio.h>
#include <cmath>
#include <vector>

/**
 * @class EnvelopeFollower
 * @brief A simple envelope follower .
 */

typedef void (*DataProcessed)(const std::vector<short> &);

class EnvelopeFollower {
public:

    /**
     * @brief Envelope Follower constructor
     *
     * This instantiates an IIR filter, which will be used in the main process.
     *
     * @a fs - audio sample rate (required)
     * @a fc - lowpass filter cut-off frequency (optional, default=10)
     */
    EnvelopeFollower(int fs, int fc);

    /**
     * @brief Envelope Follower destructor
     */
    ~EnvelopeFollower();

    /**
     * @brief Callback to send ouput data to next process
     */
    void registerCallback(DataProcessed cb);

    /**
     * @brief Carries out the envelope follower process.
     *
     * Triggered by data being available from audio capture.
     */
    static void audio_callback(const std::vector<short> &buffer);

private:
    /**
     * @brief The envelope follower is a singleton.
     */
    static EnvelopeFollower* singleton;
    DataProcessed callback;
    Iir::Butterworth::LowPass<4> filter;
    int fs;
    int fc;
    
};