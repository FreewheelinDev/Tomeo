//
// Created by pangyu on 2022/12/2.
//

#ifndef FREEWHEELINGPROJECT_MAINWINDOW_H
#define FREEWHEELINGPROJECT_MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPaintEvent>
#include <QWidget>
#include <QDebug>
#include <QEvent>
#include <QMediaPlaylist>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QTime>
#include "the_button.h"
#include "the_player.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:

    std::vector<TheButton *> outVideoList = std::vector<TheButton *>();

    explicit MainWindow(QWidget *parent = nullptr);

    std::vector<TheButton *> getVideoList(std::string loc);

    ~MainWindow() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    QWidget *initPic;

    QLabel *initLabel;

    QMediaPlaylist *playlist;

    ThePlayer* player;
};


#endif //FREEWHEELINGPROJECT_MAINWINDOW_H
