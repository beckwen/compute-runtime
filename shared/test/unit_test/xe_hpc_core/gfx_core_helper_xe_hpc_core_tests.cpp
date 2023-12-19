/*
 * Copyright (C) 2021-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/helpers/api_specific_config.h"
#include "shared/source/helpers/gfx_core_helper.h"
#include "shared/source/os_interface/product_helper.h"
#include "shared/source/xe_hpc_core/hw_cmds_xe_hpc_core_base.h"
#include "shared/test/common/helpers/default_hw_info.h"
#include "shared/test/common/helpers/gfx_core_helper_tests.h"
#include "shared/test/common/mocks/mock_execution_environment.h"
#include "shared/test/common/test_macros/header/per_product_test_definitions.h"
#include "shared/test/common/test_macros/test.h"

using namespace NEO;
using GfxCoreHelperXeHpcCoreTest = ::testing::Test;

XE_HPC_CORETEST_F(GfxCoreHelperXeHpcCoreTest, givenSlmSizeWhenEncodingThenReturnCorrectValues) {
    ComputeSlmTestInput computeSlmValuesXeHpcTestsInput[] = {
        {0, 0 * MemoryConstants::kiloByte},
        {1, 0 * MemoryConstants::kiloByte + 1},
        {1, 1 * MemoryConstants::kiloByte},
        {2, 1 * MemoryConstants::kiloByte + 1},
        {2, 2 * MemoryConstants::kiloByte},
        {3, 2 * MemoryConstants::kiloByte + 1},
        {3, 4 * MemoryConstants::kiloByte},
        {4, 4 * MemoryConstants::kiloByte + 1},
        {4, 8 * MemoryConstants::kiloByte},
        {5, 8 * MemoryConstants::kiloByte + 1},
        {5, 16 * MemoryConstants::kiloByte},
        {8, 16 * MemoryConstants::kiloByte + 1},
        {8, 24 * MemoryConstants::kiloByte},
        {6, 24 * MemoryConstants::kiloByte + 1},
        {6, 32 * MemoryConstants::kiloByte},
        {9, 32 * MemoryConstants::kiloByte + 1},
        {9, 48 * MemoryConstants::kiloByte},
        {7, 48 * MemoryConstants::kiloByte + 1},
        {7, 64 * MemoryConstants::kiloByte},
        {10, 64 * MemoryConstants::kiloByte + 1},
        {10, 96 * MemoryConstants::kiloByte},
        {11, 96 * MemoryConstants::kiloByte + 1},
        {11, 128 * MemoryConstants::kiloByte}};

    auto hwInfo = *defaultHwInfo;
    MockExecutionEnvironment mockExecutionEnvironment{};
    auto &gfxCoreHelper = mockExecutionEnvironment.rootDeviceEnvironments[0]->getHelper<GfxCoreHelper>();

    for (auto &testInput : computeSlmValuesXeHpcTestsInput) {
        EXPECT_EQ(testInput.expected, gfxCoreHelper.computeSlmValues(hwInfo, testInput.slmSize));
    }

    EXPECT_THROW(gfxCoreHelper.computeSlmValues(hwInfo, 129 * MemoryConstants::kiloByte), std::exception);
}

XE_HPC_CORETEST_F(GfxCoreHelperXeHpcCoreTest, WhenGettingIsCpuImageTransferPreferredThenTrueIsReturned) {
    MockExecutionEnvironment mockExecutionEnvironment{};
    auto &gfxCoreHelper = mockExecutionEnvironment.rootDeviceEnvironments[0]->getHelper<GfxCoreHelper>();
    EXPECT_TRUE(gfxCoreHelper.isCpuImageTransferPreferred(*defaultHwInfo));
}

XE_HPC_CORETEST_F(GfxCoreHelperXeHpcCoreTest, givenGfxCoreHelperWhenCheckTimestampWaitSupportThenReturnTrue) {
    MockExecutionEnvironment mockExecutionEnvironment{};
    auto &gfxCoreHelper = mockExecutionEnvironment.rootDeviceEnvironments[0]->getHelper<GfxCoreHelper>();
    EXPECT_TRUE(gfxCoreHelper.isTimestampWaitSupportedForQueues());
}

using ProductHelperTestXeHpcCore = Test<DeviceFixture>;

XE_HPC_CORETEST_F(ProductHelperTestXeHpcCore, givenProductHelperWhenCheckTimestampWaitSupportForEventsThenReturnTrue) {
    auto &helper = getHelper<ProductHelper>();
    EXPECT_TRUE(helper.isTimestampWaitSupportedForEvents());
}

XE_HPC_CORETEST_F(GfxCoreHelperTest, givenGfxCoreHelperWhenCallCopyThroughLockedPtrEnabledThenReturnTrue) {
    const auto &gfxCoreHelper = getHelper<GfxCoreHelper>();
    const auto &productHelper = getHelper<ProductHelper>();
    EXPECT_TRUE(gfxCoreHelper.copyThroughLockedPtrEnabled(*defaultHwInfo, productHelper));
}

XE_HPC_CORETEST_F(GfxCoreHelperTest, givenGfxCoreHelperWhenCallGetAmountOfAllocationsToFillThenReturnTrue) {
    auto &gfxCoreHelper = getHelper<GfxCoreHelper>();
    EXPECT_EQ(gfxCoreHelper.getAmountOfAllocationsToFill(), 1u);
}

HWTEST_EXCLUDE_PRODUCT(GfxCoreHelperTest, givenGfxCoreHelperWhenAskingForRelaxedOrderingSupportThenReturnFalse, IGFX_XE_HPC_CORE);

XE_HPC_CORETEST_F(GfxCoreHelperXeHpcCoreTest, givenGfxCoreHelperWhenAskingForRelaxedOrderingSupportThenReturnTrue) {
    MockExecutionEnvironment mockExecutionEnvironment{};
    auto &gfxCoreHelper = mockExecutionEnvironment.rootDeviceEnvironments[0]->getHelper<GfxCoreHelper>();

    EXPECT_TRUE(gfxCoreHelper.isRelaxedOrderingSupported());
}
XE_HPC_CORETEST_F(GfxCoreHelperXeHpcCoreTest, whenGetDefaultDeviceHierarchyThenReturnFlatHierarchy) {
    MockExecutionEnvironment mockExecutionEnvironment{};
    auto &gfxCoreHelper = mockExecutionEnvironment.rootDeviceEnvironments[0]->getHelper<GfxCoreHelper>();

    auto defaultDeviceHierarchy = gfxCoreHelper.getDefaultDeviceHierarchy();
    EXPECT_STREQ("FLAT", defaultDeviceHierarchy);
}
