/*
 * Copyright (C) 2020-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/gen12lp/hw_cmds_tgllp.h"
#include "shared/source/gen12lp/hw_info.h"

#include "level_zero/core/source/cmdqueue/cmdqueue_hw.inl"
#include "level_zero/core/source/cmdqueue/cmdqueue_hw_base.inl"

#include "cmdqueue_extended.inl"
#include "igfxfmid.h"

namespace L0 {
template struct CommandQueueHw<IGFX_GEN12LP_CORE>;
static CommandQueuePopulateFactory<IGFX_TIGERLAKE_LP, CommandQueueHw<IGFX_GEN12LP_CORE>>
    populateTGLLP;

} // namespace L0
