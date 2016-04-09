#ifndef H_SHADER_RGB_KAY27
# define H_SHADER_RGB_KAY27

# include "config.h"

  class MyShader
  {
    public:
      static GLuint CreateProgram();
      static void LinkProgram(GLuint program);
      static void AttachVertexShader(GLuint program, const char *shaderCode);
      static void AttachFragmentShader(GLuint program, const char *shaderCode);
      static void AttachShader(GLuint program, GLenum shaderType, GLint shader, const char *shaderCode);
  };

  static const GLfloat vertices[] =
  {
    -1, -1, 0,
    -1,  1, 0,
     1, -1, 0,
     1,  1, 0,
  };

  static const char * rgbVertexShader =
    "attribute vec4 vPosition;\n"
    "varying vec2 crds;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vPosition;\n"
    "  crds        = vPosition.xy;\n"
    "}\n"
  ;

  static const char * rgbFragmentShader =
    "precision mediump float;\n"
    "varying vec2 crds;\n"
    "uniform vec2 vCrdR;\n"
    "uniform vec2 vCrdG;\n"
    "uniform vec2 vCrdB;\n"
    "uniform float vMul;\n"
    "void main()\n"
    "{\n"
    "  vec2 m = vec2(vMul, 1.0);\n"
    "  vec2 c = crds * m;\n"
    "  vec2 r = vCrdR * m;\n"
    "  vec2 g = vCrdG * m;\n"
    "  vec2 b = vCrdB * m;\n"
    "  float ir = max(1.0 - distance(c, r), 0.0);\n"
    "  float ig = max(1.0 - distance(c, g), 0.0);\n"
    "  float ib = max(1.0 - distance(c, b), 0.0);\n"
    "  gl_FragColor = vec4(ir, ig, ib, 1.0);\n"
    "}\n"
  ;

#endif // #ifndef H_SHADER_RGB_KAY27
