/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/source/indirect_heap/indirect_heap.h"

namespace NEO {

inline uint64_t getStateBaseAddress(const IndirectHeap &heap, const bool useGlobalHeaps) {
    if (useGlobalHeaps) {
        return heap.getGraphicsAllocation()->getGpuBaseAddress();
    } else {
        return heap.getHeapGpuBase();
    }
}

inline size_t getStateSize(const IndirectHeap &heap, const bool useGlobalHeaps) {
    if (useGlobalHeaps) {
        return MemoryConstants::sizeOf4GBinPageEntities;
    } else {
        return heap.getHeapSizeInPages();
    }
}

inline uint64_t getStateBaseAddress(const IndirectHeap &heap, const bool useGlobalHeaps, const bool isBindlessKernel) {
    if (useGlobalHeaps && isBindlessKernel) {
        return heap.getGraphicsAllocation()->getGpuBaseAddress();
    } else {
        return heap.getHeapGpuBase();
    }
}

inline size_t getStateSize(const IndirectHeap &heap, const bool useGlobalHeaps, const bool isBindlessKernel) {
    if (useGlobalHeaps && isBindlessKernel) {
        return MemoryConstants::sizeOf4GBinPageEntities;
    } else {
        return heap.getHeapSizeInPages();
    }
}

} // namespace NEO
