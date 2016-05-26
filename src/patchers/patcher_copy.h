#ifndef PATCHER_COPY_H
#define PATCHER_COPY_H

#include "patcher.h"

class patcher_copy : public patcher
{
public:
        patcher_copy(const QString& original, const QString& modified);
        virtual void diff () const;
        virtual void patch () const;
};

#endif // PATCHER_COPY_H
