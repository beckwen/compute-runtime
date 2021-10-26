/*
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/source/helpers/compiler_hw_info_config.h"

namespace NEO {
template <PRODUCT_FAMILY gfxProduct>
bool CompilerHwInfoConfigHw<gfxProduct>::isForceToStatelessRequired() const {
    return false;
}

template <PRODUCT_FAMILY gfxProduct>
bool CompilerHwInfoConfigHw<gfxProduct>::isForceEmuInt32DivRemSPRequired() const {
    return false;
}
template <PRODUCT_FAMILY gfxProduct>
bool CompilerHwInfoConfigHw<gfxProduct>::isStatelessToStatefulBufferOffsetSupported() const {
    return true;
}

} // namespace NEO
