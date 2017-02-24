#include "mainwindow.h"
#include <QApplication>
#include "decoderthread.h"
#include "scannerqwidgetsink.h"

static QSharedMemory *gShm = NULL;

static void terminate(int signum)
{
    if (gShm) {
        delete gShm;
        gShm = NULL;
    }
    qDebug() << "Terminate with signal:" << signum;
    exit(128 + signum);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Handle any further termination signals to ensure the
    // QSharedMemory block is deleted even if the process crashes
    signal(SIGHUP,  terminate ); // 1
    signal(SIGINT,  terminate ); // 2
    signal(SIGQUIT, terminate ); // 3
    signal(SIGILL,  terminate ); // 4
    signal(SIGABRT, terminate ); // 6
    signal(SIGFPE,  terminate ); // 8
    signal(SIGBUS,  terminate ); // 10
    signal(SIGSEGV, terminate ); // 11
    signal(SIGSYS,  terminate ); // 12
    signal(SIGPIPE, terminate ); // 13
    signal(SIGALRM, terminate ); // 14
    signal(SIGTERM, terminate ); // 15
    signal(SIGXCPU, terminate ); // 24
    signal(SIGXFSZ, terminate ); // 25

    gShm = new QSharedMemory("QRScannerNXP");
    if (!gShm->create(4, QSharedMemory::ReadWrite)) {
        delete gShm;
        qDebug() << "Only allow one instance of QRScanner";
        exit(0);
    }
    MainWindow w;
    w.show();

    return a.exec();
}
