#ifndef DSP_HPP
#define DSP_HPP

#include <cmath>
#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <fstream>

namespace niistt {

namespace dsp {

namespace datatypes {

typedef struct {
    int16_t I;
    int16_t Q;
} int16_iq_t;

typedef struct {
    int32_t I;
    int32_t Q;
} int32_iq_t;

typedef struct {
    float I;
    float Q;
} float_iq_t;

typedef struct {
    double I;
    double Q;
} double_iq_t;

}

/**
 * @brief Функция wavelet "Мексиканская шляпа"
 * @param a Масштабный коэффициент
 * @param b Временной сдвиг
 * @param t Дискрета времени
 * @return Значение в точке t
 */
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
        Waveform_DataType_double_plain,
        Waveform_DataType_unknown
    };

protected:

    template<typename T>
    uint16_t getType(void) {
        if (std::is_same<T, datatypes::int16_iq_t>::value) {
            return Waveform_DataType_int16_iq;
        } else if (std::is_same<T, datatypes::int32_iq_t>::value) {
            return Waveform_DataType_int32_iq;
        } else if (std::is_same<T, datatypes::float_iq_t>::value) {
            return Waveform_DataType_float_iq;
        } else if (std::is_same<T, datatypes::double_iq_t>::value) {
            return Waveform_DataType_double_iq;
        } else {
            return ~((uint16_t)0x0);
        }
    }

    void * memory;
    uint64_t memorySize;
    uint16_t currentType;

public:
    Waveform() {}

    Waveform(const Waveform & other) {
        this->memory = malloc(other.memorySize);
        this->memorySize = other.memorySize;

        std::memcpy(this->memory, other.memory, this->memorySize);
        this->currentType = other.currentType;
    }

    Waveform(const Waveform && other);

    template<typename T>
    Waveform(std::vector<double> & timeline, std::vector<T> & data) {
        if (timeline.size() != data.size())
            throw std::runtime_error("Timeline duration not equal to data");

        Waveform wave;
        memorySize = data.size() * sizeof (T);
        wave.memory = malloc(memorySize);
        std::memcpy(memory, data.data(), memorySize);

        this->currentType = getType<T>();
    }
};

}

}

#endif // DSP_HPP
