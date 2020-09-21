#include "circledectection.h"
#include "ui_circledectection.h"

#include<QTextStream>

circleDectection::circleDectection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::circleDectection)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
}

circleDectection::~circleDectection()
{
    delete ui;
}

/*****************获取下一帧图像************************/
void circleDectection::nextFrame1()
{
    capture >> frame;
       if (!frame.empty())
       {
           image = circleDectection::Mat2QImage(frame);
           ui->label->setPixmap(QPixmap::fromImage(image));
          // this->update();
       }
}

void circleDectection::nextFrame2()
{
    capture >> frame;
       if (!frame.empty())
       {

           Mat midImage;
               cvtColor(frame, midImage, CV_BGR2GRAY);//转化边缘检测后的图
               Canny(midImage, midImage, 50, 150);
               GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
           image = circleDectection::Mat2QImage(midImage);
           ui->label_2->setPixmap(QPixmap::fromImage(image));
          // this->update();
       }
}

/****************将MAT转换成QImage****************/

QImage circleDectection::Mat2QImage(Mat cvImg)
{
        QImage qImg;
        if(cvImg.channels()==3)                             //3 channels color image
        {

            cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
            qImg =QImage((const unsigned char*)(cvImg.data),
                        cvImg.cols, cvImg.rows,
                        cvImg.cols*cvImg.channels(),
                        QImage::Format_RGB888);
        }
        else if(cvImg.channels()==1)                    //grayscale image
        {

            qImg =QImage((const unsigned char*)(cvImg.data),
                        cvImg.cols,cvImg.rows,
                        cvImg.cols*cvImg.channels(),
                        QImage::Format_Indexed8);

        }
        else
        {
            qImg =QImage((const unsigned char*)(cvImg.data),
                        cvImg.cols,cvImg.rows,
                        cvImg.cols*cvImg.channels(),
                        QImage::Format_RGB888);
        }

        return qImg;
}


/**************function circleDectection*******************/
void circleDectection::circleDected()
{
    if (!capture.isOpened())
        capture.release();     //decide if capture is already opened; if so,close it
    capture.open(0);           //open the default camera
    if (capture.isOpened())
    {
        //rate= capture.get(CV_CAP_PROP_FOCUS);

        capture >> frame;
        if (!frame.empty())
        {
           ui->label->setPixmap(QPixmap::fromImage(image));
           timer = new QTimer(this);
           timer->setInterval(1000.0/rate);   //set timer match with FPS
           connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame1()));
           timer->start(30);
        }

              Mat midImage;
                cvtColor(frame, midImage, CV_BGR2GRAY);//转化边缘检测后的图
                Canny(midImage, midImage, 50, 150);
                GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

               /***show the test pic*****/
               QImage image1;
               image1=Mat2QImage(midImage);
               ui->label_2->setPixmap(QPixmap::fromImage(image1));
//               timer = new QTimer(this);
//               timer->setInterval(1000.0/rate);   //set timer match with FPS
//               connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame2()));
//               timer->start(30);
               /***show the test pic*****/

                vector<Vec3f> circles;
                    HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1, 20, 200, 100, 10, 120);
                    for (size_t i = 0; i < circles.size(); i++)
                    {
                       //参数定义
                        Point center(circles[i][0], circles[i][1]);
                        int radius= cvRound(circles[i][2]);
                       //绘制圆心
                      // circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
                       //绘制圆轮廓
                       //circle(frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);

                       //打印同心圆圆心坐标和每个圆的半径
                       cout << "圆心坐标为：" <<center<< endl;
                       cout << "圆半径为：" <<radius<< endl;
                    }
                    timer = new QTimer(this);
                    timer->setInterval(1000.0/rate);   //set timer match with FPS
                    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame2()));
                    timer->start(30);

    }
}

