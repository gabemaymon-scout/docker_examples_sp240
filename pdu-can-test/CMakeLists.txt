cmake_minimum_required(VERSION 3.10)
project(pdu_toggle_project C)

# Define your executable target by bundling your C code and the core driver source
add_executable(pdu_toggle 
    pdu_toggle.c 
    /tmp-libcsp/src/drivers/can/can_socketcan.c
)

# Add standard include directories for tracking all internal header headers
target_include_directories(pdu_toggle PRIVATE 
    /usr/local/include 
    /tmp-libcsp/src
)

# Link using system targets
target_link_libraries(pdu_toggle 
    csp 
    socketcan 
    pthread
)
