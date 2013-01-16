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
// Ce logiciel est la propriété de Taodyne SAS - Confidentiel
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "tao/coords3d.h"
#include "tao/matrix.h"
#include "shading.h"
#include <QObject>

using namespace std;
using namespace Tao;


struct GoochShading  : public Shading
{
    GoochShading ();
    ~GoochShading ();

    void setWarmColor(GLfloat color[3]);
    void setCoolColor(GLfloat color[3]);
    void setSurfaceColor(GLfloat color[3]);

    void setWarmDiffuse(coord d);
    void setCoolDiffuse(coord d);

    // Draw gooch shading
    virtual void    Draw();

protected:
    virtual void    createShaders();

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
    static const QGLContext* context;
};


#endif // GOOCH_SHADING_H
