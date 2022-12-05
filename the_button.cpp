//
// Created by twak on 11/11/2019.
//

#include "the_button.h"

int TheButton::index = -1;  // which one is clicked, -1 means none

TheButton::TheButton(QWidget *parent, QUrl *url, QImage *icon, QLabel *title, QLabel *duration) : QWidget(parent) {

    this->url = url;
    this->icon = icon;
    this->title = title;
    this->duration = duration;
    auto *imageWidget = new QWidget(this);
    auto *image = new QLabel(imageWidget);
    image->setPixmap(QPixmap::fromImage(*icon));
    image->setScaledContents(true);
    image->setFixedSize(157,88);
    imageWidget->setFixedSize(157,88);
    auto *rWidget = new QWidget(this);
    auto *rLayout = new QVBoxLayout(rWidget);
    rLayout->addWidget(title);
    rLayout->addWidget(duration);
    auto *layout = new QHBoxLayout(this);
    layout->addWidget(imageWidget);
    layout->addWidget(rWidget);
    this->setMinimumSize(250, 110);
    this->setMaximumSize(250, 110);

    this->bottomWidget = new QWidget(this);
    bottomWidget->setStyleSheet("background-color: #d0d0d1; border-radius: 15px; ");
    bottomWidget->setGeometry(this->geometry());
    bottomWidget->stackUnder(rWidget);
    bottomWidget->stackUnder(imageWidget);
}

void TheButton::mouseReleaseEvent(QMouseEvent *event) {
    emit clicked();
}
