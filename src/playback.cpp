#include "playback.hpp"

Playback::Playback(const char* name) {
    bzero(this->name, 100);
    strncpy(this->name, name, strlen(name));
    namedWindow(this->name, WINDOW_AUTOSIZE);

    AXIS = Mat::eye(3, 3, CV_64F);
}

int Playback::redraw(Mat image, vector<Point2f>& prevFeatures, vector<Point2f>& currFeatures, Mat& R) {

    if(prevFeatures.size() == currFeatures.size()) {

        for(int i = 0;i < prevFeatures.size();i++) {
            Point2f prev = prevFeatures.at(i);
            Point2f curr = currFeatures.at(i);

            line(image, prev, curr, CV_RGB(0, 255, 0));
        }
    }

    if(R.rows > 0 && R.cols > 0) {

        Point2f origin(320, 240);

        // double *r = (double*)R.data;
        // AXIS = Mat(3, 3, CV_64F);
        Mat A = R * AXIS;
        double *axis = (double*)A.data;

        Point2f xAxis(axis[0] * 100 + origin.x, axis[3] * 100 + origin.y);
        Point2f yAxis(axis[1] * 100 + origin.x, axis[4] * 100 + origin.y);
        Point2f zAxis(axis[2] * 100 + origin.x, axis[5] * 100 + origin.y);

        // Point2f xAxis(r[0] * 100 + origin.x, r[3] * 100 + origin.y);
        // Point2f yAxis(r[1] * 100 + origin.x, r[4] * 100 + origin.y);
        // Point2f zAxis(r[2] * 100 + origin.x, r[5] * 100 + origin.y);

        line(image, origin, xAxis, CV_RGB(255, 0, 0), 2);
        line(image, origin, yAxis, CV_RGB(0, 255, 0), 2);
        line(image, origin, zAxis, CV_RGB(0, 0, 255), 2);
    }

    imshow(name, image);

    return 0;
}
