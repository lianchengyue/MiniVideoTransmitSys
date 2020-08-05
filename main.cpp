#include "H264VideoStreamer.h"

int main()
{
#ifdef FROM_CAMERA
    //从camera加载
    startH264VideoStream();
#elif defined FROM_FILE_NV21
    //从文件加载
    startH264StreamFromFile();
#endif
    return 0;
}
