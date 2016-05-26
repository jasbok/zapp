#ifndef TYPE_ANALYSER_H
#define TYPE_ANALYSER_H

#include "target_analyser.h"
#include <QMap>
#include <QString>
#include <QStringList>

class type_analyser
{
public:

    enum target_type {
        DOSBOX, SCUMMVM, WIN, UNKNOWN
    };

    static QString target_type_string(target_type type)
    {
        switch(type) {
        case DOSBOX:
            return "DOSBOX";
        case SCUMMVM:
            return "SCUMMVM";
        case WIN:
            return "WIN";
        case UNKNOWN:
            return "UNKNOWN";
        }

        return "UNKNOWN";
    }

    type_analyser(const target_analyser& ta);

    target_type type() const;
    QString working_dir() const;

private:
    QString _data_path;
    target_type _type;
    QString _working_dir;

    void _process(const target_analyser& ta);
    target_type _analyse_type(const target_analyser& ta);
    QMap<target_type, int> _analyse_file_path(const QString& file_path);
    QMap<target_type, int> _analyse_file_contents(const QString& file_path);

    void _sum_refs(QMap<target_type, int>& a, const QMap<target_type, int>& b);
};

#endif // TYPE_ANALYSER_H
