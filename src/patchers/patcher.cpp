#include "patcher.h"

#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QtDebug>

patcher::patcher(const QString &original, const QString &patched)
    : _original(original), _patched(patched)
{}

bool patcher::timestamp_exists () const
{
    return QFile(_original + "/.timestamp").exists();
}

void patcher::create_timestamp () const
{
    QFile timestamp(_original + "/.timestamp");
    if(!timestamp.exists()){
        if(timestamp.open(QIODevice::WriteOnly)){
            timestamp.close();
        }
        else{
            qWarning() << "Unable to write timestamp: " + _original + "/.timestamp";
        }
    }
}

QDateTime patcher::read_timestamp () const
{
    QDateTime timestamp;
    QFileInfo timestamp_info(_original + "/.timestamp");
    if(timestamp_info.exists()){
        timestamp = timestamp_info.lastModified();
    }
    return timestamp;
}

QStringList patcher::modified_files() const{
    QStringList modified_files;
    QDateTime timestamp = read_timestamp();

    QDirIterator it ( _original, QDirIterator::Subdirectories );
    while ( it.hasNext() ) {
        QString file = it.next();
        if(QFileInfo(file).lastModified() > timestamp){
            modified_files << file.right(file.size() - _original.size());
        }
    }
    return modified_files;
}

QStringList patcher::patched_files() const
{
    QStringList patched_files;
    QDirIterator it ( _patched, QDirIterator::Subdirectories );
    while ( it.hasNext() ) {
        QString file = it.next();
        patched_files << file.right(file.size() - _patched.size());
    }
    return patched_files;
}

QString patcher::original() const
{
    return _original;
}

QString patcher::patched() const
{
    return _patched;
}
