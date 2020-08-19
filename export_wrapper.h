#define DataStorage_API __declspec(dllexport)
#ifdef __cplusplus 


extern "C"
{
#endif

	DataStorage_API bool InitNet();

#ifdef __cplusplus
}


extern "C"
{
#endif

	DataStorage_API void CloseNet();

#ifdef __cplusplus
}


extern "C"
{
#endif

	DataStorage_API bool GetImage(unsigned char* data);

#ifdef __cplusplus
}

#endif