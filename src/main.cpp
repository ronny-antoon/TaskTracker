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

TaskHandle_t *newHandle = new TaskHandle_t;
void setup()
{
  Serial.begin(115200);
  delay(1000);
  // newHandle = TaskHandle_t;
  xTASK_CREATE_TRACKED(funcTask1, "task1", 2048, nullptr, 1, newHandle);
  delay(1000);
}

int i = 0;
void loop()
{
  i++;
  // print all tasks
  TaskTracker::getInstance().printTaskList();
  if (i == 5)
  {
    vTASK_DELETE_TRACKED(newHandle);
  }

  if (i == 8)
  {
    xTASK_CREATE_TRACKED(funcTask1, "task1", 2048, nullptr, 1, newHandle);
    i = 0;
  }

  delay(10000);
}
