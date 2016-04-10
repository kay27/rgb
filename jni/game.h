#ifndef H_GAME_RGB_KAY27
# define H_GAME_RGB_KAY27

# include "config.h"
# include "shader.h"

  static int started = 0;

  static GLuint vb;
  static GLint rgbProgram, vMul, vCrdR, vCrdG, vCrdB, vPosition;
  static GLfloat xMulValue = 1;
  static GLfloat rx, ry, gx, gy, bx, by;
  static bool rc, gc, bc;
  static int ri, gi, bi;
  static float rdx, gdx, bdx, rdy, gdy, bdy;

  void Init();

  void Resize(int w, int h);

  void MoveR(float x, float y);
  void MoveG(float x, float y);
  void MoveB(float x, float y);

  void Render();

#endif // #ifndef H_GAME_RGB_KAY27
