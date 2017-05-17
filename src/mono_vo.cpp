#include "mono-vo.h"

#if !defined WIN32 && !defined _WIN32
#define VK_ESCAPE 0x1B      // Escape character (27)
#endif

int main(int argc, char **argv) {
    Camera camera;
    Plotter plotter;
    Playback playback("Road facing camera");
    camera.init(0);

    Odometer odometer(camera.getFocal(), camera.getPrinciplePoint());

    int numFrame;
    Mat image;
    Mat colorImage;

    while ((numFrame = camera.capture(image)) >= 0) {
        double x, y, z;

        odometer.estimate(image, 1.0, x, y, z);

        plotter.plot(x, y, z);

        cvtColor(image, colorImage, COLOR_GRAY2RGB);
        playback.redraw(colorImage, odometer.getLastFeatures(), odometer.getCurrFeatures(), odometer.getR());

        char keypress = waitKey(20);
        if (keypress == VK_ESCAPE) {   // Escape Key
            // Quit the program!
            break;
        }
    }
}
