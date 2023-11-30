#ifndef MYTEST_HPP
#define MYTEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>
#include <esp_system.h>

#include "TaskTracker.hpp"

void testTask(void *pvParameters)
{
    while (true)
    {
        // Serial.println("Test task");
        delay(100);
    }
}

TEST(MyTest, Test1)
{

    TaskTracker::getInstance();
    int startFreeHeap = esp_get_free_heap_size();

    TaskHandle_t *taskHandle = new TaskHandle_t;

    xTASK_CREATE_TRACKED(testTask, "Test task", 2048, NULL, 1, taskHandle);

    delay(1000);

    vTASK_DELETE_TRACKED(taskHandle);

    delay(100);

    delete taskHandle;

    EXPECT_EQ(startFreeHeap, esp_get_free_heap_size());
}

#endif // MYTEST_HPP    2460