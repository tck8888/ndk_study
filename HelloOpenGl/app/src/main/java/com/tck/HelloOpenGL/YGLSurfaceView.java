package com.tck.HelloOpenGL;

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
}
