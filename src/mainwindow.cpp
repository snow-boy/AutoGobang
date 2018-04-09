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

static QString AssembleHighlightString(const QString &str)
{
    return QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'宋体'; font-size:10pt; font-weight:400; font-style:normal;\"><p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:25pt; font-weight:600; color:#ff0000;\">%1</span></p></body></html>").arg(str);
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

    connect(ChessArena::Get(), &ChessArena::SigFightEnd, this,
            [&](Chess winner)
    {
        if(winner == Chess::Black){
            ui->textEdit_player1->append(AssembleHighlightString("Winner"));
        }
        else {
            ui->textEdit_player2->append(AssembleHighlightString("Winner"));
        }

        ui->pushButton_fight->setEnabled(true);
        ui->pushButton_fight->setText("Reset");
    });

    connect(ChessArena::Get(), &ChessArena::SigChessError, this,
            [&](Chess chess)
    {
        if(chess == Chess::Black){
            ui->textEdit_player1->append(AssembleHighlightString("Illegal"));
        }
        else {
            ui->textEdit_player2->append(AssembleHighlightString("Illegal"));
        }

        ui->pushButton_fight->setEnabled(true);
        ui->pushButton_fight->setText("Reset");
    });

    ui->comboBox_black_player->addItems(PlayerManager::Get()->GetPlayerList());
    ui->comboBox_white_player->addItems(PlayerManager::Get()->GetPlayerList());

    if(PlayerManager::Get()->GetPlayerList().size() == 0){
        ui->pushButton_fight->setEnabled(false);
        ui->pushButton_fight->setText("No player found!");
    }
}

void MainWindow::on_pushButton_fight_clicked()
{
    if(ui->pushButton_fight->text() == "Fight!!!")
    {
        IChessPlayer *black_player = PlayerManager::Get()->GetPlayerByName(
                    ui->comboBox_black_player->currentText());
        IChessPlayer *white_player = PlayerManager::Get()->GetPlayerByName(
                    ui->comboBox_white_player->currentText());

        ChessArena::Get()->Fight(black_player, Chess::Black,
                                 white_player, Chess::White);

        ui->comboBox_black_player->setEnabled(false);
        ui->comboBox_white_player->setEnabled(false);

        ui->pushButton_fight->setText("Fighting...");
        ui->pushButton_fight->setEnabled(false);
    }
    else if(ui->pushButton_fight->text() == "Reset")
    {
        ChessArena::Get()->Reset();
        ui->widget_chess_board->ClearHighlightPoints();
        ui->widget_chess_board->update();

        ui->comboBox_black_player->setEnabled(true);
        ui->comboBox_white_player->setEnabled(true);

        ui->textEdit_player1->clear();
        ui->textEdit_player2->clear();

        ui->pushButton_fight->setText("Fight!!!");
    }
}
