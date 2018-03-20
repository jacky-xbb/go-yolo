// Copyright 2017 <yummy.bian@gmail.com>. All rights reserved.

// Package yolo provides darknet binding.
package yolo

// #cgo pkg-config: opencv
// #cgo linux LDFLAGS: -ldarknet -lm -L/usr/local/cuda/lib64 -lcuda -lcudart -lcublas -lcurand -lcudnn
// #cgo darwin LDFLAGS: -ldarknet
// #include "yolo.h"
import "C"

// SetGPU set a gpu device you want
func SetGPU(gpu int) {
	C.set_gpu(C.int(gpu))
}

// ImageDetector recognize a image
func ImageDetector(dc, cf, wf, fn string, t, ht float64, of ...string) {
    if len(of) > 0 {
        C.image_detector(
            C.CString(dc),
            C.CString(cf),
            C.CString(wf),
            C.CString(fn),
            C.float(t),
            C.float(ht),
            C.CString(of[0]))
    } else {
        C.image_detector(
            C.CString(dc),
            C.CString(cf),
            C.CString(wf),
            C.CString(fn),
            C.float(t),
            C.float(ht),
            nil)
    }
}

// VideoDetector recognize a video
func VideoDetector(dc, cf, wf, fn string, t, ht float64, of ...string) {
    if len(of) > 0 {
        C.video_detector(
            C.CString(dc),
            C.CString(cf),
            C.CString(wf),
            C.CString(fn),
            C.float(t),
            C.float(ht),
            C.CString(of[0]))
    } else {
        C.video_detector(
            C.CString(dc),
            C.CString(cf),
            C.CString(wf),
            C.CString(fn),
            C.float(t),
            C.float(ht),
            nil)
    }
}

// CameraDetector recognize a camera stream
func CameraDetector(dc, cf, wf string, i int, t, ht float64, of ...string) {
    if len(of) > 0 {
        C.camera_detector(
            C.CString(dc),
            C.CString(cf),
            C.CString(wf),
            C.int(i),
            C.float(t),
            C.float(ht),
            C.CString(of[0]))
    } else {
        C.camera_detector(
            C.CString(dc),
            C.CString(cf),
            C.CString(wf),
            C.int(i),
            C.float(t),
            C.float(ht),
            nil)
    }
}
