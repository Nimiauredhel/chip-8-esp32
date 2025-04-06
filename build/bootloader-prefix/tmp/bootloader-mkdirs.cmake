# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mickey/esp/esp-idf/components/bootloader/subproject"
  "/home/mickey/Repos/chip-8-esp32/build/bootloader"
  "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix"
  "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix/tmp"
  "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix/src/bootloader-stamp"
  "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix/src"
  "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mickey/Repos/chip-8-esp32/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
