#ifndef H264ENCODER_H
#define H264ENCODER_H

#include "encoder_define.hh"
#include "Utils.h"

class H264Encoder
{
public:
    void init_encoder(void);
    void compress_begin(Encoder *en, int width, int height);
    int  compress_frame(Encoder *en, int type, unsigned char *in, int len, unsigned char *out);
    void compress_end(Encoder *en);
    void Destory();
    void close_encoder();
    size_t encode_frame(unsigned char* yuv_frame, size_t yuv_length, unsigned char* h264_buf/*, unsigned int* h264_length*/);

    BUFTYPE *usr_buf;
#ifdef DUMP_H264
    char* h264_file_name;
    FILE *h264_fp;
#endif
    int lumaPlaneSize;
    int chromaPlaneSize;
public:
    Encoder en;
};

#endif // H264ENCODER_H
