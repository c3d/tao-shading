#ifndef GOOCH_SHADING_H
#define GOOCH_SHADING_H
// *****************************************************************************
// gooch_shading.h                                                 Tao3D project
// *****************************************************************************
//
// File description:
//
//      Define gooch shading.
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2011-2013, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2011-2012, Catherine Burvelle <catherine@taodyne.com>
// (C) 2011-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// (C) 2011-2013, Jérôme Forissier <jerome@taodyne.com>
// (C) 2011-2013, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// *****************************************************************************
// This file is part of Tao3D
//
// Tao3D is free software: you can r redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tao3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tao3D, in a file named COPYING.
// If not, see <https://www.gnu.org/licenses/>.
// *****************************************************************************

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
