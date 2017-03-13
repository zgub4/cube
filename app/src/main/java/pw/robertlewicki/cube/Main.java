package pw.robertlewicki.cube;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class Main extends Activity {

    private GLSurfaceView surface;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        surface = new GLSurfaceView(this);
        surface.setEGLContextClientVersion(2);
        surface.setRenderer(new Renderer(getResources().getAssets()));
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
}
