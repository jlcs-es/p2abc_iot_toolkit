# UTIL SmartCard

include_directories(p2abc_iot_toolkit_include)

set(UTIL_SC_SRC_FILES
        p2abc_iot_toolkit_src/smartcard_common/m_adapted_API.c
        p2abc_iot_toolkit_src/smartcard_common/global_vars.c
        p2abc_iot_toolkit_src/smartcard_common/subroutines.c

        p2abc_iot_toolkit_src/smartcard_adaptor/system_funcs.c
        p2abc_iot_toolkit_src/smartcard_adaptor/crypto_util.c
        p2abc_iot_toolkit_src/smartcard_adaptor/arithmetic_util.c

        p2abc_iot_toolkit_src/smartcard_adaptee/arithmetic_implementation_v1.c
        p2abc_iot_toolkit_src/smartcard_adaptee/mini-gmp.c
        p2abc_iot_toolkit_src/smartcard_adaptee/tiny-AES128.c

        p2abc_iot_toolkit_src/mota_smartcard.c
        p2abc_iot_toolkit_src/debug.cpp
        )

set(UTIL_SC_INCLUDE_FILES
        p2abc_iot_toolkit_include/smartcard_common/defs_types.h
        p2abc_iot_toolkit_include/smartcard_common/defs_consts.h
        p2abc_iot_toolkit_include/smartcard_common/defs_errs.h
        p2abc_iot_toolkit_include/smartcard_common/defs_ins.h
        p2abc_iot_toolkit_include/smartcard_common/abc4T_types.h
        p2abc_iot_toolkit_include/smartcard_common/APDU_types.h
        p2abc_iot_toolkit_include/smartcard_common/m_adapted_API.h
        p2abc_iot_toolkit_include/smartcard_common/global_vars.h
        p2abc_iot_toolkit_include/smartcard_common/subroutines.h

        p2abc_iot_toolkit_include/smartcard_adaptor/system_funcs.h
        p2abc_iot_toolkit_include/smartcard_adaptor/crypto_util.h
        p2abc_iot_toolkit_include/smartcard_adaptor/arithmetic_util.h

        p2abc_iot_toolkit_include/smartcard_adaptee/arithmetic_implementation_v1.h
        p2abc_iot_toolkit_include/smartcard_adaptee/mini-gmp.h
        p2abc_iot_toolkit_include/smartcard_adaptee/tiny-AES128.h

        p2abc_iot_toolkit_include/mota_smartcard.h
        p2abc_iot_toolkit_include/debug.h
        ) #CLion/IDEs add header files to project only if explecitly referenced and used


add_definitions( -DUSE_MINI_GMP )


add_library(util_sc ${UTIL_SC_SRC_FILES} ${UTIL_SC_INCLUDE_FILES})