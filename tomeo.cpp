//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//

#include <QApplication>
#include <QMediaPlaylist>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // create the main window
    MainWindow w;

    // showtime!
    w.show();


    // wait for the app to terminate
    return QApplication::exec();
}