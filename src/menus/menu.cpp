#include "menu.h"

menu::menu(const target_analyser& analyser)
    : _target_analyser(analyser),
      _display(),
      _options(),
      _option_chars({ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                    'q', 'w', 'e', 'r', 't', 'a', 's', 'd', 'f', 'g',
                    'z', 'x', 'c', 'v', 'b', 'y', 'u', 'i', 'o', 'p',
                    'h', 'j', 'k', 'l', 'n', 'm', '[', ']', ';', '\'',
                    ',', '.', '/', '\\', '-', '=', '`'})
{
    unsigned int option = 0;

    _display_section("Configuration Files", _target_analyser.configs(), option);
    _display_section("Application Executables", _target_analyser.application_executables(), option);
    _display_section("Setup Executables", _target_analyser.setup_executables(), option);
    _display_section("Documentation Executables", _target_analyser.documentation_executables(), option);
    _display_section("Other Executables", _target_analyser.other_executables(), option);
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

void menu::_display_section(const QString &section_name, const QStringList &list, unsigned int& option)
{
    if(list.size() > 0){
        _display << section_name + ":";
        for(QString exec : list){
            _options[QChar(_option_chars[option])] = exec;
            _display << QString("[%1] %2").arg(QChar(_option_chars[option++]), exec.replace(_target_analyser.data_path(), ""));
        }
    }
}
