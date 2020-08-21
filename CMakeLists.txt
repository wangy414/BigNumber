cmake_minimum_required(VERSION 2.8)

project(BigNumber)
add_definitions(-fpermissive)
# headers
include_directories(${PROJECT_SOURCE_DIR}/
)
#sources
set(SRC_CC
    ${PROJECT_SOURCE_DIR}/main.cpp
	${PROJECT_SOURCE_DIR}/BigFloat.cpp
	${PROJECT_SOURCE_DIR}/BigFloatPowerCalc.cpp
	${PROJECT_SOURCE_DIR}/BigInt.cpp
)


link_directories(${PROJECT_SOURCE_DIR})
add_executable(BigNumber ${SRC_CC})
target_link_libraries(BigNumber -lstdc++)
