#ifndef MENU_H
#define MENU_H

#include "analysers/target_analyser.h"
#include <QMap>
#include <QString>
#include <QVector>

class menu
{
public:
    menu(const target_analyser& analyser);
    QStringList display();
    QString selection(QChar option);

private:
    target_analyser _target_analyser;
    QStringList _display;
    QMap<QChar, QString> _options;
    QVector<char> _option_chars;

    void _display_section(const QString &section_name, const QStringList &list, unsigned int& option);
};

#endif // MENU_H
