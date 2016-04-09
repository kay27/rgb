package com.kay27.RGB;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.Configuration;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
//import android.util.Log;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

public class MainActivity extends Activity
{
  private static Activity activity;

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    activity = this;
    ActivityManager am = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
    ConfigurationInfo info = am.getDeviceConfigurationInfo();
    boolean supportES2 = (info.reqGlEsVersion >= 0x20000);
    if(supportES2)
    {
      requestWindowFeature(Window.FEATURE_NO_TITLE);
      getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
      mGLView = new MyGLSurfaceView(this);
      setContentView(mGLView);
    }
    else
      Toast.makeText(this, "Your device doesn't support OpenGL ES 2.0. (" + info.reqGlEsVersion + ")", Toast.LENGTH_LONG).show();
  }

  @Override
  public void onConfigurationChanged(Configuration newConfig)
  {
    super.onConfigurationChanged(newConfig);
    getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
  }

  public static void ErrorCallback(final String message)
  {
    activity.runOnUiThread(new Runnable() {
      public void run(){ Toast.makeText(activity, message, Toast.LENGTH_LONG).show(); } } );
    activity.finish();
  }

  public static void ToastCallback(final String message)
  {
    activity.runOnUiThread(new Runnable() {
      public void run(){ Toast.makeText(activity, message, Toast.LENGTH_SHORT).show(); } } );
  }

  private MyGLSurfaceView mGLView;

  static { System.loadLibrary("rgb"); }

}

class MyGLSurfaceView extends GLSurfaceView
{
  public MyGLSurfaceView(Context context)
  {
    super(context);
    setEGLContextClientVersion(2);
    mRenderer = new MyRenderer();
//    setPreserveEGLContextOnPause(true); //???fix
    setRenderer(mRenderer);
//    requestRender(); //temp
  }

  public boolean onTouchEvent(final MotionEvent ev)
  {
    int action = ev.getAction();
    if(action == MotionEvent.ACTION_MOVE)
    {
      int count = ev.getPointerCount();
    }
    return true;
  }

  private MyRenderer mRenderer;

  private static native void nativeKeyPress();

}

class MyRenderer implements GLSurfaceView.Renderer
{
  public void onSurfaceCreated(GL10 gl, EGLConfig config) { nativeInit(); }
  public void onSurfaceChanged(GL10 gl, int w, int h) { nativeResize(w, h); }
  public void onDrawFrame(GL10 gl) { nativeRender(); }

  private static native void nativeInit();
  private static native void nativeResize(int w, int h);
  private static native void nativeRender();
}
