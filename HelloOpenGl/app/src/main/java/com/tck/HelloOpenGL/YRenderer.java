package com.tck.HelloOpenGL;

import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import com.tck.HelloOpenGL.util.CameraHelper;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * <p>description:</p>
 * <p>created on: 2019/6/11 8:47</p>
 *
 * @author tck
 * @version 3.5.2
 */
public class YRenderer implements GLSurfaceView.Renderer, SurfaceTexture.OnFrameAvailableListener {

    private CameraHelper cameraHelper;
    private SurfaceTexture surfaceTexture;
    private YGLSurfaceView yglSurfaceView;

    private float[] mtx = new float[16];

    public YRenderer(YGLSurfaceView yglSurfaceView) {
        this.yglSurfaceView = yglSurfaceView;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        cameraHelper = new CameraHelper(Camera.CameraInfo.CAMERA_FACING_BACK);
        //创建纹理id
        int[] textures = new int[1];
        GLES20.glGenTextures(textures.length, textures, 0);
        surfaceTexture = new SurfaceTexture(textures[0]);
        surfaceTexture.setOnFrameAvailableListener(this);
    }

    /**
     * 画布发生了变化
     *
     * @param gl10
     * @param i
     * @param i1
     */
    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        //开启预览
        cameraHelper.startPreview(surfaceTexture);
    }

    /**
     * 开始画画
     *
     * @param gl10
     */
    @Override
    public void onDrawFrame(GL10 gl10) {
        // 配置屏幕
        //清理屏幕 :告诉opengl 需要把屏幕清理成什么颜色
        GLES20.glClearColor(0, 0, 0, 0);
        //执行上一个：glClearColor配置的屏幕颜色
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        // 把摄像头的数据先输出来
        // 更新纹理，然后我们才能够使用opengl从SurfaceTexure当中获得数据 进行渲染
        surfaceTexture.updateTexImage();
        //surfaceTexture 比较特殊，在opengl当中 使用的是特殊的采样器 samplerExternalOES （不是sampler2D）
        //获得变换矩阵
        surfaceTexture.getTransformMatrix(mtx);
    }

    /**
     * @param surfaceTexture
     */
    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        yglSurfaceView.requestRender();
    }
}
