#!/bin/bash -e

# Verifies that every file in the source folder has been copied into the
# distribution folder by `build.sh`. Note that it does not check whether a
# file from the source folder has been removed from the distribution folder.

DIST_DIR=$(pwd)/dist
SRC_DIR=$(pwd)/src

# Operating system artifacts that are never part of the distribution.
EXCLUDED_NAMES=(".DS_Store" "Thumbs.db" "desktop.ini")

CHECKED=0
FAILED=0

if [ ! -d "${SRC_DIR}" ]; then
    echo "error: source folder '${SRC_DIR}' does not exist."
    exit 1
fi

if [ ! -d "${DIST_DIR}" ]; then
    echo "error: distribution folder '${DIST_DIR}' does not exist. Run build.sh first."
    exit 1
fi

# Translate the exclusion list into arguments for find.
FIND_ARGS=()

for EXCLUDED_NAME in "${EXCLUDED_NAMES[@]}"
do
    FIND_ARGS+=(! -name "${EXCLUDED_NAME}")
done

# Compare every source file with its counterpart in the distribution.
while IFS= read -r -d '' SRC_FILE
do
    REL_FILE="${SRC_FILE#"${SRC_DIR}/"}"
    DIST_FILE="${DIST_DIR}/${REL_FILE}"

    CHECKED=$((CHECKED + 1))

    if [ ! -e "${DIST_FILE}" ]; then
        echo "missing: ${REL_FILE} is not present in the distribution."
        FAILED=$((FAILED + 1))
    elif [ ! -f "${DIST_FILE}" ]; then
        echo "invalid: ${REL_FILE} is not a regular file in the distribution."
        FAILED=$((FAILED + 1))
    elif ! cmp -s "${SRC_FILE}" "${DIST_FILE}"; then
        echo "changed: ${REL_FILE} differs from the distribution."
        diff -u "${DIST_FILE}" "${SRC_FILE}" \
            --label "dist/${REL_FILE}" --label "src/${REL_FILE}" || true
        FAILED=$((FAILED + 1))
    else
        echo "ok: ${REL_FILE}"
    fi
done < <(find "${SRC_DIR}" -type f "${FIND_ARGS[@]}" -print0 | sort -z)

# Report the outcome.
if [ "${CHECKED}" -eq 0 ]; then
    echo "error: no files were found in '${SRC_DIR}'."
    exit 1
fi

if [ "${FAILED}" -gt 0 ]; then
    echo "Verified ${CHECKED} file(s), of which ${FAILED} deviate(s). The distribution is incorrect, run build.sh again."
    exit 1
fi

echo "Verified ${CHECKED} file(s). The distribution is up to date."
