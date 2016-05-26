#ifndef DOSBOX_CONFIG_ANALYSER_H
#define DOSBOX_CONFIG_ANALYSER_H

#include <QSharedPointer>
#include <QString>

class dosbox_config_analyser
{
public:

    class mount{
    public:
        mount(const QString& command);

        QChar drive() const;
        QString path() const;
        QString command() const;
        QString to_string() const;

    private:
        QChar _drive;
        QString _path;
        QString _command;

        void _parse();
    };

    class imgmount{
    public:
        imgmount(const QString& command);

        QChar drive() const;
        QString path() const;
        QString t() const;
        QString fs() const;
        QString command() const;
        QString to_string() const;

    private:
        QChar _drive;
        QString _path, _t, _fs;
        QString _command;

        void _parse();
    };

    class section{
    public:
        section(const QString& name);
        QString name() const;
        QStringList commands() const;
        void add_command(const QString& command);

    private:
        QString _name;
        QStringList _cmds;
    };

    dosbox_config_analyser(const QString& path);

    QSharedPointer<mount> mount_cmd() const;
    QSharedPointer<imgmount> imgmount_cmd() const;
    QStringList dos_cmds() const;
    QStringList all_cmds() const;

private:
    QString _path;
    QSharedPointer<mount> _mount_cmd;
    QSharedPointer<imgmount> _imgmount_cmd;
    QStringList _dos_cmds;
    QStringList _all_cmds;

    void _parse();
    static QString _read_quoted_path(const QStringList& tokens, int& index);
};

#endif // DOSBOX_CONFIG_ANALYSER_H
