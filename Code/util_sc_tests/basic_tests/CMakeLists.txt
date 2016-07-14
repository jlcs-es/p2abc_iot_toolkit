include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(runBasicTests
        random_numbers_check.cpp
        )

target_link_libraries(runBasicTests gtest gtest_main)
target_link_libraries(runBasicTests util_sc)