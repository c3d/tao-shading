#ifndef CEL_SHADING_H
#define CEL_SHADING_H
// ****************************************************************************
//  cel_shading.h                                                   Tao project
// ****************************************************************************
//
//   File Description:
//
//      Define cel shading.
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
#include <QObject>

using namespace std;
using namespace Tao;

struct Shading : public QObject
{
public :
    static bool tested, licensed;
    static const Tao::ModuleApi *tao;
};


struct CelShading : public Shading
{
    CelShading();
    ~CelShading();

    void setCelColor(GLfloat color[3]);

    // Draw cel shading
    virtual void    Draw();

    static void     render_callback(void *arg);
    static void     identify_callback(void *arg);
    static void     delete_callback(void *arg);

private:
   GLfloat cel[3];

   static bool failed;
   static QGLShaderProgram* pgm;
   static std::map<text, GLint> uniforms;
};


#endif
