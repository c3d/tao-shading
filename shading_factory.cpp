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
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "shading_factory.h"
#include <iostream>
#include "coords3d.h"

XL_DEFINE_TRACES

// cel shading parameter
static GLfloat celColor[3] = {1.0, 1.0, 1.0};

// gooch shading parameters
static GLfloat warmDiffuse = 0.45;
static GLfloat coolDiffuse = 0.045;
static GLfloat warmColor[3]    = {1.0, 1.0, 1.0};
static GLfloat coolColor[3]    = {0.0, 0.0, 0.0};
static GLfloat surfaceColor[3] = {1.0, 1.0, 1.0};

// -------------------------------------------------------------------------------------------------------------------
//   CEL SHADING
// -------------------------------------------------------------------------------------------------------------------

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


Tree_p cel_shading(Tree_p, float)
// ----------------------------------------------------------------------------
//   Define cel shading
// ----------------------------------------------------------------------------
{
    CelShading* cel = new CelShading();
    cel->setCelColor(celColor);

    Shading::tao->AddToLayout2(Shading::render_callback,
                               Shading::identify_callback,
                               cel, Shading::delete_callback);

    return xl_true;
}

// -------------------------------------------------------------------------------------------------------------------
//   GOOCH SHADING
// -------------------------------------------------------------------------------------------------------------------

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


Tree_p gooch_shading(Tree_p, float)
// ----------------------------------------------------------------------------
//   Define gooch shading
// ----------------------------------------------------------------------------
{
    GoochShading* gooch = new GoochShading();

    gooch->setWarmColor(warmColor);
    gooch->setCoolColor(coolColor);
    gooch->setSurfaceColor(surfaceColor);

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
