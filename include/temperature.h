#pragma once

#include "common.h"
#include "system.h"
#include <vector>
#include <future>
#include <thread>
#include <chrono>

class TemperatureMonitor {
    System sys;
    unsigned int sampling_rate;
    std::vector<std::vector<unsigned int> > temp_log;
    std::future<void> logger;
    bool logger_state;
public:
    TemperatureMonitor(System const& s) : sys(s), sampling_rate(1), logger_state(false) {
        temp_log.resize(s.getDeviceCount());
    }

    void setSamplingRate(unsigned h) { sampling_rate = h; }
    unsigned int getSamplingRate() const { return sampling_rate; }

    void start() {
        logger_state = true;
        logger = std::async(std::launch::async, [&]() {
            while(logger_state) {
                for(int i=0; i<temp_log.size(); ++i) {
                    temp_log[i].push_back(-1);
                    NVML_CHECKED_CALL(nvmlDeviceGetTemperature(sys.getDevice(i), NVML_TEMPERATURE_GPU, &(temp_log[i].back())));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds((int)((double)(1.0/sampling_rate)*1000)));
            }
        });
    }

    void stop() {
        logger_state = false;
        logger.wait();
    }
    
    void reset() {
        temp_log = std::vector<std::vector<unsigned int> >();
        temp_log.clear();
        temp_log.resize(sys.getDeviceCount());
    }

    void printInformation() const {
        std::cout << "###LIBGPOW TEMPMON INFORMATION [°C]###\n";
        for(unsigned i=0; i<temp_log.size(); ++i) {
            std::cout << "Device" << i << "\t";
        }
        std::cout << std::endl;
        if(temp_log.size()) {
            for(unsigned i=0; i<temp_log[0].size(); ++i) {
                for(unsigned j=0; j<temp_log.size(); ++j) {
                    std::cout << temp_log[j][i] << "\t";
                }
                std::cout << std::endl;
            }
        }
    } 
};
