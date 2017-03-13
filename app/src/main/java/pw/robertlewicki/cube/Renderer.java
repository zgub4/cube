package pw.robertlewicki.cube;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class Renderer implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("engine");
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        init(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        draw();
    }

    public native void init(int width, int height);
    public native void draw();
}
