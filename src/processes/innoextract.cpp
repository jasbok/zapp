#include "innoextract.h"
#include "configs/config.h"

#include <QDebug>
#include <QRegExp>
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

    process.start(config::instance().innoextract_bin(), QStringList() << "-em" << "-L" << "-d" << destination << _target);
    process.waitForFinished(-1);
    return process.exitCode() == 0;
}

QStringList innoextract::list() const
{
    QProcess process;
    QStringList files;
    QRegExp path_regex("(\".+\")");

    QObject::connect(&process, &QProcess::readyReadStandardOutput, [&](){
       // stdout << process.readAllStandardOutput();
    });
    QObject::connect(&process, &QProcess::readyReadStandardError, [&](){
        QTextStream(::stderr) << process.readAllStandardError();
    });

    process.start(config::instance().innoextract_bin(), QStringList() << "-lm" << _target);
    process.waitForFinished(-1);

    if(process.exitCode() == 0){
        for(QString output : process.readAllStandardOutput().split('\n')){
            path_regex.indexIn(output);
            if(path_regex.capturedTexts()[1].size() > 0){
                files << path_regex.capturedTexts()[1].remove('"');
            }
        }
    }

    return files;
}
