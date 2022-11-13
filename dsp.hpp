#ifndef DSP_HPP
#define DSP_HPP

#include <cmath>
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

namespace niistt {

namespace dsp {

static double waveletMHAT(double a, double b, double t) {
    return (1.0 / std::sqrt(a)) * std::exp(-0.5 * std::pow((t - b) / a, 2)) * (std::pow((t - b) / 2, 2) - 1);
}

class Waveform {
public:

    enum Waveform_DataType_ : uint16_t {
        Waveform_DataType_int16_iq,
        Waveform_DataType_int32_iq,
        Waveform_DataType_float_iq,
        Waveform_DataType_double_iq,
        Waveform_DataType_int16_plain,
        Waveform_DataType_itn32_plain,
        Waveform_DataType_float_plain,
        Waveform_DataType_double_plain
    };

protected:

public:
    Waveform() {}
    Waveform(const Waveform & other);
    Waveform(const Waveform && other);

    static Waveform && createFromFile(std::string path, Waveform_DataType_ type);

    template<class T, class ... args>
    static Waveform && createFromData(const std::vector<double> & timeline, std::vector<T> & graphData, args ...) {

    }
};

}

}

#endif // DSP_HPP
