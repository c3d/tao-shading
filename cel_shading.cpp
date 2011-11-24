// ****************************************************************************
//  cel_shading.cpp                                                Tao project
// ****************************************************************************
//
//   File Description:
//
//   Cel Shading (or Toon Shading) implementation.
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

bool Shading::tested = false;
bool Shading::licensed = false;

const Tao::ModuleApi *Shading::tao = NULL;

// ============================================================================
//
//    Cel Shading
//
// ============================================================================

QGLShaderProgram *CelShading::pgm = NULL;
bool		  CelShading::failed = false;

CelShading::CelShading()
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
{
    if(!pgm && !failed)
    {
        pgm = new QGLShaderProgram();
        bool ok = false;

        // Basic vertex shader
        static string vSrc =
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

        pgm->link();
    }
}

CelShading::~CelShading()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void CelShading::setCelColor(coord r, coord g, coord b)
{
    cel[0] = r;
    cel[1] = g;
    cel[2] = b;
}


void CelShading::render_callback(void *arg)
// ----------------------------------------------------------------------------
//   Rendering callback: call the render function for the object
// ----------------------------------------------------------------------------
{
    ((CelShading *)arg)->Draw();
}


void CelShading::identify_callback(void *arg)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
}


void CelShading::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (CelShading *)arg;
}


void CelShading::Draw()
{
    if (!tested)
    {
        licensed = tao->checkLicense("Shading 1.0", false);
        tested = true;
    }
    if (!licensed && !tao->blink(1.0, 0.2))
        return;

    uint id = pgm->programId();
    tao->SetShader(pgm->programId());

    if(id)
    {
        // Set cel color
        GLint cel_color = glGetUniformLocation(id, "cel_color");
        glUniform3fv(cel_color, 1, cel);

        if(tao->isGLExtensionAvailable("GL_EXT_gpu_shader4"))
        {
            GLint lights = glGetUniformLocation(id, "lights");
            GLint lightsmask = tao->EnabledLights();

            glUniform1i(lights, lightsmask);
        }
    }
}

