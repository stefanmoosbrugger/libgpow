#pragma once

#include "common.h"
#include <vector>

class System {
    unsigned int unit_cnt;
    unsigned int dev_cnt;
    std::vector<nvmlDevice_t> devs;
public:
    System() {
        NVML_CHECKED_CALL(nvmlInit()); // initialize nvml lib
        NVML_CHECKED_CALL(nvmlUnitGetCount(&unit_cnt)); // get number of units 
        NVML_CHECKED_CALL(nvmlDeviceGetCount(&dev_cnt)); // get device count
        // initialize all devices
        devs.resize(dev_cnt);
        for(unsigned i=0; i<dev_cnt; ++i) {
            NVML_CHECKED_CALL(nvmlDeviceGetHandleByIndex(i, &(devs[i]))); 
        }
    }

    ~System() {
        NVML_CHECKED_CALL(nvmlShutdown());
    }

    unsigned int getUnitCount() const { return unit_cnt; }

    unsigned int getDeviceCount() const { return dev_cnt; }

    nvmlDevice_t getDevice(unsigned i) const { return devs[i]; }

    void printInformation() const {
        std::cout << "###LIBGPOW SYSTEM INFORMATION###\n";
        std::cout << "Number of Units: " << getUnitCount() << std::endl;
        std::cout << "Number of Devices: " << getDeviceCount() << std::endl;
        for(unsigned i=0; i<devs.size(); ++i) {
            char name[64];
            NVML_CHECKED_CALL(nvmlDeviceGetName (devs[i], &name[0], 64));
            std::cout << "Device " << i << " name: " << name << std::endl; 
        }
    }
};
