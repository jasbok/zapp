#ifndef EXECUTOR_DOSBOX_H
#define EXECUTOR_DOSBOX_H

#include "executor.h"
#include "processes/dosbox.h"
#include "analysers/type_analyser.h"
#include <QFileInfo>

class executor_dosbox : public executor
{
public:
    executor_dosbox();
    virtual void target(const QString& target);
    virtual void working_dir(const QString& working_dir);
    virtual bool run() const;

private:
    dosbox _dosbox;
    QString _target;
    QString _working_dir;

    void _configure_for_executable(const QString &target, const QFileInfo &file_info);
    void _configure_for_config(const QString &target);

    void lowercase_file_contents(const QString& path) const;
};

#endif // EXECUTOR_DOSBOX_H
