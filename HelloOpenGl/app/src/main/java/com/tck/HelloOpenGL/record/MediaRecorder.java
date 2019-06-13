package com.tck.HelloOpenGL.record;

import android.content.Context;
import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaExtractor;
import android.media.MediaFormat;
import android.media.MediaMuxer;
import android.opengl.EGLContext;
import android.os.Handler;

import android.os.HandlerThread;
import android.os.Looper;
import android.view.Surface;

import java.io.IOException;


/**
 * <p>description:</p>
 * <p>created on: 2019/6/13 12:42</p>
 *
 * @author tck
 * @version 3.5.2
 */
public class MediaRecorder {

    private final Context mContext;
    private final String mPath;
    private final int mWidth;
    private final int mHeight;
    private final EGLContext mEglContext;
    private MediaCodec mMediaCodec;
    private Surface mInputSurface;
    private MediaMuxer mMediaMuxer;
    private Handler mHandler;
    private EGLBase mEglBase;
    private boolean isStart;
    private int index;
    private float mSpeed;

    public MediaRecorder(Context context, String path, int width, int height,EGLContext eglContext) {
        mContext = context.getApplicationContext();
        mPath = path;
        mWidth = width;
        mHeight = height;
        mEglContext = eglContext;
    }

    public void start() throws IOException {
        /**
         * 配置MediaCodec 编码器
         */
        //视频格式
        // 类型（avc高级编码 h264） 编码出的宽、高
        // 类型（avc高级编码 h264） 编码出的宽、高
        MediaFormat mediaFormat = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, mWidth, mHeight);
        //参数配置
        // 1500kbs码率
        mediaFormat.setInteger(MediaFormat.KEY_BIT_RATE, 1500_000);
        //帧率
        mediaFormat.setInteger(MediaFormat.KEY_FRAME_RATE, 20);
        //关键帧间隔
        mediaFormat.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, 20);
        //颜色格式（RGB\YUV）
        //从surface当中回去
        mediaFormat.setInteger(MediaFormat.KEY_COLOR_FORMAT, MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface);
        //编码器
        mMediaCodec = MediaCodec.createEncoderByType(MediaFormat.MIMETYPE_VIDEO_AVC);
        //将参数配置给编码器
        mMediaCodec.configure(mediaFormat, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        //交给虚拟屏幕 通过opengl 将预览的纹理 绘制到这一个虚拟屏幕中
        //这样MediaCodec 就会自动编码 inputSurface 中的图像
        mInputSurface = mMediaCodec.createInputSurface();



        //  H.264
        // 播放：
        //  MP4 -> 解复用 (解封装) -> 解码 -> 绘制
        //封装器 复用器
        // 一个 mp4 的封装器 将h.264 通过它写出到文件就可以了
        mMediaMuxer = new MediaMuxer(mPath, MediaMuxer.OutputFormat.MUXER_OUTPUT_MPEG_4);



        /**
         * 配置EGL环境
         */
        //Handler ： 线程通信
        // Handler: 子线程通知主线程
//        Looper.loop();
        HandlerThread handlerThread = new HandlerThread("VideoCodec");
        handlerThread.start();
        Looper looper = handlerThread.getLooper();
        // 用于其他线程 通知子线程
        mHandler = new Handler(looper);

        //子线程： EGL的绑定线程 ，对我们自己创建的EGL环境的opengl操作都在这个线程当中执行
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                //创建我们的EGL环境 (虚拟设备、EGL上下文等)
                mEglBase = new EGLBase(mContext, mWidth, mHeight, mInputSurface, mEglContext);
                //启动编码器
                mMediaCodec.start();
                isStart = true;
            }
        });

    }
}
