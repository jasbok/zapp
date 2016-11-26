#include "config.h"
#include "QCoreApplication"
#include "QtDebug"
#include "QFileInfo"
#include "QStandardPaths"

config::config()
        : _container ( "/tmp/zapp/container" ),
          _user ( "/.zapp/user" ),
          _innoextract_bin ( "innoextract" ),
          _dosbox_bin ( "dosbox" )
{
        _user = QStandardPaths::standardLocations ( QStandardPaths::HomeLocation ) [0] + _user;
        _parse_args();
        _calculate_paths();
}

QString config::source() const
{
        return _source;
}

QString config::container() const
{
        return _container;
}

QString config::target() const
{
        return _target;
}

QString config::user() const
{
        return _user;
}

QString config::innoextract_bin() const
{
        return _innoextract_bin;
}

QString config::dosbox_bin() const
{
        return _dosbox_bin;
}

void config::_parse_args()
{
        QStringList arguments = QCoreApplication::arguments();
        if ( arguments.size() >= 2 ) {
                for ( int arg = 1; arg < arguments.size(); arg++ ) {
                        switch ( arg ) {
                        case 1:
                                _source = arguments[arg];
                                break;
                        case 2:
                                _container = arguments[arg];
                                break;
                        default:
                                break;
                        }
                }
        } else {
                qFatal ( "Insufficient arguments supplied." );
        }
}

void config::_calculate_paths()
{
        _source = _source.right ( 1 ) == "/" ? _source.left ( _source.size() - 2 ) : _source;
        _container = _container.right ( 1 ) == "/" ? _container.left ( _container.size() - 2 ) : _container;
        _target = QString ( "%1/%2" ).arg ( _container, QFileInfo ( _source ).baseName() );
        _user = _user.right ( 1 ) == "/" ? _user.left ( _user.size() - 2 ) : _user;
}
