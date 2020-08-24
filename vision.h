#pragma once
#include <iostream>
#include <stdio.h>
#include <cstdio>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "torch/torch.h"
#include <torch/script.h>
#include <memory>


class vision
{
public:

	// Video Feed
	cv::VideoCapture _capture;

	// Torch Model Loader
	torch::jit::script::Module module;

	// Camera Stuff
	int cam_id = 0;
	cv::Mat frame;

	// Capture dimensions
	int frame_width = 1920;
	int frame_height = 1080;

	// Outut Dimensions
	int out_width = 512;
	int out_height = 512;

	// Neural Net Resolution
	int run_size = 512;


public:

	vision();

	bool init();

	void close();

	bool get_raw_image_bytes(unsigned char* data);

	~vision();
};

