/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/debug_settings/debug_settings_manager.h"

#include "level_zero/sysman/source/api/ras/linux/sysman_os_ras_imp.h"
#include "level_zero/sysman/source/shared/firmware_util/sysman_firmware_util.h"
#include "level_zero/sysman/source/shared/linux/zes_os_sysman_imp.h"

namespace L0 {
namespace Sysman {

void LinuxRasSourceHbm::getSupportedRasErrorTypes(std::set<zes_ras_error_type_t> &errorType, OsSysman *pOsSysman, ze_bool_t isSubDevice, uint32_t subDeviceId) {
    LinuxSysmanImp *pLinuxSysmanImp = static_cast<LinuxSysmanImp *>(pOsSysman);
    FirmwareUtil *pFwInterface = pLinuxSysmanImp->getFwUtilInterface();
    if (pFwInterface != nullptr) {
        errorType.insert(ZES_RAS_ERROR_TYPE_CORRECTABLE);
        errorType.insert(ZES_RAS_ERROR_TYPE_UNCORRECTABLE);
    }
}

ze_result_t LinuxRasSourceHbm::getMemoryErrorCountFromFw(zes_ras_error_type_t rasErrorType, uint32_t subDeviceCount, uint64_t &errorCount) {
    return pFwInterface->fwGetMemoryErrorCount(rasErrorType, subDeviceCount, subdeviceId, errorCount);
}

ze_result_t LinuxRasSourceHbm::osRasGetState(zes_ras_state_t &state, ze_bool_t clear) {
    if (pFwInterface == nullptr) {
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    if (clear == true) {
        uint64_t errorCount = 0;
        ze_result_t result = getMemoryErrorCountFromFw(osRasErrorType, this->subDeviceCount, errorCount);
        if (result != ZE_RESULT_SUCCESS) {
            return result;
        }
        errorBaseline = errorCount; // during clear update the error baseline value
    }

    uint64_t errorCount = 0;
    ze_result_t result = getMemoryErrorCountFromFw(osRasErrorType, this->subDeviceCount, errorCount);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    state.category[ZES_RAS_ERROR_CAT_NON_COMPUTE_ERRORS] = errorCount - errorBaseline;
    return ZE_RESULT_SUCCESS;
}

ze_result_t LinuxRasSourceHbm::osRasGetStateExp(uint32_t numCategoriesRequested, zes_ras_state_exp_t *pState) {
    if (pFwInterface == nullptr) {
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    uint64_t errorCount = 0;
    ze_result_t result = getMemoryErrorCountFromFw(osRasErrorType, this->subDeviceCount, errorCount);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    pState[0].category = ZES_RAS_ERROR_CATEGORY_EXP_MEMORY_ERRORS;
    pState[0].errorCounter = errorCount - errorBaseline;

    return ZE_RESULT_SUCCESS;
}

uint32_t LinuxRasSourceHbm::osRasGetCategoryCount() {
    // Return one for "MEMORY" category
    return 1u;
}

LinuxRasSourceHbm::LinuxRasSourceHbm(LinuxSysmanImp *pLinuxSysmanImp, zes_ras_error_type_t type, uint32_t subdeviceId) : pLinuxSysmanImp(pLinuxSysmanImp), osRasErrorType(type), subdeviceId(subdeviceId) {
    pFwInterface = pLinuxSysmanImp->getFwUtilInterface();
    pDevice = pLinuxSysmanImp->getSysmanDeviceImp();
    subDeviceCount = pLinuxSysmanImp->getSubDeviceCount();
}

} // namespace Sysman
} // namespace L0
