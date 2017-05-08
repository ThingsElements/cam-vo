#include "mono-vo.h"

int main(int argc, char** argv) {
    Camera camera;
    Playback playback("Road facing camera");
    camera.init(0);

    Odometer odometer(camera.getFocal(), camera.getPrinciplePoint());

    int numFrame;
    Mat image;
    Mat colorImage;

    while((numFrame = camera.capture(image)) >= 0) {
        double x, y, z;

        odometer.estimate(image, 1.0, x, y, z);

        cvtColor(image, colorImage, COLOR_GRAY2RGB);
        playback.redraw(colorImage, odometer.getLastFeatures(), odometer.getCurrFeatures(), odometer.getR());

        waitKey(20);
    }
}