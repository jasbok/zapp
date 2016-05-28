#ifndef TARGET_ANALYSER_H
#define TARGET_ANALYSER_H

#include "name_analyser.h"
#include <QMap>
#include <QString>
#include <QStringList>

class target_analyser
{
public:
    target_analyser(const QString& data_path);

    QString data_path() const;
    QStringList files() const;
    QStringList executables() const;
    QStringList configs() const;

    QStringList application_executables() const;
    QStringList setup_executables() const;
    QStringList documentation_executables() const;
    QStringList other_executables() const;

    QStringList find_files_by_name(const QString& name) const;

private:
    QString _data_path;
    QStringList _files;
    QStringList _executables;
    QStringList _configs;

    QMap<QString, name_analyser> _name_analysers;
    QStringList _stop_executable_list;
    QStringList _application_executable_list;
    QStringList _setup_executable_list;
    QStringList _documentation_executable_list;

    QStringList _application_executables;
    QStringList _setup_executables;
    QStringList _documentation_executables;
    QStringList _other_executables;

    bool _classify_executable(const QString& path, const QString& basename, const QStringList& classification_list, QStringList& classified_list);

    void _process();
};

#endif // TARGET_ANALYSER_H
