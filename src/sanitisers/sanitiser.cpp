#include "sanitiser.h"

#include "analysers/dosbox_config_analyser.h"
#include <QtDebug>
#include <QFile>
#include <QFileInfo>
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
    for(QString config : target_analyser.configs()){
        dosbox_config_analyser dca(config);

        if(dca.imgmount_cmd() != nullptr){
            QString imgmount_file = QFileInfo(dca.imgmount_cmd()->path().toLower().remove('"')).fileName();
            qDebug() << "imgmount file: " << imgmount_file;

            QStringList files = target_analyser.find_files_by_name(imgmount_file);
            if(files.size() == 1 && QFileInfo(files.first()).size() < 2e6){
                qDebug() << "Lowercasing file: " << files.first();
                lowercase_file_contents(files.first());
            }
        }
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
