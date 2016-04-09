#ifndef H_GAME_RGB_KAY27
# define H_GAME_RGB_KAY27

# include "config.h"
# include "shader.h"

  static GLuint vb;
  static GLint rgbProgram, vMul, vCrdR, vCrdG, vCrdB, vPosition;
  static GLfloat xMulValue;

  void Init();

  void Resize(int w, int h);

  void Render();

#endif // #ifndef H_GAME_RGB_KAY27
