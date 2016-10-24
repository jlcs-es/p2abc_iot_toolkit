# Code

The source code is organized in several directories.
- util_sc_tests/ contains basic_tests/ and lib/ with the googletest framework.
- util_sc/ contains the implementation of C smartcard and p2abc IoT toolkit.
  + A CMakeLists.txt file defines it as a library, and organizes the code in three main categories:
    * common: Pure C code that implements the smart card functionality and is platform independent with IoT systems in mind. Relies on the adaptors, interfaces to external utilities that are not standard in IoT and may need custom implementations.
    * adaptor: Interfaces (.h) to functions that not all IoT devices can provide, like standard libraries or cryptography utilities (some may have HW implementations, some SW, some none). The source files (.c) are the implementations of the interfaces, and **are the files to be modified** when porting the toolkit to new systems.
    * adaptee: Usually the adaptor .c files won't implement everything from scratch, and simply rely on other external libraries, the adaptees, which files should be copied in the adaptee directories. These directories **are the ones to be modified** when porting the toolkit to new systems.


In summary, to port the implementation, change the .c adaptor files and adaptee directories.

This file was written before the implementation of the main process that will handle how the smartcard works in a system, so things may change in the future.
