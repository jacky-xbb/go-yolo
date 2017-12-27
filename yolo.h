#ifndef _GO_YOLO_BINDING_H_
#define _GO_YOLO_BINDING_H_

#include <cv.h>
#include <highgui.h>

// Recognize a image
void image_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename,
	float thresh, float hier_thresh, char *outfile);

// Recognize a video
void video_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename,
	float thresh, float hier_thresh, char *prefix);

// Recognize a camera stream
void camera_detector(char *datacfg, char *cfgfile, char *weightfile, int camindex,
        float thresh, float hier_thresh, char *prefix);


#endif // _GO_YOLO_BINDING_H_
