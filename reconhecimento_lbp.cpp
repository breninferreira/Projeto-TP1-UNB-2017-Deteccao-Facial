/*
 * Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 */

#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

using namespace cv;
using namespace cv::face;
using namespace std;

void detectAndDisplay( Mat frame, FaceRecognizer *model );
static void read_csv(vector<Mat>& images, vector<int>& labels);

String face_cascade_name = "lbpcascade_frontalface.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

//pegar path CV fotos

String window_name = "Capture - Face detection";

int main(void) {
    // Check for valid command line arguments, print usage
    // if no arguments were given.
    // if (argc != 4) {
    //     cout << "usage: " << argv[0] << " </path/to/haar_cascade> </path/to/csv.ext> </path/to/device id>" << endl;
    //     cout << "\t </path/to/haar_cascade> -- Path to the Haar Cascade for face detection." << endl;
    //     cout << "\t </path/to/csv.ext> -- Path to the CSV file with the face database." << endl;
    //     cout << "\t <device id> -- The webcam device id to grab frames from." << endl;
    //     exit(1);
    // }
    // // Get the path to your CSV:
    // string fn_haar = string(argv[1]);
    // string fn_csv = string(argv[2]);
    // int deviceId = atoi(argv[3]);
    // These vectors hold the images and corresponding labels:
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
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size AND we need to reshape incoming faces to this size:

    // int im_width = images[0].cols;
    // int im_height = images[0].rows;

    // Create a FaceRecognizer and train it on the given images:
    Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    model->train(images, labels);


    // That's it for learning the Face Recognition model. You now
    // need to create the classifier for the task of Face Detection.
    // We are going to use the haar cascade you have specified in the
    // command line arguments:
    //
    VideoCapture capture;
    Mat frame;
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };
    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame , model );
        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }
    return 0;
}

void detectAndDisplay( Mat frame , FaceRecognizer* model)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    //cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    cvtColor( frame, frame_gray, CV_BGR2GRAY );

    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    //face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
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
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes
        // eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        // for ( size_t j = 0; j < eyes.size(); j++ )
        // {
        //     Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
        //     int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
        //     circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        // }
        int pos_x = std::max(face_i_rec.tl().x - 10, 0);
        int pos_y = std::max(face_i_rec.tl().y - 10, 0);
        // And now put it into the image:
        putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
    }
    //-- Show what you got
    imshow( window_name, frame );
}

static void read_csv(vector<Mat>& images, vector<int>& labels) {
    char separator = ';';

    std::ifstream file("/home/pablomuro/Projeto-TP1-UNB-2017-Deteccao-Facial/pablo.csv", ifstream::in);
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
