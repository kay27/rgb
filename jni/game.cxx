#include "game.h"

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

  glUniform2f(vCrdR, -0.5,  0.5);
  glUniform2f(vCrdG,  0.5,  0.5);
  glUniform2f(vCrdB,  0.0, -0.5);
}

void Resize(int w, int h)
{
  glViewport(0, 0, w, h);
  if(h>0)
  {
    xMulValue = float(w)/h;
    glUseProgram(rgbProgram);
    glUniform1f(vMul, xMulValue);
  }
}

void Render()
{
  glUseProgram(rgbProgram);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}