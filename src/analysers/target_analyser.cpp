#include "target_analyser.h"
#include <QDirIterator>
#include <QFileInfo>

target_analyser::target_analyser(const QString &data_path)
    : _data_path(data_path),
      _stop_executable_list(QStringList{"foxitreader"}),
      _application_executable_list(QStringList{"main", "start", "play"}),
      _setup_executable_list(QStringList{"install", "setup", "sound", "blaster", "setmain"}),
      _documentation_executable_list(QStringList{"catalog", "order", "readme", "help", "hint"})
{
    _process();
}

QString target_analyser::data_path() const
{
    return _data_path;
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

QStringList target_analyser::application_executables() const
{
    return _application_executables;
}

QStringList target_analyser::setup_executables() const
{
    return _setup_executables;
}

QStringList target_analyser::documentation_executables() const
{
    return _documentation_executables;
}

QStringList target_analyser::other_executables() const
{
    return _other_executables;
}

QStringList target_analyser::find_files_by_name(const QString &name) const
{
    QStringList results;
    for(QString file : _files) {
        QFileInfo file_info(file);
        if(file_info.fileName() == name) {
            results.push_back(file);
        }
    }
    return results;
}

bool target_analyser::_classify_executable(const QString &path, const QString &basename, const QStringList &classification_list, QStringList &classified_list)
{
    for(QString item : classification_list) {
        if(basename.contains(item)) {
            classified_list << path;
            return true;
        }
    }
    return false;
}

void target_analyser::_process()
{
    name_analyser na(QFileInfo(_data_path).baseName());

    QDirIterator it(_data_path, QDirIterator::Subdirectories);
    while(it.hasNext()) {
        _files.push_back(it.next());
    }

    QString target_name = QFileInfo(_data_path).baseName();
    _name_analysers.insert(target_name, name_analyser(target_name));

    for(QString path : _files) {
        QFileInfo info(path);
        QString basename = info.baseName().toLower();
        QString suffix = info.suffix().toLower();

        if(!_stop_executable_list.contains(basename) && (suffix == "exe" || suffix == "com" || suffix == "bat" || suffix == "sh")) {
            _executables << path;

            QString parent_name = QFileInfo(QFileInfo(path).absoluteDir().path()).baseName();
            if(_name_analysers.find(parent_name) == _name_analysers.end()) {
                _name_analysers.insert(parent_name, name_analyser(parent_name));
            }

            if(     _application_executable_list.contains(basename) ||
                    _name_analysers[target_name].keywords().contains(basename) ||
                    _name_analysers[parent_name].keywords().contains(basename) ||
                    _name_analysers[target_name].abbreviations().contains(basename) ||
                    _name_analysers[parent_name].abbreviations().contains(basename)
              ) {
                _application_executables << path;
            } else {
                if (!(_classify_executable(path, basename, _setup_executable_list, _setup_executables) ||
                        _classify_executable(path, basename, _documentation_executable_list, _documentation_executables))) {
                    _other_executables << path;
                }
            }
        } else if(suffix.contains("conf")) {
            _configs.push_back(path);
        }
    }
}
