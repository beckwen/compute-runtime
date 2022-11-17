/*
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/test/common/helpers/default_hw_info.h"
#include "shared/test/common/test_macros/header/per_product_test_definitions.h"
#include "shared/test/common/test_macros/test.h"

#include "level_zero/core/source/hw_helpers/l0_hw_helper.h"
#include "level_zero/core/test/unit_tests/fixtures/device_fixture.h"

#include "hw_cmds_xe_hpg_core_base.h"

namespace L0 {
namespace ult {

HWTEST_EXCLUDE_PRODUCT(L0HwHelperTest, givenBitmaskWithAttentionBitsForSingleThreadWhenGettingThreadsThenSingleCorrectThreadReturned, IGFX_XE_HPG_CORE);
HWTEST_EXCLUDE_PRODUCT(L0HwHelperTest, givenBitmaskWithAttentionBitsForAllSubslicesWhenGettingThreadsThenCorrectThreadsAreReturned, IGFX_XE_HPG_CORE);
HWTEST_EXCLUDE_PRODUCT(L0HwHelperTest, givenBitmaskWithAttentionBitsForAllEUsWhenGettingThreadsThenCorrectThreadsAreReturned, IGFX_XE_HPG_CORE);
HWTEST_EXCLUDE_PRODUCT(L0HwHelperTest, givenEu0To1Threads0To3BitmaskWhenGettingThreadsThenCorrectThreadsAreReturned, IGFX_XE_HPG_CORE);
HWTEST_EXCLUDE_PRODUCT(L0HwHelperTest, givenBitmaskWithAttentionBitsForHalfOfThreadsWhenGettingThreadsThenCorrectThreadsAreReturned, IGFX_XE_HPG_CORE);

using L0HwHelperTestXeHpg = Test<DeviceFixture>;

XE_HPG_CORETEST_F(L0HwHelperTestXeHpg, GivenXeHpgWhenCheckingL0HelperForMultiTileCapablePlatformThenReturnFalse) {
    auto &l0CoreHelper = getHelper<L0CoreHelper>();
    EXPECT_FALSE(l0CoreHelper.multiTileCapablePlatform());
}

XE_HPG_CORETEST_F(L0HwHelperTestXeHpg, GivenXeHpgWhenCheckingL0HelperForCmdListHeapSharingSupportThenReturnTrue) {
    auto &l0CoreHelper = getHelper<L0CoreHelper>();
    NEO::HardwareInfo hwInfo = *NEO::defaultHwInfo;
    EXPECT_TRUE(l0CoreHelper.platformSupportsCmdListHeapSharing(hwInfo));
}

XE_HPG_CORETEST_F(L0HwHelperTestXeHpg, GivenXeHpgcWhenCheckingL0HelperForStateComputeModeTrackingSupportThenReturnTrue) {
    auto &l0CoreHelper = getHelper<L0CoreHelper>();
    NEO::HardwareInfo hwInfo = *NEO::defaultHwInfo;
    EXPECT_TRUE(l0CoreHelper.platformSupportsStateComputeModeTracking(hwInfo));
}

XE_HPG_CORETEST_F(L0HwHelperTestXeHpg, GivenXeHpgWhenCheckingL0HelperForFrontEndTrackingSupportThenReturnTrue) {
    auto &l0CoreHelper = getHelper<L0CoreHelper>();
    NEO::HardwareInfo hwInfo = *NEO::defaultHwInfo;
    EXPECT_TRUE(l0CoreHelper.platformSupportsFrontEndTracking(hwInfo));
}

XE_HPG_CORETEST_F(L0HwHelperTestXeHpg, GivenXeHpgWhenCheckingL0HelperForPipelineSelectTrackingSupportThenReturnTrue) {
    auto &l0CoreHelper = getHelper<L0CoreHelper>();
    NEO::HardwareInfo hwInfo = *NEO::defaultHwInfo;
    EXPECT_TRUE(l0CoreHelper.platformSupportsPipelineSelectTracking(hwInfo));
}

} // namespace ult
} // namespace L0
