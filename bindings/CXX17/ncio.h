/**
 * ncio.h : unique public header. Projects using ncio should only include this
 * header
 *
 *  Created on: May 8, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioTypes.h"
#include "ncio/cxx17/cxx17DataDescriptor.h"
#include "ncio/cxx17/cxx17NCIO.h"
#include "ncio/ncioConfig.h"

// MAKE SCHEMA TYPES PUBLICLY ACCESSIBLE
#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"
#endif
