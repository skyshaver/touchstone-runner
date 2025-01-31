cmake_minimum_required (VERSION 3.30)

project("touchstone-runner")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/../build/bin/)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE PATH "" FORCE)

include_directories(../)
 
# GLFW
find_package(glfw3 CONFIG REQUIRED)

# fmt
# find_package(fmt CONFIG REQUIRED)

# Dear ImGui
# set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/../imgui/)
set(IMGUI_DIR "C:/imgui/")
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

# need to change import of imgui.h in implot.h to be relative to imgui parent directory
#set(IMPLOT_DIR "C:/imgui/implot/")
# include_directories(${IMPLOT_DIR})

# Libraries
set(LIBRARIES "glfw")

set(all_file
  "main.cpp"
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp 
  ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp 
  ${IMGUI_DIR}/imgui.cpp 
  ${IMGUI_DIR}/imgui_draw.cpp 
  ${IMGUI_DIR}/imgui_demo.cpp 
  ${IMGUI_DIR}/imgui_tables.cpp 
  ${IMGUI_DIR}/imgui_widgets.cpp
 )

add_executable (touchstone-runner ${all_file})

target_link_libraries(touchstone-runner PRIVATE 	
	glfw	
)