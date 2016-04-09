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
  JNIEXPORT void Java_com_kay27_RGB_MyGLSurfaceView_nativeKeyPress(JNIEnv* env)
  {
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
