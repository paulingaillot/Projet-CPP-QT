#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    QApplication application(argc, argv);
    // Demarrage du menu
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
