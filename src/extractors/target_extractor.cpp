#include "target_extractor.h"
#include "config.h"
#include "innoextract.h"
#include "QDir"
#include "QFileInfo"
#include "QtDebug"

target_extractor::target_extractor(const QString &target)
    : _target(target), _target_type(determine_target_type(target))
{}

target_extractor::target_extractor(const QString &target, target_extractor::target_type type)
    : _target(target), _target_type(type)
{}

target_extractor::target_type target_extractor::determine_target_type(const QString& target)
{
    target_type type = target_type::UNKNOWN;

    QFileInfo file_info(target);
    QString suffix = file_info.suffix().toLower();

    if(file_info.isDir()){
        type = target_type::FOLDER;
    }
    else if(suffix == "exe"){
        type = target_type::EXE;
    }
    else if(suffix == "rar"){
        type = target_type::RAR_ARCHIVE;
    }
    else if(supported_archives().contains(suffix)){
        type = target_type::ARCHIVE;
    }

    return type;
}

bool target_extractor::extract_innoextract(const QString& destination)
{
    bool success = false;
    innoextract ie(_target);

    if(!(success = ie.extract(destination))){
        qWarning() << "Failed to extract target using innoextract.";
    }

    return success;
}

bool target_extractor::extract_copy(const QString &destination)
{
    bool success = false;

    return success;
}

bool target_extractor::extract(const QString& destination)
{
    bool success = false;
    QFileInfo target_info(_target);
    QFileInfo destination_info(destination);
    qDebug() << "Target Type: " << _target_type;
    qDebug() << "Extraction Destination: " << destination;

    if(!destination_info.exists()){
        QDir destination_dir(destination);
        destination_dir.mkpath(destination);

        switch (_target_type){
        case ARCHIVE:
        case RAR_ARCHIVE:
            break;
        case EXE:
            success = extract_innoextract(destination);
            break;
        case FOLDER:
            success = extract_copy(destination);
            break;
        case UNKNOWN:
            qWarning() << "Unknown target type, stopping extraction.";
            break;
        }
    }
    else{
        qInfo() << "Destination directory already exists... ignoring extraction request.";
    }

    return success;
}
