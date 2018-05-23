//
// Created by or on 17/01/18.
//

#ifndef REVERSI_TASK_H
#define REVERSI_TASK_H


class Task {
public:
    /**
     * constructor
     * @param func function
     * @param arg argument
     */
    Task(void * (*func)(void *arg), void* arg) : func(func), arg(arg) {}
    /**
     * execute the function with the args
     */
    void execute() {
        func(arg);
    }
    /**
     * destructor
     */
    virtual ~Task() {}
private:
    void * (*func)(void *arg);
    void *arg;
};


#endif //REVERSI_TASK_H
