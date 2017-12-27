# Golang Wrapper for YOLO/Darknet Framework

[Darknet](https://github.com/pjreddie/darknet) is an open source neural network framework written in C and CUDA. It is fast, easy to install, and supports CPU and GPU computation.

**go-yolo** wraps darknet with cgo.

- [darknet](http://pjreddie.com/darknet/)
- [YOLO (You only look once)](http://pjreddie.com/darknet/yolo/)

## Features

Currently, the wrapper can recognize objects from webcam/video or a image file. Equivalent to

```sh
# image
./darknet detect cfg/yolo.cfg yolo.weights data/dog.jpg
# webcom
./darknet detector demo cfg/coco.data cfg/yolo.cfg yolo.weights
# video
./darknet detector demo cfg/coco.data cfg/yolo.cfg yolo.weights /path/video.mp4
```

## Prerequisites

Requires:

- OpenCV (version 2 or 3 is optional) to be installed on your system.

  For example, install opencv2 with Brew on MacOS:
  
  ``` sh
  brew install opencv@2
  sudo chown -R $(whoami):admin /usr/local
  brew link --force opencv@2
  ```

- darknet is installed correctly on your system

  There are two ways to install it.

  1. Install [official version](https://github.com/pjreddie/darknet)
  
  ```sh
  git clone https://github.com/pjreddie/darknet
  cd darknet
  make OPENCV=1 # optionally GPU=1
  cp libdarknet.a /usr/local/lib
  cp include/darknet.h /usr/local/include
  ```
  
  2. Install [this fork](https://github.com/ZanLabs/darknet.git)
  
  ```sh
  git clone https://github.com/ZanLabs/darknet.git
  cd darknet
  make OPENCV=1 # optionally GPU=1
  make install
  ```

The fork contains some workaround to [makefile](https://github.com/pjreddie/darknet/compare/master...ZanLabs:master).

- Makefile is extended to build a static library (darknet.a).
- Makefile is extended with `install` and `uninstall` commands which install the library globally so that this module can easily find and link it.


## Installation

```sh
go get github.com/ZanLabs/go-yolo
```

## Usage

Firstly prepare your `cfg`, `data` folders and download `.weight` files from the darknet project.


Detect on a single image:

```golang
import (
    "github.com/ZanLabs/go-yolo"
)

yolo.ImageDetector(
        "./cfg/coco.data", // datacfg
        "./cfg/yolo.cfg",  // cfgfile
        "./yolo.weights",  // weightfile
        "./data/dog.jpg",  // image that you want recognize
        0.24,					// thresh default: 0.24
        0.5)					// hierThresh default: 0.5
```

Detect a video from a file:

```golang
import (
    "github.com/ZanLabs/go-yolo"
)

yolo.VideoDetector(
        "./cfg/coco.data", // datacfg
        "./cfg/yolo.cfg",  // cfgfile
        "./yolo.weights",  // weightfile
        "/path/video.mp4", // video that you want recognize
        0.24,              // thresh default: 0.24
        0.5,               // hierThresh default: 0.5
        false)             // whether save frames
```

Detect video from camera:

```golang
import (
    "github.com/ZanLabs/go-yolo"
)

yolo.CameraDetector(
        "./cfg/coco.data", // datacfg
        "./cfg/yolo.cfg",  // cfgfile
        "./yolo.weights",  // weightfile
        0,                 // Camera device default: 0
        0.24,              // thresh default: 0.24
        0.5,               // hierThresh default: 0.5
        false)             // whether save frames
```

Finally if you save frames, you can use the below command to reassemble these frames to a video.

``` sh
ffmpeg -framerate 25 -i output_%08d.jpg output.mp4
```
