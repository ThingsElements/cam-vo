#include "plotter.hpp"

Plotter::Plotter() {
  namedWindow( "Trajectory", WINDOW_AUTOSIZE );
  trajectory = Mat::zeros(600, 600, CV_8UC3);
}

int Plotter::plot(double dx, double dy, double dz) {

  char text[100];
  Point textOrg(10, 50);
  int fontFace = FONT_HERSHEY_PLAIN;
  double fontScale = 1;
  int thickness = 1;

  int x = int(dx) + 300;
  int y = int(dz) + 100;

  circle(trajectory, Point(x, y) ,1, CV_RGB(255, 0, 0), 1);

  rectangle(trajectory, Point(10, 30), Point(550, 70), CV_RGB(0,0,0), CV_FILLED);
  sprintf(text, "Coordinates: x = %02fm y = %02fm z = %02fm", dx, dy, dz);
  putText(trajectory, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);

  imshow( "Trajectory", trajectory );

  return 0;
}