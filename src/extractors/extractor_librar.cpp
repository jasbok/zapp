#include "extractor_librar.h"

extractor_librar::extractor_librar(const QString& file)
    : _librar(file)
{}

bool extractor_librar::extract(const QString &destination) const
{
    return _librar.extract(destination);
}


