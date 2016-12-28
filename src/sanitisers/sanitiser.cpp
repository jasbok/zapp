#include "sanitiser.h"

#include "analysers/dosbox_config_analyser.h"
#include <QtDebug>
#include <QFile>
#include <QFileInfo>
#include <QSet>
#include <QStringList>
#include <QTextStream>

void sanitiser::sanitise_environment(const target_analyser& target_analyser, type_analyser::target_type type)
{
    switch(type){
        case type_analyser::DOSBOX:
            dosbox(target_analyser);
            break;
        case type_analyser::SCUMMVM:
        case type_analyser::WIN:
        case type_analyser::UNKNOWN:
            break;
    }
}

void sanitiser::dosbox(const target_analyser& target_analyser){
    QSet<QString> cue_files;

    for(QString config : target_analyser.configs()){
        sanitise_config(config);
        dosbox_config_analyser dca(config);

        if(dca.imgmount_cmd() != nullptr){
            QString imgmount_file = QFileInfo(dca.imgmount_cmd()->path().toLower().remove('"')).fileName();

            QStringList files = target_analyser.find_files_by_name(imgmount_file);
            if(files.size() == 1 && QFileInfo(files.first()).size() < 2e6){
                cue_files << files.first();
            }
        }
    }
    for(QString cue_file : cue_files){
        lowercase_file_contents(cue_file);
    }
}

void sanitiser::lowercase_file_contents(const QString &path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString contents = QTextStream(&file).readAll().toLower();
        file.close();

        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);
            stream << contents;
            file.close();
        }
    }
    else{
        qWarning() << "Could not open file for lowercasing operation: " << path;
    }
}

void sanitiser::sanitise_config(const QString &path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream (&file);
        QStringList contents;
        QString line;
        while(!(line = stream.readLine().trimmed()).isNull()){
            QString line_lower = line.toLower();
            if(line_lower.startsWith("#") ||
                    line_lower.startsWith(":") ||
                    line_lower.startsWith("echo") ||
                    line_lower.startsWith("choice")){
                contents << line;
            }
            else{
                contents << line_lower.replace("\\","/");
            }
        }
        file.close();

        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);

            for(QString line : contents){
                stream << line << "\n";
            }
            file.close();
        }
    }
    else{
        qWarning() << "Could not open file for sanitation operation: " << path;
    }
}
