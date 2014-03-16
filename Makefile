all:
	$(MAKE) test
	$(MAKE) test-opencv

test: v4l2cam.o test.cpp
	g++ -o test test.cpp v4l2cam.o

test-opencv: v4l2cam.o test-opencv.cpp
	g++ -o test-opencv test-opencv.cpp v4l2cam.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_legacy

v4l2cam.o: v4l2cam.cpp v4l2cam.h
	g++ -c v4l2cam.cpp

clean:
	rm -f v4l2cam.o test test-opencv