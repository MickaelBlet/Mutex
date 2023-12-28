set(library_project_name "${PROJECT_NAME}")

set(example_files
    "${CMAKE_CURRENT_SOURCE_DIR}/quickstart.cpp"
)

foreach(file ${example_files})
    get_filename_component(filenamewe "${file}" NAME_WE)
    add_executable("${filenamewe}.example" "${file}")
    set_target_properties("${filenamewe}.example"
        PROPERTIES
            CXX_STANDARD "${CMAKE_CXX_STANDARD}"
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            NO_SYSTEM_FROM_IMPORTED ON
            COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
            LINK_LIBRARIES "${library_project_name};pthread"
    )
endforeach()