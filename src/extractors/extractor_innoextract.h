#ifndef EXTRACTOR_INNOEXTRACT_H
#define EXTRACTOR_INNOEXTRACT_H

#include "extractor.h"
#include "processes/innoextract.h"
#include <QString>

class extractor_innoextract : public extractor
{
public:
    extractor_innoextract(const QString& file);
    virtual bool extract(const QString& destination) const;

private:
    innoextract _innoextract;
};

#endif // EXTRACTOR_INNOEXTRACT_H
