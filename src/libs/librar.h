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
                // Extra string copy needed, since valgrind shows issues
                // with unrar and the QString char* representation.
                std::string str = path.toLocal8Bit().toStdString();
                archive_data.ArcName = (char*) str.c_str();
                archive_data.OpenMode = open_mode;
                archive = RAROpenArchive ( &archive_data );
        }

        int status;
        HANDLE archive;
        struct RARHeaderData current_header;
        struct RAROpenArchiveData  archive_data;
};

#endif // LIBRAR_H
