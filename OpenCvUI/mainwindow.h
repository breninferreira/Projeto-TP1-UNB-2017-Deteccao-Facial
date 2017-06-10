#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void read_csv(std::vector<cv::Mat>& images, std::vector<int>& labels);

    cv::String face_cascade_name = "/home/pablomuro/Projeto-TP1-UNB-2017-Deteccao-Facial/lbpcascade_frontalface.xml";
    cv::String eyes_cascade_name = "/home/pablomuro/Projeto-TP1-UNB-2017-Deteccao-Facial/haarcascade_eye_tree_eyeglasses.xml";
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;

    cv::Ptr<cv::face::FaceRecognizer> model;

    cv::VideoCapture capture;
    cv::Mat frame;
    cv::Mat frame_gray;

    QImage frameQT;

    QTimer* timer;

private slots:
    void UpdateFrame();
};

#endif // MAINWINDOW_H
