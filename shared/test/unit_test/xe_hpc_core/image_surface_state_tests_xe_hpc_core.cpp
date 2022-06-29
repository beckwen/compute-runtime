/*
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/command_container/command_encoder.h"
#include "shared/source/xe_hpc_core/hw_cmds_xe_hpc_core_base.h"
#include "shared/test/common/test_macros/header/per_product_test_definitions.h"
#include "shared/test/common/test_macros/test.h"
#include "shared/test/unit_test/image/image_surface_state_fixture.h"

using namespace NEO;

using ImageSurfaceStateTestsXeHpcCore = ImageSurfaceStateTests;

XE_HPC_CORETEST_F(ImageSurfaceStateTestsXeHpcCore, givenGmmWithMediaCompressedWhenSetFlagsForMediaCompressionThenAuxiliarySurfaceNoneIsSetAndMemoryCompressionEnable) {
    auto size = sizeof(typename FamilyType::RENDER_SURFACE_STATE);
    auto surfaceState = std::make_unique<char[]>(size);
    auto castSurfaceState = reinterpret_cast<typename FamilyType::RENDER_SURFACE_STATE *>(surfaceState.get());
    castSurfaceState->setAuxiliarySurfaceMode(FamilyType::RENDER_SURFACE_STATE::AUXILIARY_SURFACE_MODE::AUXILIARY_SURFACE_MODE_AUX_CCS_E);

    mockGmm->gmmResourceInfo->getResourceFlags()->Info.MediaCompressed = false;
    EncodeSurfaceState<FamilyType>::setFlagsForMediaCompression(castSurfaceState, mockGmm.get());
    EXPECT_EQ(castSurfaceState->getAuxiliarySurfaceMode(), FamilyType::RENDER_SURFACE_STATE::AUXILIARY_SURFACE_MODE::AUXILIARY_SURFACE_MODE_AUX_CCS_E);
    EXPECT_EQ(castSurfaceState->getMemoryCompressionEnable(), false);
    mockGmm->gmmResourceInfo->getResourceFlags()->Info.MediaCompressed = true;
    EncodeSurfaceState<FamilyType>::setFlagsForMediaCompression(castSurfaceState, mockGmm.get());
    EXPECT_EQ(castSurfaceState->getAuxiliarySurfaceMode(), FamilyType::RENDER_SURFACE_STATE::AUXILIARY_SURFACE_MODE::AUXILIARY_SURFACE_MODE_AUX_NONE);
    EXPECT_EQ(castSurfaceState->getMemoryCompressionEnable(), true);
}

XE_HPC_CORETEST_F(ImageSurfaceStateTestsXeHpcCore, givenGmmWhenSetClearColorParamsThenClearValueAddressEnable) {
    auto size = sizeof(typename FamilyType::RENDER_SURFACE_STATE);
    auto surfaceState = std::make_unique<char[]>(size);
    auto castSurfaceState = reinterpret_cast<typename FamilyType::RENDER_SURFACE_STATE *>(surfaceState.get());

    mockGmm->gmmResourceInfo->getResourceFlags()->Gpu.IndirectClearColor = true;
    EncodeSurfaceState<FamilyType>::setClearColorParams(castSurfaceState, mockGmm.get());
    EXPECT_EQ(castSurfaceState->getClearValueAddressEnable(), true);
}

XE_HPC_CORETEST_F(ImageSurfaceStateTestsXeHpcCore, givenGmmWithMediaCompressedWhenSetMipTailStartLodThenMipTailStartLodIsSet) {
    auto size = sizeof(typename FamilyType::RENDER_SURFACE_STATE);
    auto surfaceState = std::make_unique<char[]>(size);
    auto castSurfaceState = reinterpret_cast<typename FamilyType::RENDER_SURFACE_STATE *>(surfaceState.get());

    setMipTailStartLod<FamilyType>(castSurfaceState, nullptr);

    EXPECT_EQ(castSurfaceState->getMipTailStartLod(), 0u);

    setMipTailStartLod<FamilyType>(castSurfaceState, mockGmm.get());

    EXPECT_EQ(castSurfaceState->getMipTailStartLod(), mockGmm->gmmResourceInfo->getMipTailStartLodSurfaceState());
}
