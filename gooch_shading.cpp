// ****************************************************************************
//  gooch_shading.cpp                                               Tao project
// ****************************************************************************
//
//   File Description:
//
//   Gooch Shading implementation.
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
#include "gooch_shading.h"


// ============================================================================
//
//    Gooch Shading
//
// ============================================================================

QGLShaderProgram *GoochShading::pgm = NULL;
bool		  GoochShading::failed = false;

GoochShading::GoochShading()
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
                "   vec3 kfinal = mix(kcool, kwarm, diff);"

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
                "   vec3 kfinal = mix(kcool, kwarm, diff);"

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

        pgm->link();
    }
}

GoochShading::~GoochShading()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void GoochShading::setCoolColor(coord r, coord g, coord b)
{
    warm[0] = r;
    warm[1] = g;
    warm[2] = b;
}


void GoochShading::setWarmColor(coord r, coord g, coord b)
{
    cool[0] = r;
    cool[1] = g;
    cool[2] = b;
}


void GoochShading::setSurfaceColor(coord r, coord g, coord b)
{
    surface[0] = r;
    surface[1] = g;
    surface[2] = b;
}


void GoochShading::setWarmDiffuse(coord d)
{
    wd = d;
}


void GoochShading::setCoolDiffuse(coord d)
{
    cd = d;
}


void GoochShading::render_callback(void *arg)
// ----------------------------------------------------------------------------
//   Rendering callback: call the render function for the object
// ----------------------------------------------------------------------------
{
    ((GoochShading *)arg)->Draw();
}


void GoochShading::identify_callback(void *arg)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
}


void GoochShading::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (GoochShading *)arg;
}


void GoochShading::Draw()
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
        // Set gooch colors
        GLint warm_color = glGetUniformLocation(id, "warm_color");
        glUniform3fv(warm_color, 1, warm);
        GLint cool_color = glGetUniformLocation(id, "cool_color");
        glUniform3fv(cool_color, 1, cool);
        GLint surface_color = glGetUniformLocation(id, "surface_color");
        glUniform3fv(surface_color, 1, surface);

        // Set gooch coeffs
        GLint warm_diffuse = glGetUniformLocation(id, "warm_diffuse");
        glUniform1f(warm_diffuse, wd);
        GLint cool_diffuse = glGetUniformLocation(id, "cool_diffuse");
        glUniform1f(cool_diffuse, cd);


        if(tao->isGLExtensionAvailable("GL_EXT_gpu_shader4"))
        {
            GLint lights = glGetUniformLocation(id, "lights");
            GLint lightsmask = tao->EnabledLights();

            glUniform1i(lights, lightsmask);
        }
    }
}

