// ****************************************************************************
//  shading.cpp                                                     Tao project
// ****************************************************************************
//
//   File Description:
//
//   Shading basis.
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
//  (C) 1992-2010 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2010 Jerome Forissier <jerome@taodyne.com>
//  (C) 2010 Taodyne SAS
// ****************************************************************************
#include "shading.h"

const Tao::ModuleApi *Shading::tao = NULL;

// ============================================================================
//
//    Shading
//
// ============================================================================

Shading::Shading(const QGLContext **pcontext)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : pcontext(pcontext)
{
}


Shading::~Shading()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void Shading::render_callback(void *arg)
// ----------------------------------------------------------------------------
//   Rendering callback: call the render function for the object
// ----------------------------------------------------------------------------
{
    ((Shading *)arg)->Draw();
}


void Shading::identify_callback(void *arg)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
    (void) arg;
}


void Shading::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (Shading *)arg;
}


void Shading::Draw()
// ----------------------------------------------------------------------------
//   Draw shading
// ----------------------------------------------------------------------------
{
}


void Shading::checkGLContext()
// ----------------------------------------------------------------------------
//   Re-create context-dependent resources if GL context has changed
// ----------------------------------------------------------------------------
{
    tao->makeGLContextCurrent();
    if (*pcontext != QGLContext::currentContext())
    {
        IFTRACE(shading)
                debug() << "Context has changed" << "\n";

        *pcontext = QGLContext::currentContext();
        createShaders();
    }
}


void Shading::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs for shading effect
// ----------------------------------------------------------------------------
{
}


std::ostream & Shading::debug()
// ----------------------------------------------------------------------------
//   Convenience method to log with a common prefix
// ----------------------------------------------------------------------------
{
    std::cerr << "[Shading] " << (void*)this << " ";
    return std::cerr;
}

