#include <QApplication>
#include "ui/mainui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainUI window;
    window.showFullScreen();
    return app.exec();
}