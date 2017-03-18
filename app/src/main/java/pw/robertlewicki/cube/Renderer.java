package pw.robertlewicki.cube;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.Scanner;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class Renderer implements GLSurfaceView.Renderer {

    private AssetManager assetManager;

    static {
        System.loadLibrary("engine");
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        String vertex = loadShaderFile("vertex.vert");
        String fragment = loadShaderFile("fragment.frag");
        init(vertex, fragment);
        loadTexture();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        resetAspectRatio(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        draw();
    }

    void setAssetManager(AssetManager assetManager) {
        this.assetManager = assetManager;
    }

    private String loadShaderFile(String path) {
        try {
            InputStream inputStream = assetManager.open(path);
            Scanner scanner = new Scanner(inputStream).useDelimiter("\\A");
            return scanner.hasNext() ? scanner.next() : "";
        } catch(IOException e) {
            e.printStackTrace();
        }
        return "";
    }

    private void loadTexture() {
        try {
            InputStream inputStream = assetManager.open("map_02.png");
            Bitmap bitmap = BitmapFactory.decodeStream(inputStream);
            int width = bitmap.getWidth();
            int height = bitmap.getHeight();
            ByteBuffer buffer = ByteBuffer.allocateDirect(width * height * 4);
            bitmap.copyPixelsToBuffer(buffer);
            buffer.position(0);
            createTexture(width, height, buffer.array());
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    public native void init(String vertexSource, String fragmentSource);
    public native void resetAspectRatio(int width, int height);
    public native void draw();
    public native void startTouch(float x, float y);
    public native void processTouch(float x, float y);
    public native void createTexture(int width, int height, byte[] pixels);
    public native void pinch(float scale);
}
