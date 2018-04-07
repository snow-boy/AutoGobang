#include <QApplication>
#include <QFile>
#include <QDir>
#include "mainwindow.h"
#include "chessarena.h"
#include "playermanager.h"

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

    PlayerManager player_mgr;
    {
        QDir dir(a.applicationDirPath());
        player_mgr.InitPlayerList(dir.absoluteFilePath("player"));
    }

    ChessArena chess_arena;
    chess_arena.InitChessBoard(16, 16);

    MainWindow main_window;
    main_window.show();

    return a.exec();
}

