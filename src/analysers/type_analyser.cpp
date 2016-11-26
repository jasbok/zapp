#include "type_analyser.h"

#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QMap>

type_analyser::type_analyser(const target_analyser& ta)
    : _type(target_type::UNKNOWN)
{
    _process(ta);
}

type_analyser::target_type type_analyser::type() const
{
    return _type;
}

QString type_analyser::working_dir() const
{
    return _working_dir;
}

void type_analyser::_process(const target_analyser& ta)
{
    _type = _analyse_type(ta);

    QString win_exec;
    switch(_type) {
    case DOSBOX:
        win_exec = "dosbox.exe";
        break;
    case SCUMMVM:
        win_exec = "scummvm.exe";
        break;
    case WIN:
    case UNKNOWN:
        break;
    }

    for(QString exec : ta.executables()){
        QFileInfo exec_info = QFileInfo(exec);
        QString fileName = exec_info.fileName().toLower();
        if(fileName == "start.sh" || fileName == win_exec){
            _working_dir = exec_info.absolutePath();
            break;
        }
    }
}

type_analyser::target_type type_analyser::_analyse_type(const target_analyser& ta)
{
    target_type result = target_type::UNKNOWN;
    QMap<target_type, int> type_refs;

    for(QString path : ta.executables()) {
        _sum_refs(type_refs, _analyse_file_path(path));
    }
    for(QString path : ta.configs()) {
        _sum_refs(type_refs, _analyse_file_path(path));
        _sum_refs(type_refs, _analyse_file_contents(path));
    }

    int high = 0;
    QMapIterator<target_type, int> it(type_refs);
    while(it.hasNext()) {
        it.next();
        if(it.value() > high) {
            high = it.value();
            result = it.key();
        }
    }

    return result;
}

QMap<type_analyser::target_type, int> type_analyser::_analyse_file_path(const QString &file_path)
{
    QMap<target_type, int> type_refs;
    QString fp = file_path.toLower();

    const QStringList msdos_files{
        "dosbox", "dos4gw", "catalog", "dealers", "order"
    };

    const QStringList scummvm_files{
        "scummvm"
    };

    for(QString ref : msdos_files) {
        if(fp.contains(ref)) {
            type_refs[target_type::DOSBOX]++;
            break;
        }
    }

    for(QString ref : scummvm_files) {
        if(fp.contains(ref)) {
            type_refs[target_type::SCUMMVM]++;
            break;
        }
    }

    return type_refs;
}

QMap<type_analyser::target_type, int> type_analyser::_analyse_file_contents(const QString &file_path)
{
    QMap<target_type, int> type_refs;
    QFile file(file_path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString contents = QTextStream(&file).readAll();

        if(contents.contains("dosbox")) {
            type_refs[target_type::DOSBOX]++;
        } else if(contents.contains("scummvm")) {
            type_refs[target_type::SCUMMVM]++;
        }
    } else {
        qWarning() << "Unable to open file to read contents: " << file_path;
    }

    return type_refs;
}

void type_analyser::_sum_refs(QMap<type_analyser::target_type, int> &a, const QMap<type_analyser::target_type, int> &b)
{
    QMapIterator<target_type, int> it(b);
    while(it.hasNext()) {
        it.next();
        a[it.key()] += it.value();
    }
}
