#ifndef INCLUDED_STABLE_H
#define INCLUDED_STABLE_H

#ifdef __cplusplus

#ifdef WIN32
#define WINDOWS_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include <cassert>

#include <QtCore>

#ifdef Q_WS_X11
#include <QtGui>
#include "GLee.h"
#include <QtOpenGL>
#else
#include "GLee.h"
#include <QtGui>
#include <QtOpenGL>
#endif

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#endif
#endif
