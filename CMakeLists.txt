# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

# Tell ESP-IDF to treat hf-hal and threads as extra components
set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/hf-hal
    ${CMAKE_CURRENT_LIST_DIR}/hf-hal/utils-and-drivers/hf-core-drivers/external
    ${CMAKE_CURRENT_LIST_DIR}/hf-hal/utils-and-drivers/hf-core-drivers/external/hf-ws2812-rmt-driver
    ${CMAKE_CURRENT_LIST_DIR}/threads
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# "Trim" the build. Include the minimal set of components, main, and anything it
# depends on.
idf_build_set_property(MINIMAL_BUILD ON)

project(HardFOC)
