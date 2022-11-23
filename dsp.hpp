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
#include <cstdlib>

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

class FileWatcher {
protected:

    static constexpr uint64_t windowSize = 64 * 1024 * 1024;

    std::ifstream fileStream;
    uint64_t fileSize;
    uint64_t fileOffset;

    void * windowData = nullptr;

public:
    enum UpdateOffset_Direction_ : uint8_t {
        UpdateOffset_Direction_Left,
        UpdateOffset_Direction_Right
    };

    static constexpr uint64_t visibleSize = 48 * 1024 * 1024;

    FileWatcher(std::ifstream && file, uint64_t fileSize) : fileStream(std::move(file)) {
        this->fileSize = fileSize;
        this->fileOffset = 0;

        this->windowData = std::malloc(this->windowSize);
        if (this->windowData == nullptr) {
            throw std::runtime_error("Bad memory alloc");
        }

        this->fileStream.read((char*)this->windowData, this->windowSize);
    }

    void * visibleData() {
        return (uint8_t *)this->windowData + this->fileOffset;
    }

    void updateOffset(uint64_t delta, uint8_t direction) {
        switch (direction) {
        case UpdateOffset_Direction_Left:
            if (this->fileOffset < delta)
                this->fileOffset = 0;
            break;
        case UpdateOffset_Direction_Right:
            if ((this->fileOffset + delta) >= (this->fileSize - this->visibleSize))
                this->fileOffset = this->fileSize - this->visibleSize;
            break;
        }
    }

    ~FileWatcher() {
        std::free(this->windowData);
    }
};

class Waveform {
public:

    // Типы созможных данных
    enum Waveform_DataType_ : uint16_t {
        Waveform_DataType_int16_iq = 0,
        Waveform_DataType_int32_iq = 1,
        Waveform_DataType_float_iq = 2,
        Waveform_DataType_double_iq = 3,
        Waveform_DataType_int16_plain = 4,
        Waveform_DataType_int32_plain = 5,
        Waveform_DataType_float_plain = 6,
        Waveform_DataType_double_plain = 7,
        Waveform_DataType_unknown = 8
    };

    // Получение строки с названием элемента перечисления типов данных
    static const char* Waveform_DataType_ItemName(uint16_t index) {
        switch (index) {
        case Waveform_DataType_int16_iq:
            return "Waveform_DataType_int16_iq";
        case Waveform_DataType_int32_iq:
            return "Waveform_DataType_int32_iq";
        case Waveform_DataType_float_iq:
            return "Waveform_DataType_float_iq";
        case Waveform_DataType_double_iq:
            return "Waveform_DataType_double_iq";
        case Waveform_DataType_int16_plain:
            return "Waveform_DataType_int16_plain";
        case Waveform_DataType_int32_plain:
            return "Waveform_DataType_itn32_plain";
        case Waveform_DataType_float_plain:
            return "Waveform_DataType_float_plain";
        case Waveform_DataType_double_plain:
            return "Waveform_DataType_double_plain";
        default:
            return "Waveform_DataType_unknown";
        }
    }

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
    std::shared_ptr<std::function<void(Waveform *, QCustomPlot *)>> drawer;

    std::ifstream fileStream;
    uint64_t fileSize;
    uint64_t fileOffset;

public:
    const QVector<double> & publicTimeline(void) {
        return this->timeline;
    }

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

    Waveform(std::ifstream && input, uint64_t fileSize) : fileStream(std::move(input)) {

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

    /**
     * @brief Передача функции вывода данных
     * @param drawer Функция вывода
     */
    void setDrawer(std::function<void(Waveform *, QCustomPlot *)> && drawer) {
        this->drawer = std::make_shared<std::function<void(Waveform *, QCustomPlot *)>>(drawer);
    }

    /**
     * @brief Функция отрисовки на графе
     * @param graph Целевой граф
     */
    void draw(QCustomPlot * plotter) {
        this->drawer.get()->operator()(this, plotter);
    }

    friend class QCustomPlotDrawers;
};

class QCustomPlotDrawers {

    static void addIqGraphs(QCustomPlot * plotter) {
        plotter->clearGraphs();

        plotter->addGraph();
        plotter->addGraph();
    }

public:
    static void drawer_int16_iq(QCustomPlot * plotter) {
        addIqGraphs(plotter);
    }

    static void drawer_int32_iq(QCustomPlot * plotter) {

    }

    static void drawer_float_iq(QCustomPlot * plotter) {

    }

    static void drawer_double_iq(QCustomPlot * plotter) {

    }
};

}

}

#endif // DSP_HPP
