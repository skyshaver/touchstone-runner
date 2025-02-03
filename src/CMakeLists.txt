cmake_minimum_required (VERSION 3.25)

project("touchstone-runner")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/../build/bin/)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE PATH "" FORCE)

include_directories(../)
 
#Open CV
find_package(OpenCV CONFIG REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# fmt
# find_package(fmt CONFIG REQUIRED)

# Dear ImGui
# set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/../imgui/)
set(IMGUI_DIR "C:/imgui/")
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

# need to change import of imgui.h in implot.h to be relative to imgui parent directory
#set(IMPLOT_DIR "C:/imgui/implot/")
# include_directories(${IMPLOT_DIR})


set(all_file
  "main.cpp"  
  ${IMGUI_DIR}/backends/imgui_impl_win32.cpp 
  ${IMGUI_DIR}/backends/imgui_impl_dx12.cpp   
  ${IMGUI_DIR}/imgui.cpp 
  ${IMGUI_DIR}/imgui_draw.cpp 
  ${IMGUI_DIR}/imgui_demo.cpp 
  ${IMGUI_DIR}/imgui_tables.cpp 
  ${IMGUI_DIR}/imgui_widgets.cpp
 )

add_executable (touchstone-runner ${all_file})

target_link_libraries(touchstone-runner PRIVATE 		
	${OpenCV_LIBS}
	d3d12.lib
	dxgi.lib
	d3dcompiler.lib
)