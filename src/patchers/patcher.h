#ifndef PATCHER_H
#define PATCHER_H

#include <QDateTime>
#include <QString>

class patcher
{
public:
        patcher(const QString& original, const QString& patched);
        ~patcher(){};

        QString original() const;
        QString patched() const;

        bool timestamp_exists() const;
        void create_timestamp() const;
        QDateTime read_timestamp() const;
        QStringList modified_files() const;
        QStringList patched_files() const;

        virtual void diff() const = 0;
        virtual void patch() const = 0;

private:
        QString _original, _patched;
};

#endif // PATCHER_H
