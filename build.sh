#!/bin/bash -e

GECKO_SDK_VERSION="com.silabs.sdk.gecko_platform.v2.0.feature_root_2.0.0.201710261808-100"
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
rsync -avp "${TEMP_DIR}/gecko_sdk/developer/sdks/gecko_sdk_suite/v2.0/platform/emlib" "${DIST_DIR}"
rsync -avp "${TEMP_DIR}/gecko_sdk/developer/sdks/gecko_sdk_suite/v2.0/platform/radio" "${DIST_DIR}"

rm "${DIST_DIR}/emlib/src/em_int.c"
rm "${DIST_DIR}/emlib/inc/em_int.h"

rm "${DIST_DIR}/radio/rail_lib/modules.xml"
rm -rf "${DIST_DIR}/radio/rail_lib/apps"
rm -rf "${DIST_DIR}/radio/rail_lib/hal"
rm -rf "${DIST_DIR}/radio/rail_lib/plugin"

find "${DIST_DIR}" -name "*.c" -type f -exec dos2unix -k -s -o {} ';'
find "${DIST_DIR}" -name "*.h" -type f -exec dos2unix -k -s -o {} ';'

sed -i "s/Fall through and select clock source/fallthrough/g" "${DIST_DIR}/emlib/src/em_cmu.c"

rsync -avp --ignore-existing "${SRC_DIR}/" "${DIST_DIR}"

# Cleanup.
rm -rf "${TEMP_DIR}"
