#ifndef EXTRACTOR_LIBRAR_H
#define EXTRACTOR_LIBRAR_H

#include "extractor.h"
#include "libs/librar.h"

class extractor_librar : public extractor
{
public:
    extractor_librar(const QString& file);
    bool extract(const QString& destination) const;

private:
    librar _librar;
};

#endif // EXTRACTOR_LIBRAR_H
