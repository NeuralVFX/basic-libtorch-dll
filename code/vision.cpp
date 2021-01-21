#include "vision.h"


vision::vision()
{

}


bool vision::init()
{
	// Load Torch Style Transfer Model 
	module = torch::jit::load(model_path, torch::kCUDA);

	// Setup Open CV Capture
	_capture.open(cam_id);
	_capture.set(cv::CAP_PROP_FRAME_WIDTH, frame_width);
	_capture.set(cv::CAP_PROP_FRAME_HEIGHT, frame_height);
	return _capture.isOpened();
}


void vision::close()
{
	_capture.release();
}


bool vision::get_raw_image_bytes(unsigned char* data)
{
	_capture >> frame;
	if (frame.empty())
		return false;

	// Resize Input Frame to Output Texture Size
	cv::Mat resize(run_size, run_size, frame.type());
	cv::resize(frame, resize, resize.size(), 0, 0);

	// Convert Color Space and Bit Depth
	cv::cvtColor(resize, resize, cv::COLOR_BGR2RGB);
	resize.convertTo(resize, CV_32FC3, 1.0f / 255.0f);

	// Convert to Torch Tensor and Normalize
	auto input_tensor = torch::from_blob(resize.data,
		{ 1, run_size, run_size, 3 });

	input_tensor = input_tensor.permute({ 0, 3, 1, 2 });
	input_tensor = input_tensor.sub(.5).mul(2.0);
	input_tensor = input_tensor.to(torch::kCUDA);

	// Pass Data Through Neural Net to Get Output
	std::vector<torch::jit::IValue> inputs;
	inputs.push_back(input_tensor);
	at::Tensor result= module.forward(inputs).toTensor();
	at::Tensor out_tensor = result.detach().to(torch::kCPU);

	// Prepair Tensor To Convert to OpenCV
	out_tensor = out_tensor.permute({ 0, 2, 3, 1 }).squeeze(0);
	out_tensor = out_tensor.add(1).mul(.5);
	out_tensor = out_tensor.mul(255).clamp(0, 255).to(torch::kU8);

	// Copy Tensor Data into MAT
	cv::Mat result_img(run_size, run_size, CV_8UC3);
	std::memcpy((void *)result_img.data,
		out_tensor.contiguous().data_ptr(),
		sizeof(torch::kU8) * out_tensor.numel());

	cv::Mat out_img(out_height, out_width, frame.type());

	// Resize and Convert Color for Unreal Engine
	cv::resize(result_img, out_img, out_img.size(), cv::INTER_CUBIC);
	cv::Mat argb_img;
	cv::cvtColor(out_img, argb_img, cv::COLOR_RGB2BGRA);

	// Copy OpenCV Output into Unreal Engine Pointer
	memcpy(data, argb_img.data, argb_img.total() * argb_img.elemSize());

	cv::waitKey(1);
	return true;
}


vision::~vision()
{
	_capture.release();
}
