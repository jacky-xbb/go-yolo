#include <darknet.h>
#include "yolo.h"


void set_gpu(int gpu)
{
    cuda_set_device(gpu);
}

void image_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh, float hier_thresh, char *outfile)
{
    list *options = read_data_cfg(datacfg);
    char *name_list = option_find_str(options, "names", "data/names.list");
    char **names = get_labels(name_list);

    image **alphabet = load_alphabet();
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);
    double time;
    char buff[256];
    char *input = buff;
    int j;
    float nms=.3;
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        } else {
            printf("Enter Image Path: ");
            fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return;
            strtok(input, "\n");
        }
        image im = load_image_color(input,0,0);
        image sized = letterbox_image(im, net->w, net->h);
        layer l = net->layers[net->n-1];

        box *boxes = calloc(l.w*l.h*l.n, sizeof(box));
        float **probs = calloc(l.w*l.h*l.n, sizeof(float *));
        for(j = 0; j < l.w*l.h*l.n; ++j) probs[j] = calloc(l.classes + 1, sizeof(float *));
        float **masks = 0;
        if (l.coords > 4){
            masks = calloc(l.w*l.h*l.n, sizeof(float*));
            for(j = 0; j < l.w*l.h*l.n; ++j) masks[j] = calloc(l.coords-4, sizeof(float *));
        }

        float *X = sized.data;
        time=what_time_is_it_now();
        network_predict(net, X);
        printf("%s: Predicted in %f seconds.\n", input, what_time_is_it_now()-time);
        get_region_boxes(l, im.w, im.h, net->w, net->h, thresh, probs, boxes, masks, 0, 0, hier_thresh, 1);
        if (nms) do_nms_sort(boxes, probs, l.w*l.h*l.n, l.classes, nms);
        draw_detections(im, l.w*l.h*l.n, thresh, boxes, probs, masks, names, alphabet, l.classes);
        if(outfile){
              save_image(im, outfile);
         }
         else{
            save_image(im, "predictions");
            cvNamedWindow("predictions", CV_WINDOW_NORMAL);
            show_image(im, "predictions");
            cvWaitKey(0);
            cvDestroyAllWindows();
         }

        free_image(im);
        free_image(sized);
        free(boxes);
        free_ptrs((void **)probs, l.w*l.h*l.n);
        if (filename) break;
    }
}

void video_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename,
        float thresh, float hier_thresh, char *prefix)
{
    int cam_index = 0;
    int frame_skip = 0;
    int avg = 3;

    int fullscreen = 0;
    int width = 0;
    int height = 0;
    int fps = 0;

    list *options = read_data_cfg(datacfg);
    int classes = option_find_int(options, "classes", 20);
    char *name_list = option_find_str(options, "names", "data/names.list");
    char **names = get_labels(name_list);
    demo(cfgfile, weightfile, thresh, cam_index, filename, names, classes, frame_skip,
            prefix, avg, hier_thresh, width, height, fps, fullscreen);
}

void camera_detector(char *datacfg, char *cfgfile, char *weightfile, int camindex,
        float thresh, float hier_thresh, char *prefix)
{
    char *filename = NULL;
    int frame_skip = 0;
    int avg = 3;

    int fullscreen = 0;
    int width = 0;
    int height = 0;
    int fps = 0;

    list *options = read_data_cfg(datacfg);
    int classes = option_find_int(options, "classes", 20);
    char *name_list = option_find_str(options, "names", "data/names.list");
    char **names = get_labels(name_list);
    demo(cfgfile, weightfile, thresh, camindex, filename, names, classes, frame_skip,
            prefix, avg, hier_thresh, width, height, fps, fullscreen);
}
