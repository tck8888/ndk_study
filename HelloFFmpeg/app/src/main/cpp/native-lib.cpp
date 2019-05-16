#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,"testff",__VA_ARGS__)
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include <iostream>

using namespace std;

static double r2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0. : (double) r.num / (double) r.den;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_healthmudi_dia_helloffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    hello += avcodec_configuration();
    //1.初始化解封装
    av_register_all();
    //2.初始化网络
    avformat_network_init();
    //打开文件
    AVFormatContext *ic = NULL;
    char path[] = "/sdcard/DCIM/Camera/VID_20190516_130700.mp4";

    int re = avformat_open_input(&ic, path, 0, 0);
    if (re != 0) {
        LOGW("avformat_open_input %s failed", av_err2str(re));
        return env->NewStringUTF(hello.c_str());
    }

    LOGW("avformat_open_input %s success", path);
    //获取流信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        LOGW("avformat_find_stream_info %s failed", av_err2str(re));
    }
    LOGW("duration = %lld nb_streams=%d", ic->duration, ic->nb_streams);

    int fps = 0;
    int videoStream = 0;
    int audioStream = 1;
    for (int i = 0; i < ic->nb_streams; ++i) {
        AVStream *as = ic->streams[i];
        if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) { ;
            videoStream = i;
            //AVPixelFormat
            fps = r2d(as->avg_frame_rate);
            LOGW("视频数据fps=%d,width = %d height=%d, codec_id=%d,pixFormat=%d",
                 fps,
                 as->codecpar->width,
                 as->codecpar->height,
                 as->codecpar->codec_id,
                 as->codecpar->format
            );
        } else if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioStream = i;
            LOGW("音频数据sample_rate=%d,channels=%d sample_format=%d",
                 as->codecpar->sample_rate,
                 as->codecpar->channels,
                 as->codecpar->format
            );
        }
    }

    //获取音频流数据
    audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    LOGW("av_find_best_stream =%d ", audioStream);

    //读取帧数据
    AVPacket *pkt = av_packet_alloc();
    for (;;) {
        int re = av_read_frame(ic, pkt);
        if (re != 0) {
            LOGW("读取到结尾");
            int pos = 20 * r2d(ic->streams[videoStream]->time_base);
            av_seek_frame(ic, videoStream, ic->duration / 2,
                          AVSEEK_FLAG_BACKWARD || AVSEEK_FLAG_FRAME);
            continue;
        }
        LOGW("stream=%d size=%d pts=%lld flag=%d",
             pkt->stream_index, pkt->size, pkt->pts, pkt->flags
        );
        //其他操作

        av_packet_unref(pkt);
    }

    //关闭上下文
    avformat_close_input(&ic);
    return env->NewStringUTF(hello.c_str());

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_healthmudi_dia_helloffmpeg_MainActivity_open(JNIEnv *env, jobject instance, jstring url_,
                                                      jobject handle) {
    const char *url = env->GetStringUTFChars(url_, 0);

    // TODO
    FILE *fp = fopen(url, "rb");
    if (!fp) {
        LOGW("%s open failed", url);
    } else {
        LOGW("%s open success", url);
        fclose(fp);
    }
    env->ReleaseStringUTFChars(url_, url);

    return true;
}