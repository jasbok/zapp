#ifndef SCUMMVM_CONFIG_ANALYSER_H
#define SCUMMVM_CONFIG_ANALYSER_H

#include <QString>
#include <QStringList>
#include <QVector>

class scummvm_config_analyser
{
public:
    scummvm_config_analyser(const QString& path);
    void remove_scummvm_section();

private:
    QString _path;
    QVector<QStringList> _sections;

    void _process();
    void _write();
};

#endif // SCUMMVM_CONFIG_ANALYSER_H
