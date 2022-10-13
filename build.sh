#!/bin/bash -e

GECKO_SDK_USER="SiliconLabs"
GECKO_SDK_REPO="gecko_sdk"
GECKO_SDK_SHA1="1b1146884839bbfddaae34da39de8d780ed905b9" # Version 4.1.2
GECKO_SDK_URL="https://github.com/${GECKO_SDK_USER}/${GECKO_SDK_REPO}/archive/${GECKO_SDK_SHA1}.zip"

DIST_DIR=$(pwd)/dist
SRC_DIR=$(pwd)/src
TEMP_DIR=$(pwd)/temp

# Clear everything in the target folder.
rm -rf "${DIST_DIR}"
rm -rf "${TEMP_DIR}"
mkdir -p "${DIST_DIR}"
mkdir -p "${TEMP_DIR}"

# Download and extract Gecko SDK.
wget -O "${TEMP_DIR}/gecko_sdk.zip" "${GECKO_SDK_URL}"
unzip -o "${TEMP_DIR}/gecko_sdk.zip" -d "${TEMP_DIR}"
mv "${TEMP_DIR}/${GECKO_SDK_REPO}-${GECKO_SDK_SHA1}" "${TEMP_DIR}/gecko_sdk"

# Prepare distribution.
cp "${TEMP_DIR}/gecko_sdk/License.txt" "${DIST_DIR}"
rsync -avp "${TEMP_DIR}/gecko_sdk/platform/common" "${DIST_DIR}"
rsync -avp "${TEMP_DIR}/gecko_sdk/platform/emlib" "${DIST_DIR}"
rsync -avp "${TEMP_DIR}/gecko_sdk/platform/radio" "${DIST_DIR}"

# Remove unneeded files.
rm "${DIST_DIR}/emlib/emlib_core_validation.lua"
rm -rf "${DIST_DIR}/common/component"
rm -rf "${DIST_DIR}/common/component_catalog"
rm -rf "${DIST_DIR}/common/config"
rm -rf "${DIST_DIR}/common/errno"
rm -rf "${DIST_DIR}/common/script"
rm -rf "${DIST_DIR}/common/src"
rm -rf "${DIST_DIR}/common/toolchain"
rm -rf "${DIST_DIR}/emlib/component"
rm -rf "${DIST_DIR}/emlib/config"
rm -rf "${DIST_DIR}/emlib/host"
rm -rf "${DIST_DIR}/emlib/init"
rm -rf "${DIST_DIR}/radio/efr32_multiphy_configurator"
rm -rf "${DIST_DIR}/radio/mac"
rm -rf "${DIST_DIR}/radio/radio_configuration"
rm "${DIST_DIR}/radio/rail_lib/modules.xml"
rm -rf "${DIST_DIR}/radio/rail_lib/apps"
rm -rf "${DIST_DIR}/radio/rail_lib/component"
rm -rf "${DIST_DIR}/radio/rail_lib/hal"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/coexistence"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/coexistence-stub"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/component"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/module"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/rail-library"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/rail-library-mp"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin/plugin.info"

find "${DIST_DIR}/radio/rail_lib/autogen/librail_release" -type f -name "*_iar.a" -delete
find "${DIST_DIR}/radio/rail_lib/autogen/librail_release" -type f -name "*_iar_*.a" -delete

# Ensure Unix line endings are used.
find "${DIST_DIR}" -name "*.c" -type f -exec dos2unix -k -s -o {} ';'
find "${DIST_DIR}" -name "*.h" -type f -exec dos2unix -k -s -o {} ';'

# Apply source code patches.
for PATCH_FILE in "patches/"*".patch"
do
    patch -p0 < "${PATCH_FILE}"
done

find "${DIST_DIR}" -name "*.orig" -type f -delete

# Rename IRQ handlers to match the RIOT-OS IRQ handlers.
# IRQ handler symbols used by the blobs can be obtained with some CLI magic:
# $ nm -g ${DIST_DIR}/radio/rail_lib/autogen/librail_release/*.a | grep IRQHandler | cut -d' ' -f3 | sort | uniq
for BLOB_FILE in "${DIST_DIR}/radio/rail_lib/autogen/librail_release/"*".a"
do
    arm-none-eabi-objcopy "${BLOB_FILE}" \
        --redefine-sym AGC_IRQHandler=isr_agc \
        --redefine-sym BUFC_IRQHandler=isr_bufc \
        --redefine-sym EMUDG_IRQHandler=isr_emudg \
        --redefine-sym EMU_IRQHandler=isr_emu \
        --redefine-sym FRC_IRQHandler=isr_frc \
        --redefine-sym FRC_PRI_IRQHandler=isr_frc_pri \
        --redefine-sym HOSTMAILBOX_IRQHandler=isr_hostmailbox \
        --redefine-sym MODEM_IRQHandler=isr_modem \
        --redefine-sym PRORTC_IRQHandler=isr_prortc \
        --redefine-sym PROTIMER_IRQHandler=isr_protimer \
        --redefine-sym RAC_RSM_IRQHandler=isr_rac_rsm \
        --redefine-sym RAC_SEQ_IRQHandler=isr_rac_seq \
        --redefine-sym RDMAILBOX_IRQHandler=isr_rdmailbox \
        --redefine-sym RFECA0_IRQHandler=isr_rfeca0 \
        --redefine-sym RFECA1_IRQHandler=isr_rfeca1 \
        --redefine-sym RFSENSE_IRQHandler=isr_rfsense \
        --redefine-sym SOFTM_IRQHandler=isr_softm \
        --redefine-sym SYNTH_IRQHandler=isr_synth \
        --redefine-sym SYSRTC_SEQ_IRQHandler=isr_sysrtc_seq
done

# Copy additional source files (such as Makefiles, utilities).
rsync -avp --ignore-existing "${SRC_DIR}/" "${DIST_DIR}"

# Cleanup.
rm -rf "${TEMP_DIR}"
