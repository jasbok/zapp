#include "dosbox_config_analyser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QRegExp>
#include <QStringList>
#include <QVector>

dosbox_config_analyser::mount::mount(const QString &command)
    : _command(command)
{
    _parse();
}

QChar dosbox_config_analyser::mount::drive() const
{
    return _drive;
}

QString dosbox_config_analyser::mount::path() const
{
    return _path;
}

void dosbox_config_analyser::mount::_parse()
{
    QStringList cmd = _command.trimmed().toLower().split(QRegExp("\\s+"), QString::SplitBehavior::SkipEmptyParts);
    if(cmd.first() == "mount" && cmd.size() >= 3){
        if(cmd[1].size() == 1){
            _drive = cmd[1].at(0);

            int path_index = 2;
            _path = _read_quoted_path(cmd, path_index).replace('\\','/');

            _command = QString("mount %1 %2").arg(_drive, _path);
        }
        else{
            qWarning() << "mount: Command drive must be a single letter: '" << cmd[1] << "'";
        }
    }
    else{
        qWarning() << "Command string is not a mount command: " << _command;
    }
}

QString dosbox_config_analyser::mount::command() const
{
    return _command;
}

QString dosbox_config_analyser::mount::to_string() const
{
    return QString("[drive='%1',path='%2']").arg(_drive, _path);
}

dosbox_config_analyser::imgmount::imgmount(const QString &command)
    : _command(command)
{
    _parse();
}

QChar dosbox_config_analyser::imgmount::drive() const
{
    return _drive;
}

QString dosbox_config_analyser::imgmount::path() const
{
    return _path;
}

QString dosbox_config_analyser::imgmount::t() const
{
    return _t;
}

QString dosbox_config_analyser::imgmount::fs() const
{
    return _fs;
}

QString dosbox_config_analyser::imgmount::command() const
{
    return _command;
}

QString dosbox_config_analyser::imgmount::to_string() const
{
    return QString("[drive='%1',path='%2',t='%3',fs='%4']").arg(_drive, _path, _t, _fs);
}

void dosbox_config_analyser::imgmount::_parse()
{
    QStringList cmd = _command.trimmed().toLower().split(QRegExp("\\s+"), QString::SplitBehavior::SkipEmptyParts);
    if(cmd.first() == "imgmount" && cmd.size() >= 3){
        if(cmd[1].size() == 1){
            _drive = cmd[1].at(0);

            int path_index = 2;
            _path = _read_quoted_path(cmd, path_index).replace('\\','/');

            _command = QString("imgmount %1 %2").arg(_drive, _path);

            for(int i = path_index; i < cmd.size(); i+=2){
                if(cmd[i] == "-t"){
                    _t = cmd[i+1];
                    _command += " -t " + _t;
                }
                else if(cmd[i] == "-fs"){
                    _fs = cmd[i+1];
                    _command += " -fs " + _fs;
                }
            }
        }
        else{
            qWarning() << "imgmount: Command drive must be a single letter: '" << cmd[1] << "'";
        }
    }
    else{
        qWarning() << "Command string is not an imgmount command: " << _command;
    }
}

dosbox_config_analyser::dosbox_config_analyser(const QString &path)
    : _path(path)
{
    _parse();
}

QSharedPointer<dosbox_config_analyser::mount> dosbox_config_analyser::mount_cmd() const
{
    return _mount_cmd;
}

QSharedPointer<dosbox_config_analyser::imgmount> dosbox_config_analyser::imgmount_cmd() const
{
    return _imgmount_cmd;
}

QStringList dosbox_config_analyser::dos_cmds() const
{
    return _dos_cmds;
}

QStringList dosbox_config_analyser::all_cmds() const
{
    return _all_cmds;
}

dosbox_config_analyser::section::section(const QString &name)
    : _name(name), _cmds()
{}

QStringList dosbox_config_analyser::section::commands() const
{
    return _cmds;
}

void dosbox_config_analyser::section::add_command(const QString &command)
{
    _cmds.append(command);
}

QString dosbox_config_analyser::section::name() const
{
    return _name;
}

void dosbox_config_analyser::_parse()
{
    QFile file(_path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString line;
        QRegExp section_regex("^\\[.*\\]$");

        QList<section> sections;
        QTextStream stream(&file);
        while(!stream.atEnd()){
            line = stream.readLine().trimmed().toLower();
            if(line.size() > 0 && line.at(0) != '#'){
                if(section_regex.exactMatch(line)){
                    sections.push_back(section(line.mid(1, line.size()-2).trimmed()));
                }
                else if(sections.size() > 0){
                    sections.back().add_command(line);
                }
            }
        }

        for(section section : sections){
            if(section.name() == "autoexec"){
                QRegExp mount_regex("^mount\\s");
                QRegExp imgmount_regex("^imgmount\\s");

                for(QString cmd : section.commands()){
                    if(cmd.contains(mount_regex)){
                        _mount_cmd = QSharedPointer<mount>(new mount(cmd));
                        _all_cmds.push_back(_mount_cmd->command());
                    }
                    else if(cmd.contains(imgmount_regex)){
                        _imgmount_cmd = QSharedPointer<imgmount>(new imgmount(cmd));
                        _all_cmds.push_back(_imgmount_cmd->command());
                    }
                    else{
                        _dos_cmds.push_back(cmd);
                        _all_cmds.push_back(cmd);
                    }
                }
            }
        }
    }
    else{
        qWarning() << "Unable to open dosbox config file: " << _path;
    }
}

QString dosbox_config_analyser::_read_quoted_path(const QStringList &tokens, int &index)
{
    QString quoted = tokens[index++];
    if(tokens[index-1].left(1) == "\""){
        while(index < tokens.size() && quoted.right(1) != "\""){
            quoted += " " + tokens[index++];
        }
    }

    return quoted;
}
