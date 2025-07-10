/*
 * Copyright (C) 2022-2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>

namespace android {
namespace init {
uint32_t InitPropertySet(const std::string& name, const std::string& value);
}  // namespace init
}  // namespace android

using android::base::GetProperty;
using android::init::InitPropertySet;

/*
 * Only for read-only properties. Properties that can be wrote to more
 * than once should be set in a typical init script (e.g. init.oplus.hw.rc)
 * after the original property has been set.
 */
void vendor_process_bootenv() {
    auto hw_region_id = std::stoi(GetProperty("ro.boot.hw_region_id", "0"));
    auto prjname = std::stoi(GetProperty("ro.boot.prjname", "0"));

    switch (hw_region_id) {
        case 21: // CN_IN
            if (prjname == 22811) { // CN
                InitPropertySet("ro.boot.hardware.revision", "CN");
            } else if (prjname == 22861) { // IN
                InitPropertySet("ro.boot.hardware.revision", "IN");
            }
            break;
        case 22: // EU
            InitPropertySet("ro.boot.hardware.revision", "EU");
            break;
        case 23: // NA
            InitPropertySet("ro.boot.hardware.revision", "NA");
            break;
        default:
            LOG(ERROR) << "Unexpected region ID: " << hw_region_id;
    }
}
