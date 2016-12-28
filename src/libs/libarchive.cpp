#include "libarchive.h"

#include <archive.h>
#include <archive_entry.h>
#include <QtDebug>

struct archive_wrapper {
    archive_wrapper ( const QString& path )
        : archive ( archive_read_new() ),
          current_entry()
    {
        archive_read_support_filter_all ( archive );
        archive_read_support_format_all ( archive );
        status = archive_read_open_filename ( archive, path.toLocal8Bit().data(), 10240 );
    }
    ~archive_wrapper()
    {
        if ( archive ) {
            archive_read_free ( archive );
        }
    }
    int status;
    struct ::archive* archive;
    struct ::archive_entry* current_entry;
};

libarchive::libarchive ( const QString& path )
    : _path ( path )
{}

libarchive::~libarchive()
{}

bool libarchive::extract ( const QString& dest ) const
{
    archive_wrapper aw ( _path );

    if ( aw.status == ARCHIVE_OK ) {
        QString destination = dest;
        if ( destination.right(1) != "/" ) {
            destination += QChar( '/' );
        }

        aw.status = archive_read_next_header ( aw.archive, &aw.current_entry );
        while ( aw.status == ARCHIVE_OK ) {
            QString entry_path = destination + QString(archive_entry_pathname ( aw.current_entry )).toLower();
            archive_entry_set_pathname ( aw.current_entry, entry_path.toLocal8Bit().data() );
            aw.status = archive_read_extract ( aw.archive, aw.current_entry, 0 );

            if ( aw.status == ARCHIVE_WARN ) {
                qWarning() << "An archive warning was encountered: " << entry_path;
                qWarning() << archive_error_string ( aw.archive );
            } else if ( aw.status == ARCHIVE_RETRY ) {
                qWarning() << "A non-fatal archive error was encountered: " << entry_path;
            } else if ( aw.status == ARCHIVE_FATAL ) {
                qCritical() << "A fatal archive error was encountered: " << entry_path;
                qCritical() << archive_error_string ( aw.archive );
            }

            aw.status = archive_read_next_header ( aw.archive, &aw.current_entry );
        }

        if ( aw.status != ARCHIVE_EOF ) {
            qCritical() << "An archive error was encountered: " << _path;
            qCritical() << archive_error_string ( aw.archive );
        }
    } else {
        qCritical() << "A fatal archive error was encountered while opening the archive: " << _path;
        qCritical() << archive_error_string ( aw.archive );
    }

    return aw.status == ARCHIVE_EOF;
}

bool libarchive::list ( QStringList& in ) const
{
    archive_wrapper aw ( _path );

    if ( aw.status == ARCHIVE_OK ) {
        aw.status = archive_read_next_header ( aw.archive, &aw.current_entry );
        while ( aw.status == ARCHIVE_OK ) {
            QString entry_path = archive_entry_pathname ( aw.current_entry );
            if ( entry_path.right(1) != "/" ) {
                entry_path += QChar( '/' );
            }

            in.push_back ( entry_path );
            aw.status = archive_read_next_header ( aw.archive, &aw.current_entry );
        }

        if ( aw.status != ARCHIVE_EOF ) {
            qCritical() << "An archive error was encountered: " << _path;
            qCritical() << archive_error_string ( aw.archive );
        }
    } else {
        qCritical() << "A fatal archive error was encountered while opening the archive: " << _path;
        qCritical() << archive_error_string ( aw.archive );
    }
    return aw.status == ARCHIVE_EOF;
}

QStringList libarchive::list() const
{
    QStringList results;
    list(results);
    return results;
}
