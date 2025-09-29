project(opengametools CXX)

set(APPS
    apps/vox2fbx.cpp
    apps/vox2obj.cpp
    apps/voxmerge.cpp
    apps/voxseparate.cpp
    demo/demo_vox.cpp
    demo/tests.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

foreach (app ${APPS})
    get_filename_component(APP_NAME ${app} NAME_WE)
    add_executable(${APP_NAME} ${app})
    target_compile_options(${APP_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    )
    install(TARGETS ${APP_NAME} DESTINATION bin)
endforeach()

include(CTest)
add_test(NAME test_multiple_model_scene COMMAND $<TARGET_FILE:demo_vox> ${CMAKE_CURRENT_SOURCE_DIR}/demo/vox/test_multiple_model_scene.vox)

add_test(NAME tests COMMAND $<TARGET_FILE:tests> WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/demo/vox)
