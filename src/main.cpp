#include "analysers/type_analyser.h"
#include "configs/config.h"
#include "executors/executor_factory.h"
#include "extractors/extractor_factory.h"
#include "menus/menu.h"
#include "patchers/patcher_copy.h"
#include "processes/dosbox.h"
#include "sanitisers/sanitiser.h"

#include <QCoreApplication>
#include <QDir>
#include <QtDebug>
#include <QFileInfo>
#include <QStringList>
#include <QThread>

#include <string>
#include <iostream>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "DEBUG - (%s:%u, %s): %s\n", context.file, context.line, context.function, localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, "INFO - (%s:%u, %s): %s\n", context.file, context.line, context.function, localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "WARN - (%s:%u, %s): %s\n", context.file, context.line, context.function, localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "CRITICAL - (%s:%u, %s): %s\n", context.file, context.line, context.function, localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "FATAL - (%s:%u, %s): %s\n", context.file, context.line, context.function, localMsg.constData());
        abort();
    }
}

void extract_source()
{
    config& config = config::instance();
    QFileInfo target_info(config.target());

    if(!target_info.exists()) {
        QDir().mkpath(config.target());
        QSharedPointer<extractor> extractor = extractor_factory::new_extractor(config.source());
        extractor->extract(config.target());
    } else {
        qInfo() << "Target exists, no extraction required.";
    }
}

QString display_menu(const target_analyser& ta)
{
    menu menu(ta);
    for(QString line : menu.display()) {
        QTextStream(stdout) << line << "\n";
    }

    QString selection;
    while(selection.isEmpty()) {
        QTextStream(stdin) << "Enter selection: ";
        std::string input;
        std::cin >> input;
        if(input.size() == 1) {
            selection = menu.selection(QChar(input.at(0)));
        }
        if(selection.isEmpty()) {
            QTextStream(stdout) << "Invalid selection.\n";
        }
    }
    return selection;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    QCoreApplication a(argc, argv);

    extract_source();

    config& config = config::instance();
    target_analyser ta(config.target());
    type_analyser tpa(ta);
    type_analyser::target_type type = tpa.type();

    patcher_copy pc(config.target(), config.user() + "/" + QFileInfo(config.source()).baseName());

    if(!pc.timestamp_exists()){
        sanitiser::sanitise_environment(ta, type);
        pc.create_timestamp();
        QThread::msleep(1001);
    }
    pc.patch();

    QString selection = display_menu(ta);

    QSharedPointer<executor> executor = executor_factory::new_executor(type);
    if(executor != nullptr){
        executor->working_dir(tpa.working_dir());
        executor->target(selection);
        executor->run();

        pc.diff();
    }
    else{
        qCritical() << "Null executor.";
    }


    return 0;
}
