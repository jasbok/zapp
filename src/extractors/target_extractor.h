#ifndef TARGET_EXTRACTOR_H
#define TARGET_EXTRACTOR_H

#include <QString>
#include <QStringList>

class target_extractor
{
public:
    static QStringList& supported_archives(){
        static QStringList list{"zip", "gz", "tar", "7z", "xz"};
        return list;
    }

    enum target_type {
        FOLDER, ARCHIVE, RAR_ARCHIVE, EXE, UNKNOWN
    };

    target_extractor(const QString& target);
    target_extractor(const QString& target, target_type type);
    bool extract(const QString& destination);

private:
    QString _target;
    target_type _target_type;

    target_type determine_target_type(const QString& target);

    bool extract_innoextract(const QString& destination);
    bool extract_copy(const QString& destination);
};

#endif // TARGET_EXTRACTOR_H
