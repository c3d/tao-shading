#ifndef GOOCH_SHADING_H
#define GOOCH_SHADING_H
// ****************************************************************************
//  gooch_shading.h                                                 Tao project
// ****************************************************************************
//
//   File Description:
//
//      Define gooch shading.
//
//
//
//
//
// ****************************************************************************
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriÃ©tÃ© de Taodyne SAS - Confidentiel
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "tao/coords3d.h"
#include "tao/module_api.h"
#include "tao/tao_gl.h"
#include "cel_shading.h"

using namespace std;
using namespace Tao;

struct GoochShading : public Shading
{
    GoochShading();
    ~GoochShading();

    void setWarmColor(GLfloat color[3]);
    void setCoolColor(GLfloat color[3]);
    void setSurfaceColor(GLfloat color[3]);

    void setWarmDiffuse(coord d);
    void setCoolDiffuse(coord d);

    // Draw gooch shading
    virtual void    Draw();

    static void     render_callback(void *arg);
    static void     identify_callback(void *arg);
    static void     delete_callback(void *arg);

private:
   // Gooch shading color
   GLfloat warm[3];
   GLfloat cool[3]; //
   GLfloat surface[3];

   // Gooch shading coeffs
   GLfloat wd;
   GLfloat cd;

   static bool failed;
   static QGLShaderProgram* pgm;
   static std::map<text, GLint> uniforms;
};


#endif
