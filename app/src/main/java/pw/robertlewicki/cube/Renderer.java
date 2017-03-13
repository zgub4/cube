package pw.robertlewicki.cube;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;

import java.io.IOException;
import java.io.InputStream;
import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class Renderer implements GLSurfaceView.Renderer {

    private AssetManager assetManager;

    static {
        System.loadLibrary("engine");
    }

    Renderer(AssetManager assetManager) {
        this.assetManager = assetManager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        init(width, height, assetManager);
        InputStream is = null;
        try {
            is = assetManager.open("bricks.jpg");
        } catch(IOException e) {
            e.printStackTrace();
        }
        final Bitmap bitmap = BitmapFactory.decodeStream(is);
        int w = bitmap.getWidth();
        int h = bitmap.getHeight();
        int size = bitmap.getRowBytes() * h;
        ByteBuffer buffer = ByteBuffer.allocate(size);
        bitmap.copyPixelsToBuffer(buffer);

        byte[] bytes = new byte[size];
        try {
            buffer.get(bytes, 0, bytes.length);
        } catch(BufferUnderflowException e) {
            e.printStackTrace();
        }
        createTexture(w, h, bytes);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        draw();
    }

    public native void init(int width, int height, AssetManager assetManager);
    public native void draw();
    public native void createTexture(int width, int height, byte[] bytes);
}
