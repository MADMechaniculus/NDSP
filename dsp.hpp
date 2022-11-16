#ifndef DSP_HPP
#define DSP_HPP

#include <QCustomPlot/qcustomplot.h>

#include <cmath>
#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <fstream>
#include <functional>

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

    // Типы созможных данных
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

    // Дополнительные сведения
    typedef struct {
        std::string name;
        std::string description;
        double sampleRate;
    } metadata_t;

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
            return (uint16_t)(~0x0);
        }
    }

    // TODO
    // Copy timeline

    void * memoryData;
    QVector<double> timeline;
    uint64_t memorySize;
    uint16_t currentType;
    uint16_t sizeofItem;
    std::function<void(QCPGraph *)> drawer;

public:
    Waveform(const Waveform & other) {
        this->memoryData = malloc(other.memorySize);
        this->memorySize = other.memorySize;

        std::memcpy(this->memoryData, other.memoryData, this->memorySize);
        this->currentType = other.currentType;
        this->sizeofItem = other.sizeofItem;
    }

    Waveform(const Waveform && other) {
        this->memoryData = malloc(other.memorySize);
        this->memorySize = other.memorySize;

        std::memcpy(this->memoryData, other.memoryData, this->memorySize);
        this->currentType = other.currentType;
        this->sizeofItem = other.sizeofItem;
    }

    template<typename T>
    Waveform(std::vector<double> & timeline, std::vector<T> & data) {
        if (timeline.size() != data.size())
            throw std::runtime_error("Timeline duration not equal to data");

        memorySize = data.size() * sizeof (T);
        this->memoryData = malloc(memorySize);
        std::memcpy(this->memoryData, data.data(), memorySize);

        this->currentType = getType<T>();
        this->sizeofItem = sizeof (T);
        if (this->currentType == (uint16_t)(~0x0)) {
            throw std::runtime_error("Unsupported data type");
        }
    }

    template<typename T>
    Waveform(std::vector<double> & timeline, T * data, uint64_t size /* count of element type T */) {
        if (timeline.size() != size)
            throw std::runtime_error("Timeline duration not equal to data");

        memorySize = size * sizeof (T);
        this->memoryData = malloc(memorySize);
        std::memcpy(this->memoryData, data, memorySize);

        this->currentType = getType<T>();
        this->sizeofItem = sizeof (T);
        if (this->currentType == (uint16_t)(~0x0)) {
            throw std::runtime_error("Unsupported data type");
        }
    }

    /**
     * @brief Указатель на данные внутри объекта
     */
    void const * data(void) {
        return this->memoryData;
    }

    /**
     * @brief Размер блока данных внутри объекта
     */
    uint64_t size(void) const {
        return this->memorySize;
    }

    /**
     * @brief Получение размерности одно элемента
     */
    uint16_t itemSize(void) const {
        return this->sizeofItem;
    }

    void setDrawer(std::function<void(QCPGraph *)> drawer) {
        drawer = drawer;
    }

    void draw(QCPGraph * graph) {
        this->drawer(graph);
    }
};

}

}

#endif // DSP_HPP
