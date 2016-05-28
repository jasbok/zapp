#include "name_analyser.h"

#include <QDebug>
#include <QRegExp>
#include <QVector>



name_analyser::name_analyser()
    : _name(),
      _terms(),
      _keywords(),
      _abbreviations(),
      _stopwords(QSet<QString>{"the", "to", "a", "of"})
{}

name_analyser::name_analyser(const QString& name)
    : _name(name),
      _terms(),
      _keywords(),
      _abbreviations(),
      _stopwords(QSet<QString>{"the", "to", "a", "of"})
{
    _process();
}

void name_analyser::set_name(const QString &name)
{
    _name = name;
    _process();
}

QSet<QString> name_analyser::keywords()
{
    return _keywords;
}

QSet<QString> name_analyser::abbreviations()
{
    return _abbreviations;
}

void name_analyser::_process()
{
    _calculate_keywords();
    _calculate_abbreviations();
}

void name_analyser::_calculate_keywords()
{
    for(QString term : _name.toLower().split(QRegExp("(\\s|-|_|:)+"))){
        _terms << term;
    }
    for(QString term : _terms){
        if(!_stopwords.contains(term)){
            _keywords << term;
        }
    }
}

void name_analyser::_calculate_abbreviations()
{
    QRegExp group_regex("(-|_|:)+");
    QRegExp term_regex("\\s+");
    QRegExp digit_regex("\\d+");

    QVector<QStringList> groups;
    for(QString group : _name.toLower().split(group_regex)){
        QStringList list = group.split(term_regex);
        groups.append(list);

        QStringList keyword_list;
        QStringList keyword_list_no_digits;

        for(QString term : list){
            if(!_stopwords.contains(term)){
                keyword_list.append(term);

                if(!digit_regex.exactMatch(term)){
                    keyword_list_no_digits.append(term);
                }
            }
        }
        if(keyword_list.size() < list.size()){
            groups.append(keyword_list);
        }
        if(keyword_list_no_digits.size() < keyword_list.size()){
            groups.append(keyword_list_no_digits);
        }
    }

    for(QStringList group : groups){
        QString abbr;
        for(QString term : group){
            abbr += term.left(1);
        }
        if(abbr.size() > 0){
            _abbreviations << abbr;

            if(abbr.size() > 1){
                for(int i = 1 ; i < abbr.size(); i++){
                    _abbreviations << abbr.right(i);
                    _abbreviations << abbr.left(i);
                }
            }
        }
    }
}

