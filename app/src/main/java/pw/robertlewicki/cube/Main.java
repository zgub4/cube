package pw.robertlewicki.cube;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class Main extends Activity {

    private GLSurfaceView surface;
    private Renderer renderer;
    private float factor = 1.0f;
    private float currentDistance = 0.0f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        renderer = new Renderer();
        renderer.setAssetManager(getAssets());

        surface = new GLSurfaceView(this);
        surface.setEGLContextClientVersion(2);
        surface.setRenderer(renderer);
        surface.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getPointerCount() == 2) {
                    Point first = new Point(event.getX(0), event.getY(0));
                    Point second = new Point(event.getX(1), event.getY(1));
                    processPinch(first, second);
                } else if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    renderer.startTouch(event.getX(), event.getY());
                    currentDistance = 0.0f;
                } else if(event.getAction() == MotionEvent.ACTION_MOVE) {
                    renderer.processTouch(event.getX(), event.getY());
                }
                return true;
            }
        });
        setContentView(surface);
    }

    @Override
    protected void onPause() {
        super.onPause();
        surface.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        surface.onResume();
    }

    private void processPinch(Point first, Point second) {
        if(currentDistance <= 0.01f) {
            currentDistance = distance(first, second);
        } else {
            float current = distance(first, second);
            if(Math.abs(currentDistance - current) > 15.0f) {
                if(current < currentDistance) {
                    renderer.pinch(-0.05f);
                } else {
                    renderer.pinch(0.05f);
                }
                currentDistance = current;
            }
        }
    }

    private float distance(Point first, Point second) {
        return ((float) Math.sqrt(Math.pow(first.x - second.x, 2) + Math.pow(first.y - second.y, 2)));
    }

    private class Point {
        Point(float x, float y) { this.x = x; this.y = y; }
        private float x;
        private float y;
    }
}
