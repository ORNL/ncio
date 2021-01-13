/**
 * TransportHDF5Nexus.tcc : compile-time specific extension of the TransportHDF5
 * functions that need to be NeXus schema aware
 *
 *  Created on: Jan 20, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

#include "ncio/transport/TransportHDF5.h"

namespace ncio::transport
{

void TransportHDF5::DoGetMetadataNexus(schema::nexus::model1_t &index,
                                       const schema::nexus::index model,
                                       const Parameters &parameters)
{
    auto lf_getNxClassAttribute = [&](hid_t groupID,
                                      const char *objectName) -> std::string {
        std::string attribute = "";
        hid_t attributeID = H5Aopen_by_name(groupID, objectName, "NX_class",
                                            H5P_DEFAULT, H5P_DEFAULT);
        if (attributeID < 0)
        {
            // non-existent for scientific dataset "SDS" cases
            H5Aclose(attributeID);
            return attribute;
        }

        hid_t type = H5Aget_type(attributeID);
        hid_t typeClass = H5Tget_class(type);
        if (typeClass != H5T_STRING)
        {
            throw std::runtime_error("ncio ERROR: schema NeXus attribute "
                                     "NX_class is not string type\n");
        }

        // using 128 characters, NX_class attributes not expected to be longer
        // than this
        std::vector<char> attributeVector(128);
        // needs native type
        hid_t memoryType = H5Tget_native_type(type, H5T_DIR_ASCEND);
        herr_t status =
            H5Aread(attributeID, memoryType, attributeVector.data());
        if (status < 0)
        {
            throw std::runtime_error("ncio ERROR: schema NeXus attribute "
                                     "NX_class could not be read\n");
        }

        H5Tclose(memoryType);
        H5Aclose(attributeID);

        attribute = std::string(attributeVector.data());
        return attribute;
    };

    // need a callable lambda function as the search is done recursively
    auto lf_GetGroup = [](schema::nexus::model1_t &index, hid_t groupID) {
        const std::size_t groupNameLength =
            static_cast<std::size_t>(H5Iget_name(groupID, NULL, 0));
        std::vector<char> groupName(groupNameLength);
        H5Iget_name(groupID, groupName.data(), groupNameLength);

        hsize_t nObjects = 0;
        H5Gget_num_objs(groupID, &nObjects);

        // convert to string to compare
        const std::string groupNameStr(groupName.data());
        const std::string nxClass =
            (groupNameStr == m_TopGroupID)
                ? ""
                : lf_getNxClassAttribute(groupID, groupNameStr.c_str());

        if (!nxClass.empty())
        {
            index[nxClass].insert(groupNameStr);
        }

        std::vector<char> memberName;

        for (unsigned int i = 0; i < nObjects; ++i)
        {
            const int type =
                H5Gget_objtype_by_idx(groupID, static_cast<size_t>(i));

            const std::size_t memberNameLength =
                static_cast<std::size_t>(H5Gget_objname_by_idx(
                    groupID, static_cast<hsize_t>(i), NULL, 0));
            memberName.clear();
            memberName.resize(memberNameLength);
            H5Gget_objname_by_idx(groupID, static_cast<hsize_t>(i),
                                  memberName.data(), memberNameLength);

            if (type == H5O_TYPE_GROUP)
            {
                hid_t subGroupID =
                    H5Gopen2(groupID, memberName.data(), H5P_DEFAULT);
                lf_GetGroup(subGroupID, index);
                H5Gclose(subGroupID);
            }
            else if (type == H5O_TYPE_DATASET)
            {
                const std::string memberNameStr(memberName.data(),
                                                memberNameLength);
                const std::string absoluteEntryName =
                    groupNameStr + "/" + memberNameStr;
                index["SDS"].insert(absoluteEntryName);
            }
        }
    };

    // need a callable lambda function as the search is done recursively
    lf_GetGroup(m_TopGroupID, index);
}

}
