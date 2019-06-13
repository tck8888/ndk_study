package com.tck.HelloOpenGL;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.RadioGroup;

import com.tck.HelloOpenGL.widget.RecordButton;
import com.tck.HelloOpenGL.widget.YGLSurfaceView;

public class MainActivity extends AppCompatActivity {

    private YGLSurfaceView glSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        glSurfaceView = (YGLSurfaceView) findViewById(R.id.gl_surface_view);

        RecordButton recordButton = findViewById(R.id.btn_record);
        recordButton.setOnRecordListener(new RecordButton.OnRecordListener() {
            /**
             * 开始录制
             */
            @Override
            public void onRecordStart() {
                glSurfaceView.startRecord();
            }

            /**
             * 停止录制
             */
            @Override
            public void onRecordStop() {
                glSurfaceView.stopRecord();
            }
        });

        RadioGroup radioGroup = findViewById(R.id.rg_speed);
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            /**
             * 选择录制模式
             * @param group
             * @param checkedId
             */
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                switch (checkedId){
                    case R.id.rb_extra_slow: 
                        glSurfaceView.setSpeed(YGLSurfaceView.Speed.MODE_EXTRA_SLOW);
                        break;
                    case R.id.rb_slow:
                        glSurfaceView.setSpeed(YGLSurfaceView.Speed.MODE_SLOW);
                        break;
                    case R.id.rb_normal:
                        glSurfaceView.setSpeed(YGLSurfaceView.Speed.MODE_NORMAL);
                        break;
                    case R.id.rb_fast:
                        glSurfaceView.setSpeed(YGLSurfaceView.Speed.MODE_FAST);
                        break;
                    case R.id.rb_extra_fast: 
                        glSurfaceView.setSpeed(YGLSurfaceView.Speed.MODE_EXTRA_FAST);
                        break;
                }
            }
        });
    }

}
