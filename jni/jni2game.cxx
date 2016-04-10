#include <cmath>
#include "jni2game.h"

void MyCallback::Call(const char *javaStaticMethod, const char *message)
{
  if(jo && jnienv)
    if(jclass c = jnienv->FindClass(ACTIVITY_NAME))
      if(jmethodID m = jnienv->GetStaticMethodID(c, javaStaticMethod, "(Ljava/lang/String;)V"))
        jnienv->CallStaticVoidMethod(c, m, jnienv->NewStringUTF(message));
}

void MyCallback::Call(const char *javaStaticMethod, const int n)
{
  if(jo && jnienv)
    if(jclass c = jnienv->FindClass(ACTIVITY_NAME))
      if(jmethodID m = jnienv->GetStaticMethodID(c, javaStaticMethod, "(I)V"))
        jnienv->CallStaticVoidMethod(c, m, n);
}

int MyCallback::Call(const char *javaStaticMethod)
{
  if(jo && jnienv)
    if(jclass c = jnienv->FindClass(ACTIVITY_NAME))
      if(jmethodID m = jnienv->GetStaticMethodID(c, javaStaticMethod, "()I"))
        return jnienv->CallStaticIntMethod(c, m);
  return -1;
}

extern "C"
{
  JNIEXPORT void Java_com_kay27_RGB_MyGLSurfaceView_nativeDrag(JNIEnv* env, jobject thiz, jint n, jfloat x, jfloat y)
  {
    float rd=pow(rx-x,2)+pow(ry-y,2);
    float gd=pow(gx-x,2)+pow(gy-y,2);
    float bd=pow(bx-x,2)+pow(by-y,2);
         if((!rc) && ((rd<=gd)||gc) && ((rd<=bd)||bc)) { rc=true; ri=n; rdx=rx-x; rdy=ry-y; }
    else if((!gc) && ((gd<=rd)||rc) && ((gd<=bd)||bc)) { gc=true; gi=n; gdx=gx-x; gdy=gy-y; }
    else if((!bc) && ((bd<=rd)||rc) && ((bd<=gd)||gc)) { bc=true; bi=n; bdx=bx-x; bdy=by-y; }
  }

  JNIEXPORT void Java_com_kay27_RGB_MyGLSurfaceView_nativeMove(JNIEnv* env, jobject thiz, jint n, jfloat x, jfloat y)
  {
         if(ri==n) MoveR(x+rdx, y+rdy);
    else if(gi==n) MoveG(x+gdx, y+gdy);
    else if(bi==n) MoveB(x+bdx, y+bdy);
  }

  JNIEXPORT void Java_com_kay27_RGB_MyGLSurfaceView_nativeDrop(JNIEnv* env, jobject thiz, jint n, jfloat x, jfloat y)
  {
         if(ri==n) {rc=false; ri=-1;}
    else if(gi==n) {gc=false; gi=-1;}
    else if(bi==n) {bc=false; bi=-1;}
  }

  JNIEXPORT void Java_com_kay27_RGB_MyRenderer_nativeInit(JNIEnv* env, jobject obj)
  {
    jo = obj;
    jnienv = env;
    Init();
  }

  JNIEXPORT void Java_com_kay27_RGB_MyRenderer_nativeResize(JNIEnv* env, jobject thiz, jint w, jint h)
  {
    Resize(w, h);
  }

  JNIEXPORT void Java_com_kay27_RGB_MyRenderer_nativeRender(JNIEnv* env)
  {
    Render();
  }

} // extern "C"
