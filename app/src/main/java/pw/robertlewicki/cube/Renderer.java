package pw.robertlewicki.cube;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;

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
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        draw();
    }

    public native void init(int width, int height, AssetManager assetManager);
    public native void draw();
}
