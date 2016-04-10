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
//    if(!started) return;
//    float rd=sqrt(pow((rx-x)*xMulValue,2)+pow(ry-y,2));
//    float gd=sqrt(pow((gx-x)*xMulValue,2)+pow(gy-y,2));
//    float bd=sqrt(pow((bx-x)*xMulValue,2)+pow(by-y,2));

//         if((!rc) && ((rd<=gd)||gc) && ((rd<=bd)||bc)) { rc=true; ri=n; rdx=rx-x; rdy=ry-y; }
//    else if((!bc) && ((bd<=rd)||rc) && ((bd<=gd)||gc)) { bc=true; bi=n; bdx=bx-x; bdy=by-y; }
//    else if((!gc) && ((gd<=rd)||rc) && ((gd<=bd)||bc)) { gc=true; gi=n; gdx=gx-x; gdy=gy-y; }


    float ddd=(rx-x)*xMulValue, qqq=ry-y; float rd=sqrt(ddd*ddd+qqq*qqq);
          ddd=(gx-x)*xMulValue, qqq=gy-y; float gd=sqrt(ddd*ddd+qqq*qqq);
          ddd=(bx-x)*xMulValue, qqq=by-y; float bd=sqrt(ddd*ddd+qqq*qqq);

         if((!rc) && ((rd<=gd)||gc) && ((rd<=bd)||bc)) { rc=true; ri=n; rdx=0; rx=x; rdy=0; ry=y; }
    else if((!bc) && ((bd<=rd)||rc) && ((bd<=gd)||gc)) { bc=true; bi=n; gdx=0; gx=x; gdy=0; gy=y; }
    else if((!gc) && ((gd<=rd)||rc) && ((gd<=bd)||bc)) { gc=true; gi=n; bdx=0; bx=x; bdy=0; by=y; }
  }

  JNIEXPORT void Java_com_kay27_RGB_MyGLSurfaceView_nativeMove(JNIEnv* env, jobject thiz, jint n, jfloat x, jfloat y)
  {
         if(rc && ri==n) MoveR(x+rdx, y+rdy);
    else if(gc && gi==n) MoveG(x+gdx, y+gdy);
    else if(bc && bi==n) MoveB(x+bdx, y+bdy);
  }

  JNIEXPORT void Java_com_kay27_RGB_MyGLSurfaceView_nativeDrop(JNIEnv* env, jobject thiz, jint n, jfloat x, jfloat y)
  {
         if(rc && ri==n) {rc=false; ri=-1;}
    else if(gc && gi==n) {gc=false; gi=-1;}
    else if(bc && bi==n) {bc=false; bi=-1;}
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
