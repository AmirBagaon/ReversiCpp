//
// Created by or on 17/01/18.
//

#ifndef REVERSI_THREADPOOL_H
#define REVERSI_THREADPOOL_H


#include "Task.h"
#include <queue>
#include <pthread.h>

using namespace std;
class ThreadPool {
public:
    /**
     * constructor
     * @param threadsNum number of threads.
     */
    ThreadPool(int threadsNum);
    /**
     * add task to the queue
     * @param task
     */
    void addTask(Task *task);
    /**
     * terminate the thread
     */
    void terminate();
    /**
     * destructor
     */
    virtual ~ThreadPool();

private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;
    static void *execute(void *arg);
};


#endif //REVERSI_THREADPOOL_H
