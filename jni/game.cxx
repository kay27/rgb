#include "game.h"
#include "jni2game.h"

void Init()
{
  glGenBuffers(1, &vb);
  glBindBuffer(GL_ARRAY_BUFFER, vb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

  rgbProgram = MyShader::CreateProgram();
  MyShader::AttachVertexShader(rgbProgram, rgbVertexShader);
  MyShader::AttachFragmentShader(rgbProgram, rgbFragmentShader);
  MyShader::LinkProgram(rgbProgram);

  glUseProgram(rgbProgram);

  vPosition = glGetAttribLocation(rgbProgram, "vPosition");
  vMul      = glGetUniformLocation(rgbProgram, "vMul");
  vCrdR     = glGetUniformLocation(rgbProgram, "vCrdR");
  vCrdG     = glGetUniformLocation(rgbProgram, "vCrdG");
  vCrdB     = glGetUniformLocation(rgbProgram, "vCrdB");

  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 3*sizeof(GLfloat), (void*)0);

  rx=-0.5; ry=0.5;
  gx=-0.5; gy=0.5;
  bx= 0.0; by=-0.5;

  rc = gc = bc = false;
  ri = gi = bi = -1;

  started = 1;
}

void MoveR(float x, float y){ rx=x; ry=y; }
void MoveG(float x, float y){ gx=x; gy=y; }
void MoveB(float x, float y){ bx=x; by=y; }

void Resize(int w, int h)
{
  glViewport(0, 0, w, h);
  if(h>0)
  {
    xMulValue = float(w)/h;
    glUseProgram(rgbProgram);
    glUniform1f(vMul, xMulValue);
//    glUseProgram(0);
  }
}

void Render()
{
  if(!started) return;

//  glClearColor(0.0, 0.0, 0.0, 1.0); //?????
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //????

//  glUseProgram(rgbProgram);
  glUniform2f(vCrdR, rx, ry);
  glUniform2f(vCrdG, gx, gy);
  glUniform2f(vCrdB, bx, by);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//  glUseProgram(0);
}
