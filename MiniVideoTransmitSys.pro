QT += core
QT -= gui

CONFIG += c++11

TARGET = MiniVideoTransmitSys
CONFIG += console
CONFIG -= app_bundle
DEFINES += \
    #YUYV \
    NV21 \
    DUMP_H264 \
    #FROM_CAMERA \
    FROM_FILE_NV21 \

TEMPLATE = app

SOURCES += main.cpp \
    H264FramedLiveSource.cpp \
    H264VideoStreamer.cpp \
    H264Encoder.cpp \
    H264FramedFileSource.cpp

DISTFILES += \
    MiniVideoTransmitSys.pro.user \
    zoom_aml_test.yuv

HEADERS += \
#    include/x264/x264.h \
    include/x264/x264_config.h \
    include/encoder/encoder_define.hh \
    include/encoder/H264FramedLiveSource.hh \
    include/encoder/H264Encoder.h \
    H264VideoStreamer.h \
    include/encoder/H264FramedFileSource.hh \
    include/Utils.h

INCLUDEPATH += \
#opencv
/usr/local/opencv2.4.13/include \
/usr/local/opencv2.4.13/include/opencv \
/usr/local/opencv2.4.13/include/opencv2 \
#h264
#live555
#/home/montafan/software_download/live555/UsageEnvironment/include \
#/home/montafan/software_download/live555/BasicUsageEnvironment/include \
#/home/montafan/software_download/live555/liveMedia/include \
#/home/montafan/software_download/live555/groupsock/include \
/usr/local/include/UsageEnvironment \
/usr/local/include/BasicUsageEnvironment \
/usr/local/include/liveMedia \
/usr/local/include/groupsock \
#hikvision
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/incCn \
#this project
/home/montafan/Qt5.6.2/project/rtspClient/include \
/home/montafan/Qt5.6.2/project/rtspClient/include/encoder \


LIBS +=  \
#opencv
/usr/local/opencv2.4.13/lib/libopencv_*.so \
#h264
#/usr/lib/x86_64-linux-gnu/libx264.so \
/usr/lib/libx264.so \
#ffmpeg
#-lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswscale -lswresample \
-lavformat -lavutil -lswscale -lswresample \
#-lx264
#-lmp3lame -lz -lbz2 -llzma -lva \
#live555
/usr/local/lib/libliveMedia.a \
/usr/local/lib/libgroupsock.a \
/usr/local/lib/libBasicUsageEnvironment.a \
/usr/local/lib/libUsageEnvironment.a \
#hikvison
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/libhcnetsdk.so\
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/libHCCore.so\
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/libhpr.so\
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/libPlayCtrl.so\
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/libSuperRender.so\
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/libAudioRender.so \
#/home/montafan/software_download/CH_HCNetSDK_V5.3.5.2/lib/HCNetSDKCom/lib*.so \
