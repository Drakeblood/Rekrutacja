project(TicketMachine VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE INCLUDES "include/*.h")
file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable(TicketMachine ${SOURCES} ${INCLUDES})

target_include_directories(TicketMachine PRIVATE include/TicketMachine)
target_include_directories(TicketMachine PUBLIC include)

