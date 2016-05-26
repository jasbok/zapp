#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QString>

class executor
{
public:
    virtual ~executor(){};
    virtual void target(const QString& target) = 0;
    virtual void working_dir(const QString& working_dir) = 0;
    virtual bool run() const = 0;
};

#endif // EXECUTOR_H
