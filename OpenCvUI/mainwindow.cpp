#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

using namespace cv;
using namespace cv::face;
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    capture.open( 0 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); }

    vector<Mat> images;
    vector<int> labels;
    // Read in the data (fails if no valid input filename is given, but you'll get an error message):
    try {
        read_csv(images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file CSV Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    model = createLBPHFaceRecognizer(2, 12, 12, 12, DBL_MAX);
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    model->train(images, labels);

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n");};
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n");};

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateFrame()));
    timer->start(20);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::UpdateFrame(){
    capture.read(frame);
    if( frame.empty() )
    {
        printf(" --(!) No captured frame -- Break!");
        return;
    }
    vector<cv::Rect> faces;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );


    face_cascade.detectMultiScale( frame_gray, faces, 1.3, 5, 0, Size(80, 80) );

    for ( size_t i = 0; i < faces.size(); i++ ){
        Mat faceROI = frame_gray( faces[i] );
        vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        if(eyes.size() == 2 ){
            Rect face_i_rec = faces[i];
            Mat face_i = frame_gray(face_i_rec);
            //PREDICTION
            int prediction = -1;
            double confidence = 0.0;
            model->predict(face_i, prediction, confidence);
            string box_text = format("Prediction = %d    confidence %.2f", prediction,confidence);

            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            if(confidence < 80){
                ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, CV_RGB( 255, 0, 0 ), 4, 8, 0 );
            }
            else{
                ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, CV_RGB(0,255,0), 4, 8, 0 );
            }
            //rectangle(frame, faces[i], CV_RGB(0, 255,0), 1);
            int pos_x = std::max(face_i_rec.tl().x - 10, 0);
            int pos_y = std::max(face_i_rec.tl().y - 10, 0);
            // And now put it into the image:
            putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
        }
    }


    cv::cvtColor(frame,frame,CV_BGR2RGB);
    QImage frameQT((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->videoLabel->setPixmap(QPixmap::fromImage(frameQT));
}

void MainWindow::read_csv(vector<Mat>& images, vector<int>& labels) {
    char separator = ';';

    ifstream file("/home/pablomuro/Projeto-TP1-UNB-2017-Deteccao-Facial/pablo.csv", ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
