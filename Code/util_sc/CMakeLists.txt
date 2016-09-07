# UTIL SmartCard

include_directories(include_util_sc)

set(UTIL_SC_SRC_FILES
        m_adapted_API.c
        mota_smartcard.c
        subroutines.c
        system_funcs.c
        global_vars.c
        crypto_util.c
        big_integer_arithmetic.c)

set(UTIL_SC_INCLUDE_FILES
        include_util_sc/defs_types.h
        include_util_sc/defs_consts.h
        include_util_sc/defs_errs.h
        include_util_sc/defs_ins.h
        include_util_sc/abc4T_types.h
        include_util_sc/APDU_types.h
        include_util_sc/m_adapted_API.h
        include_util_sc/mota_smartcard.h
        include_util_sc/subroutines.h
        include_util_sc/system_funcs.h
        include_util_sc/global_vars.h
        include_util_sc/crypto_util.h
        include_util_sc/big_integer_arithmetic.h
        ) #CLion/IDEs add header files to project only if explecitly referenced and used


add_library(util_sc ${UTIL_SC_SRC_FILES} ${UTIL_SC_INCLUDE_FILES})