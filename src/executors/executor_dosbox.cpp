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
    qDebug() << "Using working directory: " << _working_dir;
    return _dosbox.run();
}

void executor_dosbox::_configure_for_executable(const QString& target, const QFileInfo& file_info)
{
    _dosbox = _dosbox.executable(target);
}

void executor_dosbox::_configure_for_config(const QString& target)
{
    dosbox_config_analyser dca(target);

//    if(dca.mount_cmd() != nullptr) {
//        _dosbox = _dosbox.mount(dca.mount_cmd()->drive(), dca.mount_cmd()->path());
//    }
//    if(dca.imgmount_cmd() != nullptr) {
//        if(dca.imgmount_cmd()->t().isEmpty() || dca.imgmount_cmd()->fs().isEmpty()) {
//            _dosbox = _dosbox.imgmount(dca.imgmount_cmd()->drive(), dca.imgmount_cmd()->path());
//        } else {
//            _dosbox = _dosbox.imgmount(dca.imgmount_cmd()->drive(),
//                                       dca.imgmount_cmd()->path(),
//                                       dca.imgmount_cmd()->t(),
//                                       dca.imgmount_cmd()->fs());
//        }
//    }
//    for(QString cmd : dca.dos_cmds()) {
//        _dosbox = _dosbox.command(cmd);
//    }
    for(QString cmd : dca.all_cmds()) {
        _dosbox = _dosbox.command(cmd);
    }
}
