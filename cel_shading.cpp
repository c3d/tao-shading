// ****************************************************************************
//  cel_shading.cpp                                                 Tao project
// ****************************************************************************
//
//   File Description:
//
//   Cel shading implementation.
//
//
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
#include "cel_shading.h"

// ============================================================================
//
//   Cel shading
//
// ============================================================================

bool                  CelShading::failed = false;
QGLShaderProgram*     CelShading::pgm = NULL;
std::map<text, GLint> CelShading::uniforms;
const QGLContext*     CelShading::context = NULL;

#define GL (*graphic_state)

CelShading::CelShading()
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Shading(&context)
{
    IFTRACE(shading)
            debug() << "Create cel shading" << "\n";

    checkGLContext();
}


CelShading::~CelShading()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void CelShading::setCelColor(GLfloat color[3])
// ----------------------------------------------------------------------------
//   Set Cel Shading color
// ----------------------------------------------------------------------------
{
    cel[0] = color[0];
    cel[1] = color[1];
    cel[2] = color[2];
}


void CelShading::Draw()
// ----------------------------------------------------------------------------
//   Apply cel shading
// ----------------------------------------------------------------------------
{
    if (!tested)
    {
        licensed = tao->checkImpressOrLicense("Shading 1.006");
        tested = true;
    }

    checkGLContext();

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        IFTRACE(shading)
                debug() << "Apply cel shading" << "\n";

        // Set shader
        tao->SetShader(prg_id);

        // Set cel color
        GL.Uniform3fv(uniforms["cel_color"], 1, cel);

        if(tao->isGLExtensionAvailable("GL_EXT_gpu_shader4"))
        {
            GLint lightsmask = tao->EnabledLights();
            GL.Uniform(uniforms["lights"], lightsmask);
        }
    }
}


void CelShading::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs
// ----------------------------------------------------------------------------
{
    if(!failed)
    {
        IFTRACE(shading)
                debug() << "Create shader for cel shading" << "\n";

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
                "** This file is part of the Tao Presentations application, developped by Taodyne.\n"
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
                    "** This file is part of the Tao Presentations application, developped by Taodyne.\n"
                    "** It can be only used in the software and these modules.                        \n"
                    "**                                                                               \n"
                    "** If you have questions regarding the use of this file, please contact          \n"
                    "** Taodyne at contact@taodyne.com.                                               \n"
                    "**                                                                               \n"
                    "********************************************************************************/\n"
                    "#extension GL_EXT_gpu_shader4 : require\n"

                    "uniform vec3 cel_color;"
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
                    "       spec = max(dot(reflectVec, -viewDir), 0.0);"

                    "       diff = diff * 0.6 + spec * 0.4;"
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
                    "                   spec = max(dot(reflectVec, -viewDir), 0.0);"

                    "               diff += diffTmp * 0.6 + spec * 0.4;"
                    "           }"
                    "       }"
                    "   }"

                    "    /* Compute final color */"
                    "    vec3 color;"
                    "    if(diff < 0.2)"
                    "       color = cel_color * 0.5;"
                    "    else if(diff < 0.5)"
                    "       color = cel_color * 0.75;"
                    "    else"
                    "       color = cel_color;"

                    "    gl_FragColor = vec4(color, 1.0);"
                    "}";
        }
        else
        {
            // If the extension is not available, use this shader
            // to handle an unique light
            fSrc =
                    "/********************************************************************************\n"
                    "**                                                                               \n"
                    "** Copyright (C) 2011 Taodyne.                                                   \n"
                    "** All rights reserved.                                                          \n"
                    "** Contact: Taodyne (contact@taodyne.com)                                        \n"
                    "**                                                                               \n"
                    "** This file is part of the Tao Presentations application, developped by Taodyne.\n"
                    "** It can be only used in the software and these modules.                        \n"
                    "**                                                                               \n"
                    "** If you have questions regarding the use of this file, please contact          \n"
                    "** Taodyne at contact@taodyne.com.                                               \n"
                    "**                                                                               \n"
                    "********************************************************************************/\n"
                    "uniform vec3 cel_color;"

                    "varying vec3 normal;"
                    "varying vec3 viewDir;"
                    "void main()"
                    "{"
                    "    float diff = 0.0;"
                    "    float spec = 0.0;"

                    "    vec3 lightDir   = normalize(gl_LightSource[0].position.xyz - viewDir);"
                    "    vec3 reflectVec = normalize(reflect( -lightDir, normal ));"

                    "    /* Diffuse intensity */"
                    "    diff = max(dot(normal,lightDir), 0.0);"

                    "    /* Specular intensity */"
                    "    if (diff > 0.0)"
                    "       spec = max(dot(reflectVec, -viewDir), 0.0);"

                    "    diff = diff * 0.6 + spec * 0.4;"

                    "    /* Compute final color */"
                    "    vec3 color;"
                    "    if(diff < 0.2)"
                    "       color = cel_color * 0.5;"
                    "    else if(diff < 0.5)"
                    "       color = cel_color * 0.75;"
                    "    else"
                    "       color = cel_color;"

                    "    gl_FragColor = vec4(color, 1.0);"
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
            uniforms["cel_color"] = glGetUniformLocation(id, "cel_color");
            uniforms["lights"] = glGetUniformLocation(id, "lights");
        }
    }
}
