#ifndef CIRCLEDECTECTION_H
#define CIRCLEDECTECTION_H

#include <QMainWindow>
#include <QWidget>
#include<QImage>
#include<QTimer>

#include<highgui.h>
#include<cv.h>
#include<opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

namespace Ui {
class circleDectection;
}

class circleDectection : public QMainWindow
{
    Q_OBJECT

public:
    explicit circleDectection(QWidget *parent = 0);
    ~circleDectection();

     QImage Mat2QImage(Mat cvImg);
     void circleDected();

private slots:
     void nextFrame1();
     void nextFrame2();

private:
    Ui::circleDectection *ui;

    QTimer *timer;
    VideoCapture capture;
    QImage  image;

    Mat frame;
    double rate=30.0;//FPS
};

#endif // CIRCLEDECTECTION_H
