#include "common.h"

class Camera {
private:
    const char *windowName = "cam-vo";
    VideoCapture camera;
    Mat cameraFrame;
    int seq;

    ////// image
    char folder[100];

public:
    void init(int cameraNumber);

    int capture(Mat &image);

    double getFocal();
    double getScale();
    Point2d getPrinciplePoint();
};
