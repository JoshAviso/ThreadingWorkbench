# CMakeList.txt : CMake project for ThreadingWorkbench, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Add static runtime DLLs on build
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>DLL") 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>DLL") 

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ThreadingWorkbench")

# Change output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set base path for 3rd party ref projects
include(FetchContent)

# Set directory for 3rd party stuff
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty CACHE PATH "Base Directory if libs" FORCE)

# Set asset directory
set(RESOURCES_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Media CACHE PATH "Base Directory of resources" FORCE)

# Set project source directory
set(PROJ_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src CACHE PATH "Project SRC" FORCE)

# Add everything in source directory
file(GLOB_RECURSE PROJ_SRC CONFIGURE_DEPENDS "${PROJ_SRC_PATH}/*.[ch]pp")

FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable (ThreadingWorkbench "${PROJ_SRC}" "ThreadingWorkbench.cpp" "ThreadingWorkbench.h" "src/IWorkerAction.h")

# add_executable (ThreadingWorkbench "${PROJ_SRC}" "Test.cpp" "ThreadingWorkbench.h")

# Change C++ target ver to 20
target_compile_features(ThreadingWorkbench PRIVATE cxx_std_20)

# Link SFML graphics lib
target_link_libraries(ThreadingWorkbench PRIVATE sfml-graphics)

add_custom_command(
	TARGET ThreadingWorkbench POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/Media 
			${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Media
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThreadingWorkbench PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
