#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessarena.h"
#include "playermanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{
    ui->widget_chess_board->SetChessBoard(ChessArena::Get()->GetChessBoard());

    connect(ChessArena::Get(), &ChessArena::SigChessChanged, this,
            [&](const QVector<QPoint> &highlight_points)
    {
        ui->widget_chess_board->SetHighlightPoints(highlight_points);
        ui->widget_chess_board->update();
    });

    connect(ChessArena::Get(), &ChessArena::SigPlayerSay, this,
            [&](Chess chess, const QString &word)
    {
        if(chess == Chess::Black){
            ui->textEdit_player1->append(word);
        }
        else if(chess == Chess::White){
            ui->textEdit_player2->append(word);
        }
    });

    ui->comboBox_black_player->addItems(PlayerManager::Get()->GetPlayerList());
    ui->comboBox_white_player->addItems(PlayerManager::Get()->GetPlayerList());
}

void MainWindow::on_pushButton_fight_clicked()
{
    IChessPlayer *black_player = PlayerManager::Get()->GetPlayerByName(
                ui->comboBox_black_player->currentText());
    IChessPlayer *white_player = PlayerManager::Get()->GetPlayerByName(
                ui->comboBox_white_player->currentText());

    ChessArena::Get()->Fight(black_player, Chess::Black,
                             white_player, Chess::White);
}
