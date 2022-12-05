//
// Created by pangyu on 2022/12/2.
//

#include <iostream>
#include <QDirIterator>
#include <QImageReader>
#include "MainWindow.h"
#include "the_player.h"
#include "the_button.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // set the title of the window
    this->setWindowTitle("Tomeo");

    // set the minimum size of the window
    setMinimumSize(800, 600);

    // set the width fixed of the left side
    ui->videoListWidget->setFixedWidth(300);

    // set the object name for the widgets, so that the stylesheet can be applied
    ui->videoListWidget->setObjectName("videoListWidgetObject");
    ui->videoPlayerWidget->setObjectName("videoPlayerWidgetObject");
    ui->videoListScrollArea->setObjectName("videoListScrollAreaObject");
    QWidget *videoListInScrollArea = ui->videoListScrollArea->widget();
    videoListInScrollArea->setObjectName("videoListInScrollAreaObject");

    // set the style sheet for the videoListInScrollArea
    videoListInScrollArea->setStyleSheet("QWidget#videoListInScrollAreaObject {background-color: #d0d0d1;}");

    // set the border style of videoListScrollArea
    ui->videoListScrollArea->setStyleSheet(
            "QScrollArea#videoListScrollAreaObject{border: none; background-color: #d0d0d1;}");
    // set the background color and border style of the left side
    ui->videoListWidget->setStyleSheet(
            "QWidget#videoListWidgetObject{background-color: #d0d0d1; border-style:solid; border-width:1px; border-right-color:#a9a9a9;}");
    // set the background color of the right side
    ui->videoPlayerWidget->setStyleSheet("QWidget#videoPlayerWidgetObject{background-color: #ececec;}");

    // add copyright to the left side of the status bar
    auto* versionLabel = new QLabel("Version 1.0.0");
    versionLabel->setParent(ui->statusbar);
    versionLabel->setObjectName("versionLabel");
    versionLabel->setStyleSheet("QLabel#versionLabel { color : #929292;font-size:12px; }");
    ui->statusbar->addPermanentWidget(versionLabel);
    ui->statusbar->showMessage("Copyright © 2022 Freewheelin' Team. All rights reserved.");
    ui->statusbar->setStyleSheet("QStatusBar{font-size:12px;color:#929292;}");

    // set the player
    player = new ThePlayer;
    player->mTimer = new QTimer(this);
    player->mTimer->setInterval(100);
    player->mTimer->start();
    connect(player->mTimer, &QTimer::timeout, this, [=]() {
        if (player->state() == QMediaPlayer::PlayingState) {
            ui->progressBar->setValue(player->position()*100/player->duration());
        }
    });
    player->setVideoOutput(ui->videoWidgetContainer);

    // set the initial picture when the program starts
    initPic = new QWidget(this);
    initPic->setStyleSheet("background-color: #ececec;");
    initLabel = new QLabel(initPic);
    initLabel->setPixmap(QPixmap("../images/home_tag.png"));
    initLabel->setScaledContents(true);
    initLabel->setGeometry(initPic->width()/2-300, initPic->height()/2-300, 600,600);
    initPic->setGeometry(312, 12, this->width()-324, this->height()-136);

    // set the video list to be played
    playlist = new QMediaPlaylist(player);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    // set the icon of the search label
    auto *pixmapSearchButton = new QPixmap("../images/search.png");
    pixmapSearchButton->scaled(ui->searchButton->size(), Qt::KeepAspectRatio);
    ui->searchButton->setScaledContents(true);
    ui->searchButton->setPixmap(*pixmapSearchButton);
    ui->searchButton->setFixedSize(25, 25);
    ui->searchButton->setCursor(Qt::PointingHandCursor);

    // make the menu label to be a menu
    auto *menu = new QMenu(this);
    menu->addAction("Sorted By Title");
    menu->addAction("Sorted By Date");
    menu->addAction("Sorted By Time");
    ui->menuButton->setText("Sort");
    ui->menuButton->setMenu(menu);

    // set the icon of pause button
    ui->pauseButton->setStyleSheet("QPushButton{border-image: url(../images/play.png);}");
    ui->pauseButton->setFixedSize(25, 25);
    ui->pauseButton->setCursor(Qt::PointingHandCursor);

    // set the icon of next button
    ui->nextButton->setStyleSheet("border-image: url(../images/next.png);");
    ui->nextButton->setFixedSize(25, 25);
    ui->nextButton->setCursor(Qt::PointingHandCursor);

    // set the icon of previous button
    ui->previousButton->setStyleSheet("border-image: url(../images/previous.png);");
    ui->previousButton->setFixedSize(25, 25);
    ui->previousButton->setCursor(Qt::PointingHandCursor);

    // set the icon of terminate button
    ui->terminateButton->setStyleSheet("border-image: url(../images/terminate.png);");
    ui->terminateButton->setFixedSize(27, 27);
    ui->terminateButton->setCursor(Qt::PointingHandCursor);

    // set the icon of the voice button
    ui->volumeButton->setStyleSheet("border-image: url(../images/volume.png);");
    ui->volumeButton->setFixedSize(25, 25);
    ui->volumeButton->setCursor(Qt::PointingHandCursor);

    // set the icon of the full screen button
    ui->fullScreenButton->setStyleSheet("border-image: url(../images/fullScreen.png);");
    ui->fullScreenButton->setFixedSize(18, 18);
    ui->fullScreenButton->setCursor(Qt::PointingHandCursor);

    // set the style of the progress bar
    ui->progressBar->setStyleSheet("QProgressBar::chunk {background-color: #FF0000;}");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setFixedHeight(30);
    ui->progressBar->setCursor(Qt::PointingHandCursor);

    // set the volume slider
    ui->volumeSlider->setParent(this);
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(50);
    ui->volumeSlider->setCursor(Qt::PointingHandCursor);
    // set the position of the volume slider
    ui->volumeSlider->setFixedSize(20, 100);
    ui->volumeSlider->hide();

    // the fileDialog
    auto *fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setOption(QFileDialog::ShowDirsOnly);

    // open the finder when the openFileButton is clicked
    connect(ui->openFileButton, &QPushButton::clicked, this, [=]() {
        if (fileDialog->exec()) {
            player->setVideoOutput(ui->videoWidgetContainer);
            QString path = fileDialog->selectedFiles()[0];
            string pathString = path.toStdString();
            cout << pathString << endl;
            outVideoList = getVideoList(pathString);
            vector<QUrl*> outVideoUrlList;
            for (auto &i : outVideoList) {
                outVideoUrlList.push_back(i->url);
            }
            playlist->clear();
            for (auto &i : outVideoUrlList) {
                playlist->addMedia(*i);
            }
            // cout the playlist
            player->setPlaylist(playlist);
            playlist->setCurrentIndex(0);

            // clear the widgets in the scroll area
            QLayoutItem *child;
            while ((child = ui->videoListScrollArea->widget()->layout()->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
            this->initPic->show();
            ui->progressText->setText("00:00 / 00:00");
            for(int i = 0; i < outVideoList.size(); i++) {
                ui->scrollAreaWidgetContents->layout()->addWidget(outVideoList[i]);
                // set the position of the video button dynamically
                connect(outVideoList[i], &TheButton::clicked, this, [=](){
                    playlist->setCurrentIndex(i);
                    this->initPic->hide();
                    player->play();
                    ui->pauseButton->setStyleSheet("border-image: url(../images/pause.png);");
                    if (TheButton::index != -1 && TheButton::index != i) {
                        outVideoList[TheButton::index]->bottomWidget->setStyleSheet("background-color: #d0d0d1;");
                        outVideoList[TheButton::index]->title->setStyleSheet("color: #000000;");
                        outVideoList[TheButton::index]->duration->setStyleSheet("color: #000000;");
                    }
                    outVideoList[i]->bottomWidget->setStyleSheet("background-color: #4288f7; border-radius:15px;");
                    outVideoList[i]->title->setStyleSheet("color: #ffffff;");
                    outVideoList[i]->duration->setStyleSheet("color: #ffffff;");

                    TheButton::index = i;
                });
                ui->scrollAreaWidgetContents->setMaximumHeight(100 * (i + 1));
                ui->scrollAreaWidgetContents->setMinimumHeight(100 * (i + 1));
            }
            ui->scrollAreaWidgetContents->setMaximumHeight(ui->scrollAreaWidgetContents->geometry().height()+100);
            ui->scrollAreaWidgetContents->setMinimumHeight(ui->scrollAreaWidgetContents->geometry().height()+100);

            TheButton::index = -1;
        }
    });

    // when the volume button is clicked, show the volume slider
    connect(ui->volumeButton, &QPushButton::clicked, this, [=]() {
        // get the relative position to the MainWindow of the volume button
        QPoint pos = ui->volumeButton->mapTo(this, QPoint(0, 0));
        // set the position of the volume slider
        ui->volumeSlider->move(pos.x(), pos.y() - 100);
        if (ui->volumeSlider->isHidden()) {
            ui->volumeSlider->show();
        } else {
            ui->volumeSlider->hide();
        }
    });

    // set the volume of the video
    connect(ui->volumeSlider, &QSlider::valueChanged, this, [=](int value) {
        player->setVolume(value);
    });

    // when the volume is 0, the volume button will be changed to mute
    connect(ui->volumeSlider, &QSlider::valueChanged, this, [=](int value) {
        if (value == 0) {
            ui->volumeButton->setStyleSheet("border-image: url(../images/mute.png);");
        } else {
            ui->volumeButton->setStyleSheet("border-image: url(../images/volume.png);");
        }
    });

    // set the progress bar when the video is playing smoothly
    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->progressBar->setValue(position * 100 / player->duration());
    });

    // set the video to the position when the progress bar is clicked
    connect(ui->progressBar, &QSlider::sliderMoved, this, [=](int position) {
        player->setPosition(position * player->duration() / 100);
    });

    // set the text of the progress label when the video is playing
    // format: mm:ss / mm:ss
    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->progressText->setText(QString("%1 / %2").arg(
                QTime(0, 0, 0).addMSecs(position).toString("mm:ss"),
                QTime(0, 0, 0).addMSecs(player->duration()).toString("mm:ss")
        ));
    });

    // when the pause button is clicked, the video will be paused
    connect(ui->pauseButton, &QPushButton::clicked, this, [=]() {
        if (player->state() == QMediaPlayer::PlayingState) {
            player->pause();
            ui->pauseButton->setStyleSheet("border-image: url(../images/play.png);");
        } else {
            player->play();
            ui->pauseButton->setStyleSheet("border-image: url(../images/pause.png);");
        }
    });

    // when the terminate button is clicked, the video will be terminated
    connect(ui->terminateButton, &QPushButton::clicked, this, [=]() {
        if (TheButton::index != -1) {
            player->stop();
            player->pause();
            ui->pauseButton->setStyleSheet("border-image: url(../images/play.png);");
        }
    });

    // previous button
    connect(ui->previousButton, &QPushButton::clicked, this, [=]() {
        if (TheButton::index != -1) {
            outVideoList[playlist->currentIndex()]->bottomWidget->setStyleSheet("background-color: #d0d0d1;");
            outVideoList[TheButton::index]->title->setStyleSheet("color: #000000;");
            outVideoList[TheButton::index]->duration->setStyleSheet("color: #000000;");
            if (TheButton::index == 0) {
                TheButton::index = outVideoList.size() - 1;
            } else {
                TheButton::index--;
            }
            emit outVideoList[TheButton::index]->clicked();
        }
    });

    // next button
    connect(ui->nextButton, &QPushButton::clicked, this, [=]() {
        if (TheButton::index != -1) {
            outVideoList[playlist->currentIndex()]->bottomWidget->setStyleSheet("background-color: #d0d0d1;");
            outVideoList[TheButton::index]->title->setStyleSheet("color: #000000;");
            outVideoList[TheButton::index]->duration->setStyleSheet("color: #000000;");
            if (TheButton::index == outVideoList.size() - 1) {
                TheButton::index = 0;
            } else {
                TheButton::index++;
            }
            emit outVideoList[TheButton::index]->clicked();
        }
    });

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    // set the position of the volume slider
    QPoint pos = ui->volumeButton->mapTo(this, QPoint(0, 0));
    ui->volumeSlider->move(pos.x(), pos.y() - 100);

    initLabel->setGeometry(initPic->width()/2-300, initPic->height()/2-300, 600,600);
    this->initPic->setGeometry(312, 12, this->width()-324, this->height()-136);

}

std::vector<TheButton*> MainWindow::getVideoList (std::string loc) {
//    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    auto *out = new std::vector<TheButton*>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

        if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

                QString thumb = f.left( f .length() - 4) +".png";
                if (QFile(thumb).exists()) { // if a png thumbnail exists
                    auto *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QUrl* iconUrl = new QUrl(thumb);
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        // get the title of the video
                        QString title = f.mid(f.lastIndexOf('/') + 1);
                        title = title.left(title.length());
                        auto* label = new QLabel(title);
                        // get the duration of the video
                        auto* playerTmp = new QMediaPlayer();
                        playerTmp->setMedia(*url);
                        playerTmp->play();
                        // wait for the video to load
                        while (playerTmp->duration() == 0) {
                            QCoreApplication::processEvents();
                        }
                        playerTmp->pause();
                        QString duration = QTime(0, 0, 0).addMSecs(playerTmp->duration()).toString("mm:ss");
                        auto* durationLabel = new QLabel(duration);
                        out->push_back(new TheButton(ui->scrollAreaWidgetContents, url, &sprite, label, durationLabel));

                        delete playerTmp;
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
                }
                else
                    qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
            }
    }

    return *out;
}
