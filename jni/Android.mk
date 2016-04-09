LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rgb

LOCAL_SRC_FILES := \
  game.cxx \
  shader.cxx \
  jni2game.cxx \

#LOCAL_CPPFLAGS := -std=c++11

LOCAL_LDLIBS := -lGLESv2

include $(BUILD_SHARED_LIBRARY)
