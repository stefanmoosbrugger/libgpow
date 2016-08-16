#pragma once

#include "nvml.h"
#include <iostream>
#include <map>

namespace {
    std::map<int, std::string> errorCodes = {
        {1, "NVML was not first initialized with nvmlInit()."}, 
        {2, "A supplied argument is invalid."}, 
        {3, "The requested operation is not available on target device."},
        {4, "The current user does not have permission for operation."},
        {5, "Deprecated: Multiple initializations are now allowed through ref counting."},
        {6, "A query to find an object was unsuccessful."},
        {7, "An input argument is not large enough."},
        {8, "A device's external power cables are not properly attached."},
        {9, "NVIDIA driver is not loaded."},
        {10, "User provided timeout passed."},
        {11, "NVIDIA Kernel detected an interrupt issue with a GPU."},
        {12, "NVML Shared Library couldn't be found or loaded."},
        {13, "Local version of NVML doesn't implement this function."},
        {14, "infoROM is corrupted"}, 
        {15, "The GPU has fallen off the bus or has otherwise become inaccessible."},
        {16, "The GPU requires a reset before it can be used again."},
        {17, "The GPU control device has been blocked by the operating system/cgroups."},
        {999, "An internal driver error occurred."}
    };
}

#define NVML_CHECKED_CALL(CALL) { nvmlReturn_t res = CALL; if(res != NVML_SUCCESS) { std::cout << "Error in " << #CALL <<": " << errorCodes[res] << std::endl; abort(); } }

