# CMakeList.txt: проект CMake для ElectroCounters; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

find_package(unofficial-libmysql REQUIRED)

find_package(Poco REQUIRED COMPONENTS Util Net DataMySQL)

include_directories(survey)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ElectroCounters "ElectroCounters.cpp" "survey/Surveable.cpp" "survey/protocols/CC301_1/CC301_1.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ElectroCounters PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
target_link_libraries(ElectroCounters PRIVATE Poco::Util Poco::Net Poco::DataMySQL)
