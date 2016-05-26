#include "extractor_innoextract.h"

extractor_innoextract::extractor_innoextract(const QString& file)
    : _innoextract(file)
{}

bool extractor_innoextract::extract(const QString& destination) const
{
    return _innoextract.extract(destination);
}
