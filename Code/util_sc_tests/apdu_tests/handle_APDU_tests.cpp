#include <gtest/gtest.h>

#include <smartcard_common/global_vars.h>
#include <smartcard_common/APDU_handler.h>
#include <smartcard_common/defs_ins.h>
#include <smartcard_common/subroutines.h>
#include <smartcard_utils_interface/sc_status_io_util.h>


TEST(test_INS_PIN_TRIALS_LEFT, test1) {
    BYTE pin1[] = {0x12, 0x34, 0x56, 0x78};
    BYTE pin2[] = {0xff, 0xee, 0xdd, 0xcc};
    memcpy(pin, pin1, PIN_SIZE);

    // Set the APDU
    CLA = 0xBC; INS = INS_PIN_TRIALS_LEFT; P1=0; P2=0; Le=1; La=0; SW1=0x90; SW2=0x00; APDU_Case=2;
    mode=MODE_ROOT; pin_trials = 2; json_file = "./status.json";

    ::testing::internal::CaptureStderr();
    handle_APDU();
    std::string output = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("029000\n", output);

    Le=0; La=0; SW1=0x90; SW2=0x00;

    // insert wrong pin
    ::testing::internal::CaptureStderr();
    checkPin(pin2);
    output = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("9f03\n", output);

    Le=1; La=0; SW1=0x90; SW2=0x00;

    ::testing::internal::CaptureStderr();
    handle_APDU();
    output = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("019000\n", output);

    Le=0; La=0; SW1=0x90; SW2=0x00;
    // insert wrong pin
    ::testing::internal::CaptureStderr();
    checkPin(pin2);
    output = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("9f04\n", output);

    Le=1; La=0; SW1=0x90; SW2=0x00;

    ::testing::internal::CaptureStderr();
    handle_APDU();
    output = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("009000\n", output);
}
