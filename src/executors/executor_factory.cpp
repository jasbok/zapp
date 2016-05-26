#include "executor_factory.h"
#include "executor_dosbox.h"

QSharedPointer<executor> executor_factory::new_executor(const type_analyser::target_type& type)
{
    QSharedPointer<executor> exec;
    switch(type){
        case type_analyser::DOSBOX:
            exec = QSharedPointer<executor>(new executor_dosbox());
            break;
        case type_analyser::SCUMMVM:
            break;
        case type_analyser::WIN:
            break;
        case type_analyser::UNKNOWN:
            break;
    }
    return exec;
}
