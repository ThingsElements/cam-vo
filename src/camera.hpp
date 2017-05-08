#include "common.h"

class Camera {
private:
    const char *windowName = "mono-vo";
    VideoCapture camera;
    Mat cameraFrame;
    int seq;

public:
    void init(int cameraNumber);

    int capture(Mat &image);

    double getFocal();
    double getScale();
    Point2d getPrinciplePoint();
};