#include "export_wrapper.h"
#include "vision.h"


vision vision_util = vision();


bool InitNet()
{
	return vision_util.init();
}


void CloseNet()
{
	vision_util.close();
}


bool GetImage(unsigned char* data)
{
	return vision_util.get_raw_image_bytes(data);
}
