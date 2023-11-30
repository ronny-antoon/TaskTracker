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
    addTask(setupTaskHandle, setupTaskName, 10000, (char *)__FILENAME__, __LINE__);
}

TaskTracker &TaskTracker::getInstance()
{
    // Singleton instance creation
    static TaskTracker instance;
    return instance;
}

void TaskTracker::addTask(TaskHandle_t *taskHandle, char const *taskName, uint32_t maxStack, char *path, int line)
{
    // Create a TaskInfo object and populate its fields
    TaskInfo taskInfo;
    taskInfo.m_taskHandle = taskHandle;
    taskInfo.m_taskName = taskName;
    taskInfo.m_maxStack = maxStack;
    taskInfo.m_path = path;
    taskInfo.m_line = line;

    // Add the TaskInfo object to the task list
    taskList.push_back(taskInfo);
}

void TaskTracker::removeTask(TaskHandle_t *taskHandle)
{
    // Iterate through the task list
    for (auto it = taskList.begin(); it != taskList.end(); ++it)
    {
        // If the task handle matches, remove the task from the list
        if (it->m_taskHandle == taskHandle)
        {
            taskList.erase(it);
            taskList.shrink_to_fit();
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
        Serial.printf("Task %d      Handle: %p      Name: %s      Free Stack: %d / %d      Path: %s:%d\n",
                      i,
                      it->m_taskHandle,
                      it->m_taskName,
                      uxTaskGetStackHighWaterMark(it->m_taskHandle),
                      it->m_maxStack,
                      it->m_path,
                      it->m_line);
    }
    Serial.println("///////////////////////////////////////////////");
}
