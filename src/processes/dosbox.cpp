#include "dosbox.h"
#include "configs/config.h"

#include "QDebug"
#include "QFileInfo"
#include "QProcess"

dosbox::dosbox()
{}

dosbox &dosbox::executable ( const QString &executable )
{
    _executable = executable;
    _args << executable;
    return *this;
}

dosbox &dosbox::arg(const QString &arg)
{
    _args << arg;
    return *this;
}

dosbox &dosbox::mount ( const QChar& drive, const QString& path )
{
    _args << "-c" << QString ( "mount %1 %2" ).arg ( drive, path );
    return *this;
}

dosbox &dosbox::imgmount ( const QChar& drive, const QString& path )
{
    _args << "-c" << QString ( "imgmount %1 %2" ).arg ( drive, path );
    return *this;
}

dosbox &dosbox::imgmount ( const QChar& drive, const QString& path, const QString& t, const QString& fs )
{
    _args << "-c" << QString ( "imgmount %1 %2 -t %3 -fs %4" ).arg ( drive, path, t, fs );
    return *this;
}

dosbox &dosbox::command ( const QString& command )
{
    _args << "-c" << command;
    return *this;
}

dosbox &dosbox::working_dir ( const QString &working_dir )
{
    _wd = working_dir;
    return *this;
}

bool dosbox::run() const
{
    QProcess process;
    QObject::connect(&process, &QProcess::readyReadStandardOutput, [&](){
        QTextStream(stdout) << process.readAllStandardOutput();
    });
    QObject::connect(&process, &QProcess::readyReadStandardError, [&](){
        QTextStream(stdout) << process.readAllStandardError();
    });

    if ( !_wd.isEmpty() ) {
        process.setWorkingDirectory ( _wd );
    }

    QTextStream(stdout) << "Starting dosbox... (" << config::instance().dosbox_bin() << ")\n";
    QTextStream(stdout) << "Working Directory: " << _wd << "\n";
    process.start ( config::instance().dosbox_bin(), _args );
    process.waitForFinished ( -1 );

    QTextStream(stdout) << "Process Exit Code... (" << process.exitCode() << ")\n";
    QTextStream(stdout) << process.readAllStandardError();

    return process.exitCode() == 0;
}















