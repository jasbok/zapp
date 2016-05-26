#include "target_analyser.h"
#include <QDirIterator>
#include <QFileInfo>

target_analyser::target_analyser(const QString &data_path)
    : _data_path(data_path)
{
    _process();
}

QStringList target_analyser::files() const
{
    return _files;
}

QStringList target_analyser::executables() const
{
    return _executables;
}

QStringList target_analyser::configs() const
{
    return _configs;
}

QStringList target_analyser::find_files_by_name(const QString &name) const
{
    QStringList results;
    for(QString file : _files){
        QFileInfo file_info(file);
        if(file_info.fileName() == name){
            results.push_back(file);
        }
    }
    return results;
}

void target_analyser::_process()
{
    QDirIterator it(_data_path, QDirIterator::Subdirectories);
    while(it.hasNext()){
        _files.push_back(it.next());
    }

    for(QString path : _files){
        QFileInfo info(path);
        QString suffix = info.suffix().toLower();

        if(suffix == "exe" || suffix == "com" || suffix == "bat" || suffix == "sh"){
            _executables.push_back(path);
        }
        if(suffix.contains("conf")){
            _configs.push_back(path);
        }
    }
}
