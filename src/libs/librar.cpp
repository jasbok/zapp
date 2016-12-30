#include "librar.h"

#include <QtDebug>

librar::librar ( const QString& path )
    : _path ( path )
{}

librar::~librar ( void )
{}

bool librar::extract ( const QString& dest ) const
{
    unrar unrar(_path, RAR_OM_EXTRACT);

    if ( unrar.archive != nullptr ) {
        unrar.status = RARReadHeader ( unrar.archive, &unrar.current_header );
        while ( unrar.status != ERAR_END_ARCHIVE ) {
            if ( unrar.status == ERAR_BAD_ARCHIVE ) {
                RARProcessFile ( unrar.archive, RAR_SKIP, NULL, NULL );
                qWarning() << "Unable to extract file: " << _path << "/" << unrar.current_header.ArcName;
            } else {
                RARProcessFile ( unrar.archive, RAR_EXTRACT, ( char* ) dest.toLocal8Bit().data(), NULL );
            }
            unrar.status = RARReadHeader ( unrar.archive, &unrar.current_header );
        }
        RARCloseArchive ( unrar.archive );
    } else {
        unrar.status = ERAR_BAD_ARCHIVE;
        qCritical() << "Could not extract rar archive: " << _path;
    }

    return unrar.status == ERAR_END_ARCHIVE;
}

bool librar::list ( QStringList& in ) const
{
    unrar unrar(_path, RAR_OM_LIST);

    if ( unrar.archive != nullptr ) {
        unrar.status = RARReadHeader ( unrar.archive, &unrar.current_header );
        while ( unrar.status != ERAR_END_ARCHIVE ) {
            if ( unrar.status == ERAR_BAD_ARCHIVE ) {
                qWarning() << "Could not read header from rar archive: " << _path << "/" << unrar.current_header.ArcName;
            } else {
                in.push_back ( QString ( unrar.current_header.FileName ) );
            }
            RARProcessFile ( unrar.archive, RAR_SKIP, 0, 0 );
            unrar.status = RARReadHeader ( unrar.archive, &unrar.current_header );
        }
        RARCloseArchive ( unrar.archive );
    } else {
        unrar.status = ERAR_BAD_ARCHIVE;
        qCritical() << "Could not read file list from rar archive: " << _path;
    }
    return unrar.status == ERAR_END_ARCHIVE;
}

QStringList librar::list() const
{
    QStringList results;
    list(results);
    return results;
}
