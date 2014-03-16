
/*
 * Copyright (C) 2013 Bob Mottram
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
 */

// Single webcam demo

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "v4l2cam.h"

using namespace std;


int main(int argc, char **args) {
	int ww = 640;
	int hh = 480;
	int fps = 30;

	const char *dev="/dev/video1";

	printf("Usage is:\n    %s -w width -h height -d device -f fps\n\n", args[0]);

	// Processing arguments
	for (int i = 1; i < argc-1; i++) {
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

	/* allocate memory for the grabbed frames */
	unsigned char *img = new unsigned char[ww * hh * 4];

	int itt = 0;

	while (itt < 20) {
		// 2) Grab next frame
		c.Update();

		printf("Frame grabbed %d\n", itt);
		itt++;
	}

	// deallocate the frame buffer
	delete img;

	// 4) Automatic cleanup is done when the app terminates
	return 0;
}
