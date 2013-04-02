#ifndef SHADING_H
#define SHADING_H
// ****************************************************************************
//  shading.h                                                       Tao project
// ****************************************************************************
//
//   File Description:
//
//    Define a shading effect.
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
#include "tao/module_api.h"
#include "tao/graphic_state.h"
#include "tao/tao_gl.h"
#include <QObject>

using namespace std;
using namespace Tao;

struct Shading : public QObject
{
    Shading(const QGLContext **pcontext = NULL);
    ~Shading();

    // Draw shading
    virtual void    Draw();

    // Re-create shaders if GL context has changed
    void            checkGLContext();
    virtual void    createShaders();

    std::ostream &  debug();

    static void     render_callback(void *arg);
    static void     identify_callback(void *arg);
    static void     delete_callback(void *arg);

public:
    const QGLContext    **pcontext;

public:
    static bool tested, licensed;

    // Pointer to Tao functions
    static const Tao::ModuleApi *tao;
};


#endif
