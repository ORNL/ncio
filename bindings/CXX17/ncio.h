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

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/cxx17/schema/nexus/cxx17ncioNexus.h"
#include "ncio/schema/nexus/ncioTypesNexus.h"
#endif
