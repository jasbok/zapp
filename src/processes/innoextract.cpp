#include "innoextract.h"
#include "configs/config.h"

#include <QDebug>
#include <QTextStream>

innoextract::innoextract(const QString &target)
    : _target(target)
{}

bool innoextract::extract(const QString& destination) const
{
    QProcess process;
    QObject::connect(&process, &QProcess::readyReadStandardOutput, [&](){
        QTextStream(::stdout) << process.readAllStandardOutput();
    });
    QObject::connect(&process, &QProcess::readyReadStandardError, [&](){
        QTextStream(::stderr) << process.readAllStandardError();
    });

    process.start(config::instance().innoextract_bin(), QStringList() << "-e" << "-L" << "-d" << destination << _target);
    process.waitForFinished(-1);
    return process.exitCode() == 0;
}
