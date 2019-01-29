#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H264Encoder.h"


void H264Encoder::init_encoder(void)
{
    compress_begin(&en, WIDTH, HEIGHT);
//    h264_buf = (char *) malloc( WIDTH * HEIGHT * 2);
}


void H264Encoder::compress_begin(Encoder *en, int width, int height)
{
    en->param = (x264_param_t *) malloc(sizeof(x264_param_t));
    en->picture = (x264_picture_t *) malloc(sizeof(x264_picture_t));
    x264_param_default(en->param); //set default param


    en->param->i_frame_reference=3;
    en->param->rc.i_rc_method=X264_RC_ABR;
    en->param->b_cabac =0;
    en->param->b_interlaced=0;
    en->param->i_level_idc=30;
    en->param->i_keyint_max=en->param->i_fps_num*1.5;
    en->param->i_keyint_min=1;
    en->param->i_threads  = X264_SYNC_LOOKAHEAD_AUTO;
    en->param->i_width = WIDTH;
    en->param->i_height = HEIGHT;
    en->param->i_frame_total = 0;
    en->param->i_keyint_max = 10;
    en->param->rc.i_lookahead = 0;
    en->param->i_bframe = 5;
    en->param->b_open_gop = 0;
    en->param->i_bframe_pyramid = 0;
    en->param->i_bframe_adaptive = X264_B_ADAPT_TRELLIS;
    en->param->rc.i_bitrate = 1024 * 10;
    en->param->i_fps_num = 25;
    en->param->i_fps_den = 1;



#if 0
    en->param->i_threads  = X264_SYNC_LOOKAHEAD_AUTO;
    en->param->i_width = WIDTH; //set frame width
    en->param->i_height = HEIGHT; //set frame height
    en->param->rc.i_lookahead = 0;
    en->param->i_fps_num = 30;
    en->param->i_fps_den = 1;
#endif

#ifdef YUYV
    en->param->i_csp = X264_CSP_I422;
    x264_param_apply_profile(en->param, x264_profile_names[4]);

    if ((en->handle = x264_encoder_open(en->param)) == 0) {
        return;
    }

    x264_picture_alloc(en->picture, X264_CSP_I422, en->param->i_width,
            en->param->i_height);
#else
    en->param->i_csp = X264_CSP_I420;
    x264_param_apply_profile(en->param, x264_profile_names[4]);

    if ((en->handle = x264_encoder_open(en->param)) == 0) {
        return;
    }

    x264_picture_alloc(en->picture, X264_CSP_I420, en->param->i_width,
            en->param->i_height);
#endif
}

int H264Encoder::compress_frame(Encoder *en, int type, unsigned char *in, int len, unsigned char *out)
{
    x264_picture_t pic_out;
    int index_y, index_u, index_v;
    int num;
    int nNal = -1;
    int result = 0;
    int i = 0;
    unsigned char *p_out = out;
    char *y = (char*)en->picture->img.plane[0];
    char *u = (char*)en->picture->img.plane[1];
    char *v = (char*)en->picture->img.plane[2];

#ifdef YUYV
    //YUYV
    index_y = 0;
    index_u = 0;
    index_v = 0;

    num = WIDTH * HEIGHT * 2 - 4  ;

    for(i=0; i<num; i=i+4)
    {
            *(y + (index_y++)) = *(in + i);
            *(u + (index_u++)) = *(in + i + 1);
            *(y + (index_y++)) = *(in + i + 2);
            *(v + (index_v++)) = *(in + i + 3);
     }
#else
    //I420
    memcpy(y,in,307200);
    memcpy(u,in+307200,76800);
    memcpy(v,in+384000,76800);
#endif

    switch (type) {
    case 0:
        en->picture->i_type = X264_TYPE_P;
        break;
    case 1:
        en->picture->i_type = X264_TYPE_IDR;
        break;
    case 2:
        en->picture->i_type = X264_TYPE_I;
        break;
    default:
        en->picture->i_type = X264_TYPE_AUTO;
        break;
    }

    en->picture->i_pts ++;

    if (x264_encoder_encode(en->handle, &(en->nal), &nNal, en->picture,
            &pic_out) < 0) {
        return -1;
    }

    for (i = 0; i < nNal; i++) {
        memcpy(p_out, en->nal[i].p_payload, en->nal[i].i_payload);
        p_out += en->nal[i].i_payload;
        result += en->nal[i].i_payload;
    }

    return result;
}

void H264Encoder::compress_end(Encoder *en)
{
    if (en->handle) {
        x264_encoder_close(en->handle);
    }
    if (en->picture) {
        x264_picture_clean(en->picture);
        free(en->picture);
        en->picture = 0;
    }
    if (en->param) {
        free(en->param);
        en->param = 0;
    }
}


void H264Encoder::Destory()
{
    close_encoder();
}

void H264Encoder::close_encoder()
{
    compress_end(&en);
//    free(h264_buf);
}

#if 1
//H264Processor
size_t H264Encoder::encode_frame(unsigned char* input_frame, size_t input_frame_length, unsigned char* h264_buf/*, unsigned int* h264_length*/)
{
#if 1
    int h264_length = 0;
    static int count = 0;
    //h264_length = compress_frame(&en, -1, yuv_frame, , h264_buf);
    h264_length = compress_frame(&en, -1, input_frame, input_frame_length, h264_buf);
    if (h264_length > 0)
    {
        /*
        if(fwrite(h264_buf, h264_length, 1, h264_fp)>0)
        {
            printf("encode_frame num = %d\n",count++);
        }
        else
        {
            perror("encode_frame fwrite err\n");
        }
        */
//        printf("encode_frame num = %d, size =%d\n",count++, h264_length);
//        printf("h264_buf[20]= %c\n",h264_buf[20]);
    }

    return h264_length;
#else
    //int h264_length = 0;
    static int count = 0;
    //h264_length = compress_frame(&en, -1, yuv_frame, , h264_buf);
    *h264_length = compress_frame(&en, -1, input_frame, input_frame_length, h264_buf);
    if (*h264_length > 0)
    {
        /*
        if(fwrite(h264_buf, h264_length, 1, h264_fp)>0)
        {
            printf("encode_frame num = %d\n",count++);
        }
        else
        {
            perror("encode_frame fwrite err\n");
        }
        */
        printf("encode_frame num = %d, size =%d\n",count++, *h264_length);
    }
#endif
}

#endif
