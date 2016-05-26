#ifndef MENU_H
#define MENU_H

#include "analysers/target_analyser.h"
#include <QMap>
#include <QString>

class menu
{
public:
    menu(const target_analyser& analyser);
    QStringList display();
    QString selection(QChar option);

private:
    QStringList _display;
    QMap<QChar, QString> _options;
};

#endif // MENU_H
