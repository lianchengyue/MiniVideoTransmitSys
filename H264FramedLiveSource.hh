/*=============================================================================
 * #     FileName: H264FramedLiveSource.hh
 * #         Desc: 
 * #               
 * #       Author: licaibiao
 * #      Version: 
 * #   LastChange: 2017-02-24 
 * =============================================================================*/
#ifndef _H264FRAMEDLIVESOURCE_HH
#define _H264FRAMEDLIVESOURCE_HH
#include <FramedSource.hh>
#include <UsageEnvironment.hh>
//#include "encoder_define.hh"
#include "H264Encoder.h"

class UVCCamera
{
public:
    void init_mmap(void);
    void init_camera(void);
    void open_camera(void);
    
    void close_camera(void);
    void read_one_frame(void);
    int getnextframe(void);
    void start_capture(void);
    void stop_capture(void);
    int  camera_able_read(void);
    void Init();
	void intoloop();
    //void GetNextFrame();
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
};
#endif
