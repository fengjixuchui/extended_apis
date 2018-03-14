//
// Bareflank Extended APIs
// Copyright (C) 2018 Assured Information Security, Inc.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#ifndef EAPIS_VIC_BASE_INTEL_X64_EAPIS_H
#define EAPIS_VIC_BASE_INTEL_X64_EAPIS_H

#include "../../../hve/arch/intel_x64/base.h"

#ifndef EAPIS_VIC_LOG_MAX
#define EAPIS_VIC_LOG_MAX 10
#endif

// -----------------------------------------------------------------------------
// Exports
// -----------------------------------------------------------------------------

#include <bfexports.h>

#ifndef STATIC_EAPIS_VIC
#ifdef SHARED_EAPIS_VIC
#define EXPORT_EAPIS_VIC EXPORT_SYM
#else
#define EXPORT_EAPIS_VIC IMPORT_SYM
#endif
#else
#define EXPORT_EAPIS_VIC
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
