#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QProcess>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Embedded IDE");
    QCoreApplication::setOrganizationName("none");
    QCoreApplication::setOrganizationDomain("unknown.tk");

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/embedded-ide.svg"));

    QCommandLineParser opt;
    opt.addHelpOption();
    opt.addVersionOption();
    opt.addPositionalArgument("filename", "Makefile filename");
    opt.addOptions({
                       { { "e", "exec" }, "Execute stript or file", "execname" },
                       { { "d", "debug"}, "Enable debug" },
                       { { "s", "stacktrace" }, "Add stack trace to debug" }
                   });
    opt.process(app);

    if (opt.isSet("exec")) {
        QString execname = opt.value("exec");
        QProcess::startDetached(execname);
        return 0;
    }

    if (opt.isSet("debug")) {
        QString debugString = "[%{type}] %{appname} (%{file}:%{line}) - %{message}";
        if (opt.isSet("stacktrace"))
            debugString += "\n\t%{backtrace separator=\"\n\t\"}";
        qSetMessagePattern(debugString);
    } else
        qSetMessagePattern("");

    MainWindow w;
    w.show();

    if (!opt.positionalArguments().isEmpty()) {
        QString path = opt.positionalArguments().first();
        QTimer::singleShot(0, [path, &w]() { w.openProject(path); });
    }

    return app.exec();
}