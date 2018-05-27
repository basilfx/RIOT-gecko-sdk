#!/bin/bash -e

GECKO_SDK_VERSION="com.silabs.sdk.gecko_platform.v2.2.feature_root_2.2.2.201803221440-117"
# GECKO_SDK_VERSION="com.silabs.sdk.gecko_platform.v2.3.feature_root_2.3.0.201805241756-126"
GECKO_SDK_URL="https://devtools.silabs.com/studio/v4/updates/binary/"

DIST_DIR=`pwd`/dist
SRC_DIR=`pwd`/src
TEMP_DIR=`pwd`/temp

# Clear everything in the target folder.
rm -rf "${DIST_DIR}"
rm -rf "${TEMP_DIR}"
mkdir -p "${DIST_DIR}"
mkdir -p "${TEMP_DIR}"

# Download and extract Gecko SDK.
wget -O "${TEMP_DIR}/gecko_sdk.zip" "${GECKO_SDK_URL}${GECKO_SDK_VERSION}"

unzip -o "${TEMP_DIR}/gecko_sdk.zip" -d "${TEMP_DIR}/gecko_sdk"

# Prepare distribution.
rsync -avp "${TEMP_DIR}/gecko_sdk/developer/sdks/gecko_sdk_suite/v2.2/platform/emlib" "${DIST_DIR}"
rsync -avp "${TEMP_DIR}/gecko_sdk/developer/sdks/gecko_sdk_suite/v2.2/platform/radio" "${DIST_DIR}"

# These files are deprecated and cause build errors.
rm "${DIST_DIR}/emlib/src/em_int.c"
rm "${DIST_DIR}/emlib/inc/em_int.h"

# Remove unneeded files.
rm "${DIST_DIR}/radio/rail_lib/modules.xml"
rm -rf "${DIST_DIR}/radio/rail_lib/apps"
rm -rf "${DIST_DIR}/radio/rail_lib/hal"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin"

# Ensure Unix line endings are used.
find "${DIST_DIR}" -name "*.c" -type f -exec dos2unix -k -s -o {} ';'
find "${DIST_DIR}" -name "*.h" -type f -exec dos2unix -k -s -o {} ';'

# Apply source code patches.
for PATCH_FILE in "patches/"*".patch"
do
    patch -p0 < "${PATCH_FILE}"
done

# Rename IRQ handlers to match the RIOT-OS IRQ handlers.
for BLOB_FILE in "${DIST_DIR}/radio/rail_lib/autogen/librail_release/"*".a"
do
    arm-none-eabi-objcopy "${BLOB_FILE}" \
        --redefine-sym FRC_PRI_IRQHandler=isr_frc_pri \
        --redefine-sym FRC_IRQHandler=isr_frc \
        --redefine-sym MODEM_IRQHandler=isr_modem \
        --redefine-sym RAC_SEQ_IRQHandler=isr_rac_seq \
        --redefine-sym RAC_RSM_IRQHandler=isr_rac_rsm \
        --redefine-sym BUFC_IRQHandler=isr_bufc \
        --redefine-sym AGC_IRQHandler=isr_agc \
        --redefine-sym PROTIMER_IRQHandler=isr_protimer \
        --redefine-sym SYNTH_IRQHandler=isr_synth \
        --redefine-sym RFSENSE_IRQHandler=isr_rfsense
done

# Copy additional source files (such as Makefiles, utilities).
rsync -avp --ignore-existing "${SRC_DIR}/" "${DIST_DIR}"

# Cleanup.
rm -rf "${TEMP_DIR}"
