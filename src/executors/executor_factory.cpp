#include "executor_factory.h"
#include "executor_dosbox.h"

#include <QtDebug>

QSharedPointer<executor> executor_factory::new_executor ( const type_analyser::target_type& type )
{
        QSharedPointer<executor> exec;
        switch ( type ) {
        case type_analyser::DOSBOX:
                exec = QSharedPointer<executor> ( new executor_dosbox() );
                qInfo() << "Created dosbox executor.";
                break;
        case type_analyser::SCUMMVM:
                qInfo() << "Created ScummVM executor.";
                break;
        case type_analyser::WIN:
                qInfo() << "Created wine executor.";
                break;
        case type_analyser::UNKNOWN:
                exec = QSharedPointer<executor> ( new executor_dosbox() );
                qInfo() << "Unknown program type... created dosbox executor.";
                break;
        }
        return exec;
}
