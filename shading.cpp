// ****************************************************************************
//  shading.cpp                                                    Tao project
// ****************************************************************************
//
//   File Description:
//
//     Implementation of the XL primitives for the "shading" module.
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

#include "shading.h"
#include <iostream>
#include "coords3d.h"

XL_DEFINE_TRACES

static GLfloat celColor[3] = {1.0, 1.0, 1.0};

static GLfloat warmDiffuse = 0.45;
static GLfloat coolDiffuse = 0.045;
static GLfloat warmColor[3]    = {1.0, 1.0, 1.0};
static GLfloat coolColor[3]    = {0.0, 0.0, 0.0};
static GLfloat surfaceColor[3] = {1.0, 1.0, 1.0};

Tree_p cel_color(Tree_p, Real_p r, Real_p g, Real_p b)
// ----------------------------------------------------------------------------
//   Set cel shading color
// ----------------------------------------------------------------------------
{
    celColor[0] = r;
    celColor[1] = g;
    celColor[2] = b;

    return xl_true;
}

Tree_p cel_shading(Tree_p)
// ----------------------------------------------------------------------------
//   Define cel shading
// ----------------------------------------------------------------------------
{       
    CelShading* cel = new CelShading();
    cel->setCelColor(celColor[0], celColor[1], celColor[2]);

    Shading::tao->AddToLayout2(CelShading::render_callback,
                               CelShading::identify_callback,
                               cel, CelShading::delete_callback);

    return xl_true;
}


Tree_p warm_diffuse(Tree_p, Real_p r)
// ----------------------------------------------------------------------------
//   Set warm diffuse coeff for gooch shading
// ----------------------------------------------------------------------------
{
    warmDiffuse = r;
    return xl_true;
}


Tree_p cool_diffuse(Tree_p, Real_p r)
// ----------------------------------------------------------------------------
//   Set cool diffuse coeff for gooch shading
// ----------------------------------------------------------------------------
{
    coolDiffuse = r;
    return xl_true;
}


Tree_p warm_color(Tree_p, Real_p r, Real_p g, Real_p b)
// ----------------------------------------------------------------------------
//   Set warm color for gooch shading
// ----------------------------------------------------------------------------
{
    warmColor[0] = r;
    warmColor[1] = g;
    warmColor[2] = b;

    return xl_true;
}


Tree_p cool_color(Tree_p, Real_p r, Real_p g, Real_p b)
// ----------------------------------------------------------------------------
//   Set cool color for gooch shading
// ----------------------------------------------------------------------------
{
    coolColor[0] = r;
    coolColor[1] = g;
    coolColor[2] = b;

    return xl_true;
}


Tree_p surface_color(Tree_p, Real_p r, Real_p g, Real_p b)
// ----------------------------------------------------------------------------
//   Set surface color for gooch shading
// ----------------------------------------------------------------------------
{
    surfaceColor[0] = r;
    surfaceColor[1] = g;
    surfaceColor[2] = b;

    return xl_true;
}


Tree_p gooch_shading(Tree_p)
// ----------------------------------------------------------------------------
//   Define gooch shading
// ----------------------------------------------------------------------------
{
    GoochShading* gooch = new GoochShading();

    gooch->setWarmColor(warmColor[0], warmColor[1], warmColor[2]);
    gooch->setCoolColor(coolColor[0], coolColor[1], coolColor[2]);
    gooch->setSurfaceColor(surfaceColor[0], surfaceColor[1], surfaceColor[2]);

    gooch->setWarmDiffuse(warmDiffuse);
    gooch->setCoolDiffuse(coolDiffuse);

    Shading::tao->AddToLayout2(GoochShading::render_callback,
                               GoochShading::identify_callback,
                               gooch, GoochShading::delete_callback);


    return xl_true;
}


int module_init(const Tao::ModuleApi *api, const Tao::ModuleInfo *)
// ----------------------------------------------------------------------------
//   Initialize the Tao module
// ----------------------------------------------------------------------------
{
    glewInit();
    XL_INIT_TRACES();

    Shading::tao = api;

    return 0;
}


int module_exit()
// ----------------------------------------------------------------------------
//   Uninitialize the Tao module
// ----------------------------------------------------------------------------
{
    return 0;
}
