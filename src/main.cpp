#include <Arduino.h>
#include <TaskTracker.hpp>

void funcTask1(void *parameter)
{
  while (1)
  {
    Serial.printf("task1 High Water mark = %d\n", uxTaskGetStackHighWaterMark(nullptr));
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting...");

  TaskHandle_t newHandle;

  xTASK_CREATE_TRACKED(funcTask1, "tmpName", 2048, nullptr, 1, &newHandle);

  delay(5000);

  xPRINT_TASK_LIST();

  xTASK_DELETE_TRACKED(&newHandle);

  newHandle = nullptr;
}

void loop()
{
  xPRINT_TASK_LIST();
  delay(5000);
}
