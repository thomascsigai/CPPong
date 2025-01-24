cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CPPong")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable (CPPong "src/EntryPoint.cpp" "src/Paddle.cpp" "include/utils/Timer.cpp" "src/Ball.cpp" "include/utils/Texture.h" "include/utils/Texture.cpp" "include/utils/UserEvents.h")
target_include_directories(CPPong PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include/utils")

target_link_libraries(CPPong PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_ttf::SDL2_ttf)

# Copy SDL2.dll that exists in base project folder
# If it does not exist, find it in your SDL2 folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2.dll not found in project base directory.")
endif()

# Copy SDL2_ttf.dll that exists in base project folder
# If it does not exist, find it in your SDL2_ttf folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2_ttf.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2_ttf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2_ttf.dll not found in project base directory.")
endif()

# Copy Ressources directory to binary dir
if (EXISTS ${CMAKE_SOURCE_DIR}/resources)
	file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(TRACE "No resources directory found.")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPPong PROPERTY CXX_STANDARD 20)
endif()