#include <QApplication>
#include <QPushButton>
#include "../include/MainWidget.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWidget mainWidget;
    mainWidget.resize(320, 320);
    mainWidget.show();

    return QApplication::exec();
}