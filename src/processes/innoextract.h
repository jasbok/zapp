#ifndef INNOEXTRACT_H
#define INNOEXTRACT_H

#include <QProcess>
#include <QString>

class innoextract
{
public:
    innoextract(const QString& target);
    bool extract(const QString& destination) const;

private:
    QString _target;
};

#endif // INNOEXTRACT_H
