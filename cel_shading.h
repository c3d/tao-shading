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
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "tao/coords3d.h"
#include "tao/matrix.h"
#include "shading.h"
#include <QObject>

using namespace std;
using namespace Tao;


struct CelShading : public Shading
{
    CelShading();
    ~CelShading();

    void setCelColor(GLfloat color[3]);

    // Draw cel shading
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    GLfloat cel[3];

    static bool failed;
    static QGLShaderProgram* pgm;
    static std::map<text, GLint> uniforms;
    static const QGLContext* context;
};


#endif // CEL_SHADING_H
