package com.tck.HelloOpenGL.filter;


import android.content.Context;

import com.tck.HelloOpenGL.R;

/**
 * <p>description:负责往屏幕上渲染</p>
 * <p>created on: 2019/6/12 8:09</p>
 *
 * @author tck
 * @version 3.5.2
 */
public class ScreenFilter extends AbstractFilter{


    public ScreenFilter(Context context) {
        super(context, R.raw.base_vertex,R.raw.base_frag);
    }
}
