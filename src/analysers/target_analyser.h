#ifndef TARGET_ANALYSER_H
#define TARGET_ANALYSER_H

#include <QString>
#include <QStringList>

class target_analyser
{
public:
    target_analyser(const QString& data_path);

    QStringList files() const;
    QStringList executables() const;
    QStringList configs() const;

    QStringList find_files_by_name(const QString& name) const;

private:
    QString _data_path;
    QStringList _files;
    QStringList _executables;
    QStringList _configs;

    void _process();
};

#endif // TARGET_ANALYSER_H
