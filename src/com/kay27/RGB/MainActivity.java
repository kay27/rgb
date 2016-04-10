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
//    setPreserveEGLContextOnPause(true); //???fix
    setRenderer(mRenderer);
//    requestRender(); //temp
  }

  public boolean onTouchEvent(final MotionEvent ev)
  {
    int action = ev.getAction();
    if((action & MotionEvent.ACTION_MASK) == MotionEvent.ACTION_MOVE)
    {
      int count = ev.getPointerCount();
      for (int i = 0; i < count; i++)
      {
        float x=ev.getX(i)/halfH-1, y=1-ev.getY(i)/halfW;
        nativeMove(ev.getPointerId(i), x, y);
      }
    }
    else
    {
      int id = ev.getPointerId(ev.getActionIndex());
      float x=ev.getRawX()/halfH-1, y=1-ev.getRawY()/halfW;
    switch (action & MotionEvent.ACTION_MASK)
    {
      case MotionEvent.ACTION_DOWN: //nativeDrag(0,x,y); id0=id; break;
      case MotionEvent.ACTION_POINTER_DOWN:
        nativeDrag(id, x, y);
//        if(id1==-1) { nativeDrag(1,x,y); id1=id; }
//        else if(id2==-1) { nativeDrag(2,x,y); id2=id; }
        break;
      case MotionEvent.ACTION_UP: //nativeDrop(0, x, y); id0=-1; break;

      case MotionEvent.ACTION_POINTER_UP:
        nativeDrop(id, x, y);
//        if(id==id1) { nativeDrop(1, x, y); id1=-1; }
//        else if(id==id2) { nativeDrop(2, x, y); id2=-1; }
        break;

      case MotionEvent.ACTION_MOVE:
        nativeMove(id, x, y);
//        if(id==id0) nativeMove(0, x, y);
//        else if(id == id1) nativeMove(1, x, y);
//        else if(id == id2) nativeMove(2, x, y);
        break;
}
    }
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
