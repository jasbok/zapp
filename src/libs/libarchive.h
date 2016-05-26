#ifndef LIBARCHIVE_H
#define LIBARCHIVE_H

#include <QString>
#include <QStringList>

class libarchive
{
public:
    libarchive ( const QString& path );
    virtual ~libarchive();

    virtual bool extract ( const QString& dest ) const;
    virtual bool list ( QStringList& in ) const;
    virtual QStringList list() const;

private:
    QString _path;
};

#endif // LIBARCHIVE_H
