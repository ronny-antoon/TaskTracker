#ifndef TASK_TRACKER_HPP
#define TASK_TRACKER_HPP

#include <Arduino.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define INCLUDE_uxTaskGetStackHighWaterMark 1 // TaskHandle_t
#define INCLUDE_vTaskDelete 1                 // vTaskDelete

/**
 * @brief Structure to store information about a tracked task.
 */
struct TaskInfo
{
    TaskHandle_t *m_taskHandle; ///< Task handle.
    char const *m_taskName;     ///< Task name.
    uint32_t m_maxStack;        ///< Maximum stack size.
    char const *m_path;         ///< File path where the task is created.
};

/**
 * @brief Singleton class to track and manage tasks.
 */
class TaskTracker
{
private:
    std::vector<TaskInfo> taskList; ///< List to store tracked tasks.
    TaskTracker();                  ///< Private constructor.

public:
    /**
     * @brief Get the singleton instance of TaskTracker.
     * @return TaskTracker instance.
     */
    static TaskTracker &getInstance();

    /**
     * @brief Add a task to the tracking list.
     * @param taskHandle Task handle.
     * @param taskName Task name.
     * @param maxStack Maximum stack size.
     * @param path File path where the task is created.
     */
    void addTask(
        TaskHandle_t *taskHandle, char const *taskName,
        uint32_t maxStack, char const *const path);

    /**
     * @brief Remove a task from the tracking list.
     * @param taskHandle Task handle.
     */
    void removeTask(TaskHandle_t *taskHandle);

    /**
     * @brief Print the list of tracked tasks.
     */
    void printTaskList();

    TaskTracker(TaskTracker const &) = delete;
    void operator=(TaskTracker const &) = delete;
};

/**
 * @brief Macro to create a tracked task.
 */
#define xTASK_CREATE_TRACKED(_pvTaskCode_, _pcName_, _usStackDepth_, _pvParameters_, _uxPriority_, _pxCreatedTask_) \
    xTaskCreate(_pvTaskCode_, _pcName_, _usStackDepth_, _pvParameters_, _uxPriority_, _pxCreatedTask_);             \
    TaskTracker::getInstance().addTask(_pxCreatedTask_, _pcName_, _usStackDepth_, __FILENAME__);

/**
 * @brief Macro to delete a tracked task.
 */
#define vTASK_DELETE_TRACKED(_pvTaskCode_) \
    vTaskDelete(*_pvTaskCode_);            \
    TaskTracker::getInstance().removeTask(_pvTaskCode_);

#endif // TASK_TRACKER_HPP
