#ifndef LIBRAR_H
#define LIBRAR_H

#include <QStringList>
#include <unrar/dll.hpp>

class librar
{
public:
        librar ( const QString& path );
        virtual ~librar ( void );

        virtual bool extract ( const QString& dest ) const;
        virtual bool list ( QStringList& in ) const;
        virtual QStringList list() const;

private:
        QString _path;
};

struct unrar {
        unrar ( const QString& path, int open_mode ) {
                archive_data.ArcName = ( char* ) path.toLocal8Bit().data();
                archive_data.OpenMode = open_mode;
                archive = RAROpenArchive ( &archive_data );
        }

        int status;
        HANDLE archive;
        struct RARHeaderData current_header;
        struct RAROpenArchiveData  archive_data;
};

#endif // LIBRAR_H
