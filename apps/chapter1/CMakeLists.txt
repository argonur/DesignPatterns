project ("chapter1" VERSION "0.1" LANGUAGES CXX)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
	PRIVATE
		"src/ducks.cpp"
)
