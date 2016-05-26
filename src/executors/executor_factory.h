#ifndef EXECUTOR_FACTORY_H
#define EXECUTOR_FACTORY_H

#include "executor.h"
#include "analysers/type_analyser.h"
#include <QSharedPointer>

class executor_factory
{
public:
    static QSharedPointer<executor> new_executor(const type_analyser::target_type& type);

private:
};

#endif // EXECUTOR_FACTORY_H
