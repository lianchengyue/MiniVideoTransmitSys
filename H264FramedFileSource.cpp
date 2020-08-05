  /*
*  H264FramedLiveSource.cpp
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>
#include <assert.h>
#include "H264FramedFileSource.hh"
#include <BasicUsageEnvironment.hh>
#include "Utils.h"

extern class YUVFile Yuvfile;

void YUVFile::open_file(void)
{
    input_fd = fopen("nv21_input.yuv", "rb");
    if (!input_fd)
    {
        printf("Open YUV File Failed\n");
        exit(EXIT_FAILURE);
    }
}

void YUVFile::init_file(void)
{
    uint64_t file_size = 0;

    frmIdx = 0;

    lumaPlaneSize = WIDTH * HEIGHT;
    chromaPlaneSize = lumaPlaneSize >> 2;
    sourceFrameSize = lumaPlaneSize + chromaPlaneSize + chromaPlaneSize;

    yuv_buf = new uint8_t[sourceFrameSize];

    memset(yuv_buf, 0, sourceFrameSize);

    fseek(input_fd, 0, SEEK_END);
    file_size = ftell(input_fd);
    fseek(input_fd, 0, SEEK_SET);

    totalFrames = file_size / (lumaPlaneSize + chromaPlaneSize + chromaPlaneSize);

    printf("YUV帧尺寸为:%d\n", sourceFrameSize);
    printf("YUV总帧数为:%d\n", totalFrames);
}

void YUVFile::read_one_frame(void)
{
    uint32_t result;

    //当前帧在文件中的偏移量：当前index * 每一帧的大小
    fileOffset = (uint64_t)sourceFrameSize * frmIdx;
    //seek到偏移处
    result = fseek(input_fd, fileOffset, SEEK_SET);
    if (result == -1)
    {
        printf("从文件中读取帧失败\n");
        exit(EXIT_FAILURE);
    }

    //读取当前帧的Y、U、V数据
    if(0 == fread(yuv_buf, sourceFrameSize, 1, input_fd)){
        //fread==0时读取结束，退出程序
        printf("从文件中读取帧结束\n");
        this->Destory();
        exit(EXIT_FAILURE);
    }

    //读取当前帧的Y、U、V数据
    //fread(yuv_buf, sourceFrameSize, 1, input_fd);

    h264_frame_len = h264encoder.encode_frame((unsigned char *)yuv_buf, sourceFrameSize, (unsigned char*)h264_buf);

    frmIdx++;
}

void YUVFile::close_file(void)
{
    fclose(input_fd);
}


int YUVFile::getnextframe(void)
{
    int ret = 1;

    if(ret > 0)
    {
        //printf("getnextframe...\n");
        read_one_frame();
        ///fwrite(Yuvfile.h264_buf, Yuvfile.h264_frame_len, 1, Yuvfile.pipe_fd);
        return 0;
    }
    else
    {
        printf("Read Frame Failed!\n");
        return -1;
    }
}

void YUVFile::Init()
{
    open_file();
    init_file();
    //H264 Encoder
    h264encoder.init_encoder();
    //h264_buf
    h264_buf = (unsigned char *) malloc( WIDTH * HEIGHT * 2);
}

void YUVFile::Destory()
{
    close_file();
    //H264 Encoder
    h264encoder.close_encoder();
    //h264_buf
    free(h264_buf);
}

