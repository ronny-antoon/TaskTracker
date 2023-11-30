#include "TaskTracker.hpp"

TaskTracker::TaskTracker()
{
    // Get the handle of the setup task and its name
    TaskHandle_t *setupTaskHandle = new TaskHandle_t;
    *setupTaskHandle = xTaskGetCurrentTaskHandle();
    char *tmpName = pcTaskGetTaskName(nullptr);
    char *setupTaskName = (char *)malloc(strlen(tmpName) + 1);
    strcpy(setupTaskName, tmpName);

    // Add the setup task to the task list
    addTask(setupTaskHandle, setupTaskName, 10000, __FILENAME__);
}

TaskTracker &TaskTracker::getInstance()
{
    // Singleton instance creation
    static TaskTracker instance;
    return instance;
}

void TaskTracker::addTask(TaskHandle_t *taskHandle, char const *taskName, uint32_t maxStack, char const *const path)
{
    // Create a TaskInfo object and populate its fields
    TaskInfo taskInfo;
    taskInfo.m_taskHandle = taskHandle;
    taskInfo.m_taskName = taskName;
    taskInfo.m_maxStack = maxStack;
    taskInfo.m_path = path;

    // Add the TaskInfo object to the task list
    taskList.push_back(taskInfo);
}

void TaskTracker::removeTask(TaskHandle_t *taskHandle)
{
    // Iterate through the task list to find and remove the specified task
    for (auto it = taskList.begin(); it != taskList.end(); ++it)
    {
        if (it->m_taskHandle == taskHandle)
        {
            taskList.erase(it);
            break;
        }
    }
}

void TaskTracker::printTaskList()
{
    Serial.println("///////////////////////////////////////////////");
    int i = 0;
    // Iterate through the task list and print information for each task
    for (auto it = taskList.begin(); it != taskList.end(); ++it, ++i)
    {
        // Print task information
        Serial.printf("Task %d      Handle: %p      Name: %s      Free Stack: %d / %d      Path: %s\n",
                      i,
                      it->m_taskHandle,
                      it->m_taskName,
                      uxTaskGetStackHighWaterMark(*(it->m_taskHandle)),
                      it->m_maxStack,
                      it->m_path);
    }
    Serial.println("///////////////////////////////////////////////");
}
