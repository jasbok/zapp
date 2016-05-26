#include "menu.h"

menu::menu(const target_analyser& analyser)
    : _display(), _options()
{
    char option = 'a';
    _display << "Executables:";
    for(QString exec : analyser.executables()){
        _options[QChar(option)] = exec;
        _display << QString("[%1] %2").arg(QChar(option++), exec);
    }
    _display << "Configurations:";
    for(QString exec : analyser.configs()){
        _options[QChar(option)] = exec;
        _display << QString("[%1] %2").arg(QChar(option++), exec);
    }
}

QStringList menu::display()
{
    return _display;
}

QString menu::selection(QChar option)
{
    QString selection;
    QChar selected(option);
    if(_options.find(selected) != _options.end()){
        selection = _options[selected];
    }
    return selection;
}
