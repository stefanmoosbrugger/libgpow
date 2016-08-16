#include "system.h"
#include "temperature.h"
#include "gtest/gtest.h"

TEST(System, SimpleTest) {
    System s;
    s.printInformation();
    TemperatureMonitor t(s);
    t.setSamplingRate(2);
    t.start();
    sleep(3);
    t.stop();
    t.printInformation(); 
}
