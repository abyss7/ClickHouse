# Set standard, system and compiler libraries explicitly.
# This is intended for more control of what we are linking.

set (DEFAULT_LIBS "-nodefaultlibs")

if (OS_LINUX)
    # We need builtins from Clang's RT even without libcxx - for ubsan+int128.
    # See https://bugs.llvm.org/show_bug.cgi?id=16404
    if (COMPILER_CLANG)
        execute_process (COMMAND ${CMAKE_CXX_COMPILER} --print-file-name=libclang_rt.builtins-${CMAKE_SYSTEM_PROCESSOR}.a OUTPUT_VARIABLE BUILTINS_LIBRARY OUTPUT_STRIP_TRAILING_WHITESPACE)
    else ()
        set (BUILTINS_LIBRARY "-lgcc")
    endif ()

    set (DEFAULT_LIBS "${DEFAULT_LIBS} ${BUILTINS_LIBRARY} ${COVERAGE_OPTION} -lc -lm -lrt")

    message(STATUS "Default libraries: ${DEFAULT_LIBS}")
endif ()

set(CMAKE_CXX_STANDARD_LIBRARIES ${DEFAULT_LIBS})
set(CMAKE_C_STANDARD_LIBRARIES ${DEFAULT_LIBS})

# Global libraries

add_library(global-libs INTERFACE)

# Unfortunately '-pthread' doesn't work with '-nodefaultlibs'.
# Just make sure we have pthreads at all.
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(global-libs INTERFACE pthread ${CMAKE_DL_LIBS})

add_subdirectory(libs/libglibc-compatibility)
include (cmake/find_unwind.cmake)
include (cmake/find_cxx.cmake)

add_library(global-group INTERFACE)
target_link_libraries(global-group INTERFACE
    -Wl,--start-group
    $<TARGET_PROPERTY:global-libs,INTERFACE_LINK_LIBRARIES>
    -Wl,--end-group
)

link_libraries(global-group)

install(
    TARGETS global-group global-libs
    EXPORT global
)
