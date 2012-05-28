#ifndef SHADING_H
#define SHADING_H
// ****************************************************************************
//  shading.h                                                       Tao project
// ****************************************************************************
//
//   File Description:
//
//    Prototype of the function used by shading.tbl to
//    implement the new XL primitive
//
//
//
//
//
//
// ****************************************************************************
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriété de Taodyne SAS - Confidentiel
//  (C) 1992-2010 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2010 Jerome Forissier <jerome@taodyne.com>
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include "tree.h"
#include "main.h"
#include "runtime.h"
#include "base.h"
#include "tao/module_api.h"
#include "cel_shading.h"
#include "gooch_shading.h"

using namespace XL;

// -------------------------------------------------------------------------------------------------------------------
//   CEL SHADING
// -------------------------------------------------------------------------------------------------------------------

Tree_p cel_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p cel_shading(Tree_p);

// -------------------------------------------------------------------------------------------------------------------
//   GOOCH SHADING
// -------------------------------------------------------------------------------------------------------------------

Tree_p warm_diffuse(Tree_p, Real_p r);
Tree_p cool_diffuse(Tree_p, Real_p r);
Tree_p warm_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p cool_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p surface_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p gooch_shading(Tree_p);

#endif
