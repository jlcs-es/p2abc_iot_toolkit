# UTIL_SC

include_directories(include_util_sc)

set(UTIL_SC_SRC_FILES
        src_util_sc/crypto_help.c
)

set(UTIL_SC_INCLUDE_FILES
        include_util_sc/crypto_help.h
) #CLion adds h files to project only if explecitly referenced and used


add_library(util_sc ${UTIL_SC_SRC_FILES} ${UTIL_SC_INCLUDE_FILES})