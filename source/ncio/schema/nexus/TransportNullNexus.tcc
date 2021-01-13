/**
 * TransportNullNexus.tcc
 *
 *  Created on: Jan 20, 2021
 *      Author: wgodoy
 */

#pragma once

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

#include "ncio/transport/TransportNull.h"

namespace ncio::transport
{

void TransportNull::DoGetMetadataNexus(schema::nexus::model1_t &index,
                                       const schema::nexus::index model,
                                       const Parameters &parameters)
{
}

}
