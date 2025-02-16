/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/release_helper/release_helper.h"
#include "shared/source/release_helper/release_helper_base.inl"
#include "shared/source/xe_hpg_core/hw_cmds_xe_hpg_core_base.h"

#include "platforms.h"
#include "release_definitions.h"

#include <algorithm>

namespace NEO {
constexpr auto release = ReleaseType::release1270;

template <>
bool ReleaseHelperHw<release>::isPipeControlPriorToNonPipelinedStateCommandsWARequired() const {
    return hardwareIpVersion.value == AOT::MTL_U_A0;
}

template <>
bool ReleaseHelperHw<release>::isProgramAllStateComputeCommandFieldsWARequired() const {
    return hardwareIpVersion.value == AOT::MTL_U_A0;
}

template <>
inline bool ReleaseHelperHw<release>::isAuxSurfaceModeOverrideRequired() const {
    return true;
}

template <>
inline bool ReleaseHelperHw<release>::isDotProductAccumulateSystolicSupported() const {
    return false;
}

template <>
int ReleaseHelperHw<release>::getProductMaxPreferredSlmSize(int preferredEnumValue) const {
    using PREFERRED_SLM_ALLOCATION_SIZE = typename XeHpgCoreFamily::INTERFACE_DESCRIPTOR_DATA::PREFERRED_SLM_ALLOCATION_SIZE;
    return std::min(preferredEnumValue, static_cast<int>(PREFERRED_SLM_ALLOCATION_SIZE::PREFERRED_SLM_ALLOCATION_SIZE_96K));
}

template <>
inline bool ReleaseHelperHw<release>::isBindlessAddressingDisabled() const {
    return false;
}

template <>
inline bool ReleaseHelperHw<release>::isGlobalBindlessAllocatorEnabled() const {
    return false;
}

} // namespace NEO
#include "shared/source/release_helper/release_helper_common_xe_lpg.inl"

template class NEO::ReleaseHelperHw<NEO::release>;
