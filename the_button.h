//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H

#include <QPushButton>
#include <QUrl>
#include <QLabel>
#include <QVBoxLayout>

class TheButtonInfo {

public:
    QUrl *url; // video file to play
    QIcon *icon; // icon to display

    TheButtonInfo(QUrl *url, QIcon *icon) : url(url), icon(icon) {}
};

//class TheButton : public QPushButton {
//    Q_OBJECT
//
//public:
//    TheButtonInfo* info;
//
//     TheButton(QWidget *parent) :  QPushButton(parent) {
//         setIconSize(QSize(200,110));
//         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
//    }
//
//    void init(TheButtonInfo* i);
//
//private slots:
//    void clicked();
//
//signals:
//    void jumpTo(TheButtonInfo*);
//
//};

class TheButton : public QWidget{
Q_OBJECT


public:
    static int index;

    QUrl *url; // video file to play
    QImage *icon; // icon to display
    QLabel *title; // title to display
    QLabel *duration; // duration to display
    QWidget* bottomWidget; // bottom widget to display

    TheButton(QWidget *parent, QUrl *url, QImage *icon, QLabel *title, QLabel *duration);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked();
};

#endif //CW2_THE_BUTTON_H
