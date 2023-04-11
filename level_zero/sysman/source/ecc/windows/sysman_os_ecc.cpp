/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "level_zero/sysman/source/ecc/sysman_ecc_imp.h"
#include "level_zero/sysman/source/windows/zes_os_sysman_imp.h"

namespace L0 {
namespace Sysman {
class WddmSysmanImp;
class FirmwareUtil;

FirmwareUtil *EccImp::getFirmwareUtilInterface(OsSysman *pOsSysman) {
    return nullptr;
}

} // namespace Sysman
} // namespace L0