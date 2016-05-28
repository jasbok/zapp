#include "patcher_copy.h"

#include <QDir>
#include <QtDebug>
#include <QFileInfo>

#include <sys/time.h>

patcher_copy::patcher_copy(const QString &original, const QString &modified)
    : patcher(original, modified)
{}

void patcher_copy::diff () const
{
    QDir(patched()).removeRecursively();

    for(QString modified_file : modified_files()){
        QFile original_file(original() + "/" + modified_file);
        QString patch_path = patched() + "/" + modified_file;
        QFile patch_file(patch_path);

        if(patch_file.exists()){
            patch_file.remove();
        }
        else{
            QDir().mkpath(QFileInfo(patch_path).absolutePath());
        }

        original_file.copy(patch_path);
    }
}

void patcher_copy::patch () const
{
    for(QString patched_file : patched_files()){
        QString original_path = original() + "/" + patched_file;
        QFile original_file(original_path);

        QFile patch_file(patched() + "/" + patched_file);

        if(original_file.exists()){
            original_file.remove();
        }
        else{
            QDir().mkpath(QFileInfo(original_path).absolutePath());
        }

        patch_file.copy(original_path);
        if(utimes(original_path.toLocal8Bit(), NULL)){
            qCritical() << "Could not update patch file time.";
        }
    }
}
