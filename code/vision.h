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
	
	/** Video Feed */
	cv::VideoCapture _capture;
	
	/** Torch Model Loader */
	torch::jit::script::Module module;

	/** Path for Our Model  ( REPLACE PATH AS NEEDED ) */
	const string model_path = "C:/git-clone-tests/basic-libtorch-dll/models/traced_style_transfer_model_gpu.pt";
	
	/** Camera Stuff */
	int cam_id = 0;
	cv::Mat frame;
	
	/** Capture dimensions */
	int frame_width = 1920;
	int frame_height = 1080;
	
	/** Outut Dimensions */
	int out_width = 512;
	int out_height = 512;
	
	/** Neural Net Resolution */
	int run_size = 512;


public:

	vision();

	/**
	 * Open camera, and initiate model.
	 * @return Whether the operation was sucessfull.
	 */
	bool init();

	/**
	 * Close camera
	 */
	void close();

	/**
	 * Run neural net on camera feed and return output.
	 * @param data - Array to ouput raw data to.
	 * @return Whether the operation was sucessfull.
	 */
	bool get_raw_image_bytes(unsigned char* data);

	~vision();
};

