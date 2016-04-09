#ifndef H_JNI2GAME_RGB_KAY27
# define H_JNI2GAME_RGB_KAY27

# include <jni.h>
# include "game.h"

  static JavaVM *jvm       = NULL;
  static JNIEnv *jnienv    = NULL;
  static jobject jo        = NULL;

  class MyCallback
  {
    public:
      static void Toast(const char *message) { Call("ToastCallback", message); }
      static void Quit(const char *message) { Call("ErrorCallback", message); }

    protected:
      static void Call(const char *javaStaticMethod, const char *message);
      static void Call(const char *javaStaticMethod, const int n);
      static int Call(const char *javaStaticMethod);
  };


#endif // #ifndef H_JNI2GAME_RGB_KAY27
