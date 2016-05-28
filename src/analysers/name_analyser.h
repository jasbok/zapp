#ifndef NAME_ANALYSER_H
#define NAME_ANALYSER_H

#include <QString>
#include <QSet>

class name_analyser
{
public:
    name_analyser();
    name_analyser(const QString& name);
    void set_name(const QString& name);
    QSet<QString> keywords();
    QSet<QString> abbreviations();

private:
    QString _name;
    QSet<QString> _terms;
    QSet<QString> _keywords;
    QSet<QString> _abbreviations;
    QSet<QString> _stopwords;

    void _process();

    void _calculate_keywords();
    void _calculate_abbreviations();
};

#endif // NAME_ANALYSER_H
