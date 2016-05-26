#include "innoextract.h"
#include "configs/config.h"

#include "QDebug"
#include "QProcess"

innoextract::innoextract(const QString &target)
    : _target(target)
{}

bool innoextract::extract(const QString& destination) const
{
    QProcess process;
    process.start(config::instance().innoextract_bin(), QStringList() << "-e" << "-L" << "-d" << destination << _target);
    process.waitForFinished(-1);
    qInfo() << process.readAllStandardOutput();
    qWarning() << process.readAllStandardError();
    return process.exitCode() == 0;
}
