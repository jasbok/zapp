#include "executor_dosbox.h"
#include <QtDebug>
#include <QTextStream>

executor_dosbox::executor_dosbox()
    : _dosbox()
{}

void executor_dosbox::target(const QString& target){
    QFileInfo file_info(target);
    QString suffix = file_info.suffix().toLower();
    if(suffix == "exe" || suffix == "bat" || suffix == "com") {
        _configure_for_executable(target, file_info);
    } else {
        _configure_for_config(target);
    }
}

void executor_dosbox::working_dir(const QString &working_dir)
{
    _working_dir = working_dir;
    _dosbox = _dosbox.working_dir(_working_dir);
}

bool executor_dosbox::run() const
{
    return _dosbox.run();
}

void executor_dosbox::_configure_for_executable(const QString& target, const QFileInfo& file_info)
{
    QFileInfo target_info(target);
    _working_dir = target_info.absolutePath();

    QString target_dir = QFileInfo(_working_dir).fileName();
    target_dir = target_dir.size() <= 8 ? target_dir :
                                          target_dir.remove(' ').left(6) + "~1";
    _dosbox = _dosbox.working_dir(_working_dir)
                     .command("mount c ..")
                     .command("c:")
                     .command(QString("cd %1").arg(target_dir))
                     .command(target_info.fileName());
}

void executor_dosbox::_configure_for_config(const QString& target)
{
    dosbox_config_analyser dca(target);
    _dosbox = _dosbox.arg("-userconf").arg("-conf").arg(target);
}
