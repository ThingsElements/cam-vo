#include "common.h"

class Odometer {

    double focal;
    Point2d pp;

    vector<uchar> status;

    Mat R_f, t_f; //the final rotation and tranlation vectors containing the

    Mat E, R, t, mask;

    Mat prevR;

    Mat prevImage;
    vector<Point2f> lastFeatures;
    vector<Point2f> prevFeatures;
    vector<Point2f> currFeatures;

public:
    Odometer(double focal, Point2d pp);

    int estimate(Mat image, double scale, double& x, double& y, double& z);

    void featureTracking(Mat img_1, Mat img_2, vector<Point2f>& points1, vector<Point2f>& points2);
    void featureDetection(Mat img_1, vector<Point2f>& points1);

    vector<Point2f>& getLastFeatures();
    vector<Point2f>& getCurrFeatures();
    vector<Point2f>& getPrevFeatures();

    Mat& getR();
};
