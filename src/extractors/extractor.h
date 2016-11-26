#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <QString>
#include <QStringList>

class extractor
{
public:
    virtual ~extractor(){};
    virtual bool extract(const QString& destination) const = 0;
    virtual QStringList list() const = 0;
};

#endif // EXTRACTOR_H
