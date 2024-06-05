set(CMAKE_CXX_STANDARD 20)

file(GLOB app
	"*.cpp"
)

add_executable(RoboCrawler ${app})