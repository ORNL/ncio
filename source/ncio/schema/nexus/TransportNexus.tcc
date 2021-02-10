/**
 * TransportNexus.tcc
 *
 *  Created on: Jan 19, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"
#include "ncio/transport/Transport.h"

namespace ncio::transport
{

template <>
schema::nexus::model1_t
Transport::GetMetadata<schema::nexus::index, schema::nexus::index::model1,
                       schema::nexus::model1_t>(const Parameters &parameters)
{
    schema::nexus::model1_t index;
    DoGetMetadataNexus(index, schema::nexus::index::model1, parameters);
    return index;
}

}
