#include "camera.hpp"

#define MAX_FRAME 100000

void Camera::init(int cameraNumber) {
    // seq = 0;
    // // Get access to the default camera.
    // try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
    //     camera.open(cameraNumber);
    //     sleep(1);
    // } catch (Exception &e) {}
    // if ( !camera.isOpened() ) {
    //     cerr << "ERROR: Could not access the camera!" << endl;
    //     exit(1);
    // }
    // cout << "Loaded camera " << cameraNumber << "." << endl;
    //
    // camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    // camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    // camera.set(CV_CAP_PROP_AUTOFOCUS, 0);

//    //////// image
    sprintf(folder, "../data/01/images");
    seq = 0;
}

double Camera::getFocal() {
    // return 718.8560;
    return 514.7320;
}

double Camera::getScale() {

    if(seq < 3)
        return 1.0;

    string line;
    int i = 0;

    ifstream fposes ("../data/01/poses.txt");

    double x, y, z;
    double x_prev, y_prev, z_prev;

    if(!fposes.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    while(getline(fposes, line) && (i++ < seq - 3))
        ;

    while(getline(fposes, line) && (i++ <= seq - 1)) {

        z_prev = z;
        x_prev = x;
        y_prev = y;

        istringstream in(line);

        for (int j=0; j<12; j++) {
            in >> z ;
            if (j==7) y=z;
            if (j==3) x=z;
        }
    }

    fposes.close();

    return sqrt((x - x_prev)*(x - x_prev) + (y - y_prev)*(y - y_prev) + (z - z_prev)*(z - z_prev));
}

Point2d Camera::getPrinciplePoint() {
    // return Point2d(607.1928, 185.2157);
    return Point2d(335.7723, 247.8904);
}

int Camera::capture(Mat& image) {
    // camera >> cameraFrame;
    // if(cameraFrame.empty()){
    //     cerr << "ERROR: Couldn't grab the next camera frame." <<endl;
    //     exit(1);
    // }
    //
    // Mat grayImage;
    //
    // cvtColor(cameraFrame, grayImage, COLOR_BGR2GRAY);
    //
    // image = grayImage;
    //
    // return seq++;

//    //////////// image
    if(seq >= MAX_FRAME)
    return -1;

    char filename[200];
    Mat grayImage;

    sprintf(filename, "%s/%06d.png", folder, seq);
    Mat colorImage = imread(filename);

    Mat sharpen_image;
    Mat sharpen_kernel = (Mat_<char>(3, 3) << 0, -1, 0,
                                             -1,  5,-1,
                                              0, -1, 0);

    filter2D(colorImage, sharpen_image, colorImage.depth(), sharpen_kernel);

    cvtColor(sharpen_image, grayImage, COLOR_BGR2GRAY);

    image = grayImage;

    return seq++;
}
