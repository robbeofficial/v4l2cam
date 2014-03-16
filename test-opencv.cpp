#include <sys/time.h>

#include <iostream>
#include <opencv/highgui.h>
#include <stdio.h>

#include "v4l2cam.h"

using namespace std;


int main(int argc, char **args) {
  int ww=640;
  int hh=480;
  int fps=30;

  const char *dev="/dev/video1";

  timeval t1;
  timeval t2;

  gettimeofday(&t1, NULL);
  long t1sec = t1.tv_sec;

  printf("Usage is:\n    %s -w width -h height -d device -f fps\n\n", args[0]);


  //Processing arguments
  for(int i=1; i<argc-1; i++) {
    string a=args[i];
    if(a=="-w") {
      ww=atoi(args[i+1]);
    } else if(a=="-h") {
      hh=atoi(args[i+1]);
    } else if(a=="-d") {
      dev=args[i+1];
    } else if(a=="-f") {
      fps=atoi(args[i+1]);
    }

  }


  // 1) Instance a Camera object
  Camera c(dev, ww, hh, fps);



  cvNamedWindow("v4l2cam", CV_WINDOW_AUTOSIZE);

  IplImage *l=cvCreateImage(cvSize(ww, hh), 8, 3);
  unsigned char *l_=(unsigned char *)l->imageData;


  double lastFrame = 0;
  int frame = 0;

  while(1){
    // 2) Grab next frame
    c.Update();


    // 3) Convert to OpenCV format  (default is YUYV, stored into c.data[] )
    c.toIplImage(l);

    gettimeofday(&t2, NULL);
    double ellapsed = (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec) / 1000000.0;

    cout << "frame:" << frame << " dT:" << (ellapsed - lastFrame) << endl;



    cvShowImage("v4l2cam", l);

    if( (cvWaitKey(1) & 255) == 27 ) break;

    lastFrame = ellapsed;

    frame++;
  }



  cvDestroyWindow("l");
  cvReleaseImage(&l);


  // 4) Automatic cleanup is done when the app terminates

  return 0;
}
