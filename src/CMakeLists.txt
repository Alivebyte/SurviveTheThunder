file(GLOB SOURCE_CODE
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(SpaceShift
	${SOURCE_CODE})
	
target_include_directories(SpaceShift PRIVATE "${CMAKE_SOURCE_DIR}/olcPixelGameEngine")
target_include_directories(SpaceShift PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(SpaceShift PRIVATE "${CMAKE_SOURCE_DIR}/lib/freetype.lib")