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
    int m_line;                 ///< Line number where the task is created.
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
        uint32_t maxStack, char *path, int line);

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
 * @brief Macro to add a task to the tracker.
 *
 * @note This macro should be used after the task is created.
 * @note DONT USE THIS MACRO IF YOU ARE USING xTASK_CREATE_TRACKED MACRO.
 */
#define xADD_TAST_TO_TRACKER(_handleTask_x, _taskName_x, _stackDepth_x) \
    TaskTracker::getInstance().addTask(_handleTask_x, _taskName_x, _stackDepth_x, __FILENAME__, __LINE__);

/////////////////////////////////////////////////////////////////////////////////////////

#define xPRINT_TASK_LIST() TaskTracker::getInstance().printTaskList();

/**
 * @brief Macro to create a tracked task.
 */
#define xTASK_CREATE_TRACKED(_taskCode_x, _taskName_x, _stackDepth_x, _parameter_x, _taskPriority_x, _handleTask_x) \
    xTaskCreate(_taskCode_x, _taskName_x, _stackDepth_x, _parameter_x, _taskPriority_x, _handleTask_x);             \
    xADD_TAST_TO_TRACKER(_handleTask_x, _taskName_x, _stackDepth_x);

/**
 * @brief Macro to delete a tracked task.
 */
#define xTASK_DELETE_TRACKED(_handleTask_x) \
    vTaskDelete(*_handleTask_x);            \
    TaskTracker::getInstance().removeTask(_handleTask_x);

#endif // TASK_TRACKER_HPP
