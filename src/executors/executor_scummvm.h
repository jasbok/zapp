#ifndef EXECUTOR_SCUMMVM_H
#define EXECUTOR_SCUMMVM_H

#include "executor.h"

class executor_scummvm : public executor{
public:
    executor_scummvm();
    virtual bool run() const;
    virtual void target(const QString & target);
    virtual void working_dir(const QString & working_dir);
    
private:
};

#endif
