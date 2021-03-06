// *****************************************************************************
// gooch_shading.cpp                                               Tao3D project
// *****************************************************************************
//
// File description:
//
//   Gooch shading implementation.
//
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2011-2013, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2011-2013, Catherine Burvelle <catherine@taodyne.com>
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
#include "gooch_shading.h"

// ============================================================================
//
//   Gooch shading
//
// ============================================================================

bool                  GoochShading::failed = false;
QGLShaderProgram*     GoochShading::pgm = NULL;
std::map<text, GLint> GoochShading::uniforms;
const QGLContext*     GoochShading::context = NULL;


GoochShading::GoochShading()
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Shading(&context)
{
    IFTRACE(shading)
            debug() << "Create gooch shading" << "\n";

    checkGLContext();
}


GoochShading::~GoochShading()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void GoochShading::setCoolColor(GLfloat color[3])
// ----------------------------------------------------------------------------
//   Set cool color
// ----------------------------------------------------------------------------
{
    warm[0] = color[0];
    warm[1] = color[1];
    warm[2] = color[2];
}


void GoochShading::setWarmColor(GLfloat color[3])
// ----------------------------------------------------------------------------
//   Set warm color
// ----------------------------------------------------------------------------
{
    cool[0] = color[0];
    cool[1] = color[1];
    cool[2] = color[2];
}


void GoochShading::setSurfaceColor(GLfloat color[3])
// ----------------------------------------------------------------------------
//   Set surface color
// ----------------------------------------------------------------------------
{
    surface[0] = color[0];
    surface[1] = color[1];
    surface[2] = color[2];
}


void GoochShading::setWarmDiffuse(coord d)
// ----------------------------------------------------------------------------
//   Set warm diffuse coefficient
// ----------------------------------------------------------------------------
{
    wd = d;
}


void GoochShading::setCoolDiffuse(coord d)
// ----------------------------------------------------------------------------
//   Set cool diffuse coefficient
// ----------------------------------------------------------------------------
{
    cd = d;
}


void GoochShading::Draw()
// ----------------------------------------------------------------------------
//   Apply gooch shading
// ----------------------------------------------------------------------------
{
    checkGLContext();

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        IFTRACE(shading)
                debug() << "Apply gooch shading" << "\n";

        // Set shader
        tao->SetShader(prg_id);

        // Set gooch colors
        GL.Uniform3fv(uniforms["warm_color"], 1, warm);
        GL.Uniform3fv(uniforms["cool_color"], 1, cool);
        GL.Uniform3fv(uniforms["surface_color"], 1, surface);

        // Set gooch coeffs
        GL.Uniform(uniforms["warm_diffuse"], wd);
        GL.Uniform(uniforms["cool_diffuse"], cd);

        if(tao->isGLExtensionAvailable("GL_EXT_gpu_shader4"))
        {
            GLint lightsmask =  GL.LightsMask();
            GL.Uniform(uniforms["lights"], lightsmask);
        }
    }
}


void GoochShading::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs
// ----------------------------------------------------------------------------
{
    if(!failed)
    {
        IFTRACE(shading)
                debug() << "Create shader for gooch shading" << "\n";

        delete pgm;

        pgm = new QGLShaderProgram(*pcontext);
        bool ok = false;

        // Basic vertex shader
        static string vSrc =
                "/********************************************************************************\n"
                "**                                                                               \n"
                "** Copyright (C) 2011 Taodyne.                                                   \n"
                "** All rights reserved.                                                          \n"
                "** Contact: Taodyne (contact@taodyne.com)                                        \n"
                "**                                                                               \n"
                "** This file is part of the Tao3D application, developped by Taodyne.\n"
                "** It can be only used in the software and these modules.                        \n"
                "**                                                                               \n"
                "** If you have questions regarding the use of this file, please contact          \n"
                "** Taodyne at contact@taodyne.com.                                               \n"
                "**                                                                               \n"
                "********************************************************************************/\n"
                "varying vec3 normal;"
                "varying vec3 viewDir;"
                "void main()"
                "{"
                "    gl_Position = ftransform();"

                "    /* Get normal and view direction */"
                "    normal  = normalize(gl_NormalMatrix * gl_Normal);"
                "    viewDir = normalize((gl_ModelViewMatrix * gl_Vertex).xyz);"
                "}";

        static string fSrc;
        if(tao->isGLExtensionAvailable("GL_EXT_gpu_shader4"))
        {
            // If the extension is available, use this shader
            // to handle multiple lights
            fSrc =
                    "/********************************************************************************\n"
                    "**                                                                               \n"
                    "** Copyright (C) 2011 Taodyne.                                                   \n"
                    "** All rights reserved.                                                          \n"
                    "** Contact: Taodyne (contact@taodyne.com)                                        \n"
                    "**                                                                               \n"
                    "** This file is part of the Tao3D application, developped by Taodyne.\n"
                    "** It can be only used in the software and these modules.                        \n"
                    "**                                                                               \n"
                    "** If you have questions regarding the use of this file, please contact          \n"
                    "** Taodyne at contact@taodyne.com.                                               \n"
                    "**                                                                               \n"
                    "********************************************************************************/\n"
                    "#extension GL_EXT_gpu_shader4 : require\n"

                    "uniform float warm_diffuse;"
                    "uniform float cool_diffuse;"

                    "uniform vec3 warm_color;"
                    "uniform vec3 cool_color;"
                    "uniform vec3 surface_color;"

                    "uniform int  lights;"

                    "varying vec3 normal;"
                    "varying vec3 viewDir;"
                    "void main()"
                    "{"
                    "   /* Define a maximum of lights supported */"
                    "   int MAX_LIGHTS = 8;"
                    "   float diff = 0.0;"
                    "   float spec = 0.0;"

                    "   if(lights == 0)"
                    "   {"
                    "       vec3 lightDir   = normalize(gl_LightSource[0].position.xyz - viewDir);"
                    "       vec3 reflectVec = normalize(reflect( -lightDir, normal ));"

                    "       /* Diffuse intensity */"
                    "       diff = max(dot(normal,lightDir), 0.0);"

                    "       /* Specular intensity */"
                    "       if (diff > 0.0)"
                    "       {"
                    "          spec = max(dot(reflectVec, -viewDir), 0.0);"
                    "          spec = pow(spec, 32.0);"
                    "       }"
                    "   }"
                    "   else"
                    "   {"
                    "       for(int i = 0; i < MAX_LIGHTS; i++)"
                    "       {"
                    "           if(bool(lights & (1 << i)))"
                    "           {"
                    "               vec3 lightDir   = normalize(gl_LightSource[i].position.xyz - viewDir);"
                    "               vec3 reflectVec = normalize(reflect( -lightDir, normal ));"

                    "               /* Diffuse intensity */"
                    "               float diffTmp = max(dot(normal,lightDir), 0.0);"

                    "               /* Specular intensity */"
                    "               if (diffTmp > 0.0)"
                    "               {"
                    "                  float specTmp = max(dot(reflectVec, -viewDir), 0.0);"
                    "                  spec += pow(specTmp, 32.0);"
                    "               }"

                    "               diff += diffTmp;"
                    "           }"
                    "       }"
                    "   }"

                    "   /* Mix colors */"
                    "   vec3 kcool  = min(cool_color + cool_diffuse * surface_color, 1.0);"
                    "   vec3 kwarm  = min(warm_color + warm_diffuse * surface_color, 1.0);"
                    "   vec3 kfinal = mix(kwarm, kcool, diff);"

                    "   /* Compute final color */"
                    "   gl_FragColor = vec4(min(kfinal + spec, 1.0), 1.0);"
                    "}";
        }
        else
        {
            // If the extension is not available, use this shader
            // to handle an unique light
            fSrc =
                    "uniform float warm_diffuse;"
                    "uniform float cool_diffuse;"

                    "uniform vec3 warm_color;"
                    "uniform vec3 cool_color;"
                    "uniform vec3 surface_color;"

                    "varying vec3 normal;"
                    "varying vec3 viewDir;"
                    "void main()"
                    "{"
                    "   float diff = 0.0;"
                    "   float spec = 0.0;"

                    "   vec3 lightDir   = normalize(gl_LightSource[0].position.xyz - viewDir);"
                    "   vec3 reflectVec = normalize(reflect( -lightDir, normal ));"

                    "   /* Diffuse intensity */"
                    "   diff = max(dot(normal,lightDir), 0.0);"

                    "   /* Specular intensity */"
                    "   if (diff > 0.0)"
                    "   {"
                    "      spec = max(dot(reflectVec, -viewDir), 0.0);"
                    "      spec = pow(spec, 32.0);"
                    "   }"

                    "   /* Mix colors */"
                    "   vec3 kcool  = min(cool_color + cool_diffuse * surface_color, 1.0);"
                    "   vec3 kwarm  = min(warm_color + warm_diffuse * surface_color, 1.0);"
                    "   vec3 kfinal = mix(kwarm, kcool, diff);"

                    "   /* Compute final color */"
                    "   gl_FragColor = vec4(min(kfinal + spec, 1.0), 1.0);"
                    "}";
        }

        if (pgm->addShaderFromSourceCode(QGLShader::Vertex, vSrc.c_str()))
        {
            if (pgm->addShaderFromSourceCode(QGLShader::Fragment, fSrc.c_str()))
            {
                ok = true;
            }
            else
            {
                std::cerr << "Error loading fragment shader code: " << "\n";
                std::cerr << pgm->log().toStdString();
            }
        }
        else
        {
            std::cerr << "Error loading vertex shader code: " << "\n";
            std::cerr << pgm->log().toStdString();
        }
        if (!ok)
        {
            delete pgm;
            pgm = NULL;
            failed = true;
        }
        else
        {
            pgm->link();

            // Save uniform locations
            uint id = pgm->programId();
            uniforms["warm_color"] = GL.GetUniformLocation(id, "warm_color");
            uniforms["cool_color"] = GL.GetUniformLocation(id, "cool_color");
            uniforms["surface_color"]=GL.GetUniformLocation(id,"surface_color");
            uniforms["warm_diffuse"] = GL.GetUniformLocation(id,"warm_diffuse");
            uniforms["cool_diffuse"] = GL.GetUniformLocation(id,"cool_diffuse");
            uniforms["lights"] = GL.GetUniformLocation(id, "lights");
        }
    }
}
