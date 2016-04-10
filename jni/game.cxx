#include "game.h"
#include "jni2game.h"

inline float Rand()
{
  return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

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
//  vR        = glGetUniformLocation(rgbProgram, "vR");

  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 3*sizeof(GLfloat), (void*)0);

//  rr = rg = rb = 1.0;

  rc=false; gc=false; bc=false;
  ri =-1; gi=-1; bi = -1;

//  rx=-0.5; ry=0.5;
//  gx= 0.5; gy=0.5;
//  bx= 0.0; by=-0.5;

  struct timeval now;
  gettimeofday(&now, NULL);
  srand(now.tv_usec);
  rx=rand()*2-1; ry=rand()*2-1;
  gx=rand()*2-1; gy=rand()*2-1;
  bx=rand()*2-1; by=rand()*2-1;
  rvx=Rand()-0.5;
  rvy=Rand()-0.5;
  gvx=Rand()-0.5;
  gvy=Rand()-0.5;
  bvx=Rand()-0.5;
  bvy=Rand()-0.5;

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
  }
}

void fun1(float &rx, float &ry, float &rvx, float &rvy, const float delta, const float gx, const float mul1x, const float gy, const float mul1y, const float bx, const float mul2x, const float by, const float mul2y)
{
  rx += rvx;
  rvx+=(gx-rx)*delta/mul1x + (bx-rx)*delta/mul2x; 
  if(rx>1){rx=0.9999999; rvx=0;} if(rx<-1){rx=-0.9999999;rvx=0;}
  ry += rvy;
  rvy+=(gy-ry)*delta/mul1y + (by-ry)*delta/mul2y; 
//  if(((ry>1)&&(rvy>0)) || ((ry<-1)&&(rvy<0))) rvy=-rvy;
  if(ry>1){ry=0.9999999; rvy=0;} if(ry<-1){ry=-0.9999999;rvy=0;}
}

void Render()
{
  if(!started) return;

  struct timeval now;
  gettimeofday(&now, NULL);
  float delta = (now.tv_sec - lastTime.tv_sec) * 1000000 + ((int)now.tv_usec - (int)lastTime.tv_usec);
  lastTime = now;
  if(delta>50000) return;
//    if(!rc) fun1(rx, ry, rvx, rvy, delta, gx, 125000000, gy, 125000000, bx, 150000000, by, 150000000); else {rvx=0; rvy=0;}
//    if(!gc) fun1(gx, gy, gvx, gvy, delta, rx, 100000000, ry, 100000000, bx, 150000000, by, 150000000); else {gvx=0; gvy=0;}
//    if(!bc) fun1(bx, by, bvx, bvy, delta, rx, 100000000, ry, 100000000, gx, 125000000, gy, 125000000); else {bvx=0; bvy=0;}
  if(!rc) fun1(rx, ry, rvx, rvy, delta/1000000, gx, 33000, gy, 33000, bx, 33000, by, 33000); else {rvx=0; rvy=0;}
  if(!gc) fun1(gx, gy, gvx, gvy, delta/1000000, rx, 33000, ry, 33000, bx, 33000, by, 33000); else {gvx=0; gvy=0;}
  if(!bc) fun1(bx, by, bvx, bvy, delta/1000000, rx, 33000, ry, 33000, gx, 33000, gy, 33000); else {bvx=0; bvy=0;}

  glUniform2f(vCrdR, rx, ry);
  glUniform2f(vCrdG, gx, gy);
  glUniform2f(vCrdB, bx, by);
//  glUniform2f(vR, rr, rg, rb, 0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Drag(int n, float x, float y)
{
    if(!started) return;
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
    else if((!bc) && ((bd<=rd)||rc) && ((bd<=gd)||gc)) { bc=true; bi=n; bdx=0; bx=x; bdy=0; by=y; }
    else if((!gc) && ((gd<=rd)||rc) && ((gd<=bd)||bc)) { gc=true; gi=n; gdx=0; gx=x; gdy=0; gy=y; }

}

void Drop(int n, float x, float y)
{
         if(rc && ri==n) {rc=false; ri=-1;}
    else if(gc && gi==n) {gc=false; gi=-1;}
    else if(bc && bi==n) {bc=false; bi=-1;}
}

void Move(int n, float x, float y)
{
         if(rc && ri==n) MoveR(x+rdx, y+rdy);
    else if(gc && gi==n) MoveG(x+gdx, y+gdy);
    else if(bc && bi==n) MoveB(x+bdx, y+bdy);
}
