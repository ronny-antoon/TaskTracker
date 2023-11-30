#include <Arduino.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "myTest.hpp"

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleMock();
}

void loop()
{
    if (RUN_ALL_TESTS())
        ;

    delay(1000);

    Serial.println("-----------------------------------Finished all tests!-----------------------------------");

    delay(100000);
}