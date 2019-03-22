#ifndef SHADING_FACTORY_H
#define SHADING_FACTORY_H
// *****************************************************************************
// shading_factory.h                                               Tao3D project
// *****************************************************************************
//
// File description:
//
//    Prototype of the function used by shading.tbl to
//    implement the new XL primitive
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
#include "tree.h"
#include "main.h"
#include "runtime.h"
#include "base.h"
#include "shading.h"
#include "cel_shading.h"
#include "gooch_shading.h"

using namespace XL;


// -------------------------------------------------------------------------------------------------------------------
//   CEL SHADING
// -------------------------------------------------------------------------------------------------------------------

Tree_p cel_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p cel_shading(Tree_p, float);

// -------------------------------------------------------------------------------------------------------------------
//   GOOCH SHADING
// -------------------------------------------------------------------------------------------------------------------

Tree_p warm_diffuse(Tree_p, Real_p r);
Tree_p cool_diffuse(Tree_p, Real_p r);
Tree_p warm_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p cool_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p surface_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p gooch_shading(Tree_p, float);

#endif // SHADING_FACTORY_H
