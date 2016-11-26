#ifndef EXTRACTOR_LIBARCHIVE_H
#define EXTRACTOR_LIBARCHIVE_H

#include "extractor.h"
#include "libs/libarchive.h"

class extractor_libarchive : public extractor
{
public:
    extractor_libarchive(const QString& file);
    virtual bool extract(const QString& destination) const;
    virtual QStringList list() const;
private:
    libarchive _libarchive;
};

#endif // EXTRACTOR_LIBARCHIVE_H
