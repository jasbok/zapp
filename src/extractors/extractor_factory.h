#ifndef EXTRACTOR_FACTORY_H
#define EXTRACTOR_FACTORY_H

#include "extractor.h"
#include <QSharedPointer>

class extractor_factory
{
public:
    static QSharedPointer<extractor> new_extractor(const QString& target);
};

#endif // EXTRACTOR_FACTORY_H
