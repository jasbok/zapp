#include "extractor_factory.h"
#include "extractor_innoextract.h"
#include "extractor_libarchive.h"

#ifdef USE_LIBRAR
#include "extractor_librar.h"
#endif

#include <QFileInfo>

QSharedPointer<extractor> extractor_factory::new_extractor(const QString &target)
{
    QSharedPointer<extractor> extr;
    QFileInfo target_info(target);
    QString suffix = target_info.suffix().toLower();

    if(target_info.isDir()){

    }
    else if(suffix == "exe"){
        extr = QSharedPointer<extractor>(new extractor_innoextract(target));
    }

#ifdef USE_LIBRAR
    else if(suffix == "rar"){
        extr = QSharedPointer<extractor>(new extractor_librar(target));
    }
#endif

    else{
        extr = QSharedPointer<extractor>(new extractor_libarchive(target));
    }

    return extr;
}
