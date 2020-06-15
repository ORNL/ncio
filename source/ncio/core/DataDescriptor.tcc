/**
 * DataDescriptor.tcc: Implementation  of private core::DataDescriptor class
 * template functions.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "DataDescriptor.h"

#include "ncio/ncioConfig.h"

namespace ncio::core
{} // end namespace ncio::core

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/ncioNexusDataDescriptor.tcc"
#endif
