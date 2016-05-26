#include "extractor_libarchive.h"

extractor_libarchive::extractor_libarchive(const QString &file)
    : _libarchive(file)
{}

bool extractor_libarchive::extract(const QString &destination) const
{
    return _libarchive.extract(destination);
}
