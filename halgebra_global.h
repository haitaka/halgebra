#pragma once

#include <QtCore/qglobal.h>

// QT magic
#if defined(HALGEBRA_LIBRARY)
#  define HALGEBRASHARED_EXPORT Q_DECL_EXPORT
#else
#  define HALGEBRASHARED_EXPORT Q_DECL_IMPORT
#endif
