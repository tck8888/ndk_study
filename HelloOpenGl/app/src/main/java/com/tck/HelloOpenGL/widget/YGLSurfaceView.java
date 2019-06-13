package com.tck.HelloOpenGL.widget;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

/**
 * <p>description:</p>
 * <p>created on: 2019/6/11 8:43</p>
 *
 * @author tck
 * @version 3.5.2
 */
public class YGLSurfaceView extends GLSurfaceView {

    private YRenderer renderer;

    //默认正常速度
    private Speed mSpeed = Speed.MODE_NORMAL;

    public enum Speed {
        MODE_EXTRA_SLOW, MODE_SLOW, MODE_NORMAL, MODE_FAST, MODE_EXTRA_FAST
    }


    public YGLSurfaceView(Context context) {
        this(context, null);
    }

    public YGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);

        //设置EGL的版本
        setEGLContextClientVersion(2);
        renderer = new YRenderer(this);
        setRenderer(renderer);

        //设置按需渲染 当我们调用 requestRender 请求GLThread 回调一次 onDrawFrame
        // 连续渲染 就是自动的回调onDrawFrame
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        super.surfaceDestroyed(holder);
        renderer.onSurfaceDestroyed();
    }

    public void setSpeed(Speed speed){
        mSpeed = speed;
    }

    public void startRecord() {
        float speed = 1.f;
        switch (mSpeed) {
            case MODE_EXTRA_SLOW:
                speed = 0.3f;
                break;
            case MODE_SLOW:
                speed = 0.5f;
                break;
            case MODE_NORMAL:
                speed = 1.f;
                break;
            case MODE_FAST:
                speed = 1.5f;
                break;
            case MODE_EXTRA_FAST:
                speed = 3.f;
                break;
        }
        renderer.startRecord(speed);
    }

    public void stopRecord() {
        renderer.stopRecord();
    }
}
