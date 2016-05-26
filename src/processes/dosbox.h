#ifndef DOSBOX_H
#define DOSBOX_H

#include "analysers/dosbox_config_analyser.h"
#include "analysers/type_analyser.h"

#include <QString>
#include <QStringList>

class dosbox
{
public:
    dosbox();

    dosbox& executable(const QString& executable);
    dosbox& mount(const QChar& drive, const QString& path);
    dosbox& imgmount(const QChar& drive, const QString& path);
    dosbox& imgmount(const QChar& drive, const QString& path, const QString& t, const QString& fs);
    dosbox& command(const QString& command);
    dosbox& working_dir(const QString& working_dir);

    bool run() const;

private:
    QString _wd;
    QString _executable;
    QStringList _args;
};

#endif // DOSBOX_H
