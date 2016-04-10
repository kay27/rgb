package com.kay27.RGB;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.Configuration;
import android.opengl.GLSurfaceView;
import android.graphics.Point;
import android.os.Bundle;
//import android.util.DisplayMetrics;
import android.view.Display;
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
      Display display = getWindowManager().getDefaultDisplay();
      Point size = new Point();
      display.getSize(size);
      mGLView = new MyGLSurfaceView(this, size.x, size.y);
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
  public MyGLSurfaceView(Context context, int w, int h)
  {
    super(context);

    halfH=w/2; halfW=h/2;

    setEGLContextClientVersion(2);
    mRenderer = new MyRenderer();
    setRenderer(mRenderer);
  }

  public boolean onTouchEvent(final MotionEvent ev)
  {
    int action = ev.getActionMasked();
    if(action == MotionEvent.ACTION_MOVE)
      for (int i = 0; i < ev.getPointerCount(); i++)
        nativeMove(ev.getPointerId(i), ev.getX(i)/halfH-1, 1-ev.getY(i)/halfW);
//      {
//        int id=ev.getPointerId(i);
//        nativeMove(id, ev.getX(id)/halfH-1, 1-ev.getY(id)/halfW);
//      }
    else if(action == MotionEvent.ACTION_DOWN)
      nativeDrag(ev.getPointerId(ev.getActionIndex()), ev.getX()/halfH-1, 1-ev.getY()/halfW);
//      nativeDrag(ev.getPointerId(0), ev.getX(0)/halfH-1, 1-ev.getY(0)/halfW);
//      nativeDrag(ev.getPointerId(0), ev.getRawX()/halfH-1, 1-ev.getRawY()/halfW);
//      nativeDrag(ev.getPointerId(0), ev.getX(0)/halfH-1, 1-ev.getY(0)/halfW);
    else if(action == MotionEvent.ACTION_POINTER_DOWN)
      nativeDrag(ev.getPointerId(ev.getActionIndex()), ev.getX(ev.getActionIndex())/halfH-1, 1-ev.getY(ev.getActionIndex())/halfW);
//      nativeDrag(ev.getPointerId(ev.getActionIndex()), ev.getX()/halfH-1, 1-ev.getY()/halfW);
    else if(action == MotionEvent.ACTION_UP)
      nativeDrop(ev.getPointerId(ev.getActionIndex()), ev.getX()/halfH-1, 1-ev.getY()/halfW);
//      nativeDrop(ev.getPointerId(0), ev.getX(0)/halfH-1, 1-ev.getY(0)/halfW);
//      nativeDrop(ev.getPointerId(0), ev.getRawX()/halfH-1, 1-ev.getRawY()/halfW);
//      nativeDrop(ev.getPointerId(0), ev.getX(0)/halfH-1, 1-ev.getY(0)/halfW);
    else if(action == MotionEvent.ACTION_POINTER_UP)
      nativeDrop(ev.getPointerId(ev.getActionIndex()), ev.getX(ev.getActionIndex())/halfH-1, 1-ev.getY()/halfW);
//      nativeDrop(ev.getPointerId(ev.getActionIndex()), ev.getX()/halfH-1, 1-ev.getY()/halfW);
//    else if(action == MotionEvent.ACTION_POINTER_DOWN)
//      for (int i = 0; i < ev.getPointerCount(); i++)
//        nativeDrag(ev.getPointerId(i), ev.getX(i)/halfH-1, 1-ev.getY(i)/halfW);
//    else if(action == MotionEvent.ACTION_POINTER_UP)
//      for (int i = 0; i < ev.getPointerCount(); i++)
//        nativeDrop(ev.getPointerId(i), ev.getX(i)/halfH-1, 1-ev.getY(i)/halfW);
    return true;
  }

  private MyRenderer mRenderer;
  private int id0=-1, id1=-1, id2=-1;
  private float halfW, halfH;

  private static native void nativeDrag(int count, float x, float y);
  private static native void nativeMove(int count, float x, float y);
  private static native void nativeDrop(int count, float x, float y);

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
