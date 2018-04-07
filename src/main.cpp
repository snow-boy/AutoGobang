#include <QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    // install stylesheet
    {
        QFile file(":/stylesheet/resources/QTDark.stylesheet");
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        a.setStyleSheet(data.toStdString().c_str());
    }

    MainWindow main_window;
    main_window.show();

    return a.exec();
}

