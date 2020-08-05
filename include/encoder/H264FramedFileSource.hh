/*=============================================================================
 * #     FileName: H264FramedLiveSource.hh
 * #         Desc: 
 * #               
 * #       Author: licaibiao
 * #      Version: 
 * #   LastChange: 2017-02-24 
 * =============================================================================*/
#ifndef _H264FRAMEDFILESOURCE_HH
#define _H264FRAMEDFILESOURCE_HH
#include <FramedSource.hh>
#include <UsageEnvironment.hh>
#include "H264Encoder.h"

class YUVFile
{
public:
    void init_file(void);
    void open_file(void);

    void close_file(void);
    void read_one_frame(void);
    int getnextframe(void);

    void Init();
	void intoloop();
    void Destory();
public:
    int fd;
	FILE *save_fd;
    int n_nal;
    int h264_frame_len;
    unsigned char *h264_buf;
	unsigned int n_buffer;
	Encoder en;
//	FILE *h264_fp;
    BUFTYPE *usr_buf;
	FILE *pipe_fd;
    FILE *input_fd;
    int lumaPlaneSize;
    int chromaPlaneSize;
    uint32_t sourceFrameSize;
    uint8_t *yuv_buf;  //yuv buffer
    class H264Encoder h264encoder;
    int totalFrames;
    //相对文件位置的偏移量
    uint64_t fileOffset;
    uint32_t frmIdx;
};
#endif
