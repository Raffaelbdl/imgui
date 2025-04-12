add_library(imgui 
    imgui_demo.cpp
    imgui_draw.cpp
    backends/imgui_impl_sdl3.cpp
    backends/imgui_impl_opengl3.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    misc/cpp/imgui_stdlib.h misc/cpp/imgui_stdlib.cpp

    #imgui_curve_editor
    extensions/imgui_curve.h extensions/imgui_curve.cpp

    # imgui_node_editor
    extensions/imgui_node_editor/crude_json.cpp
    extensions/imgui_node_editor/crude_json.h
    extensions/imgui_node_editor/imgui_bezier_math.h
    extensions/imgui_node_editor/imgui_bezier_math.inl
    extensions/imgui_node_editor/imgui_canvas.cpp
    extensions/imgui_node_editor/imgui_canvas.h
    extensions/imgui_node_editor/imgui_extra_math.h
    extensions/imgui_node_editor/imgui_extra_math.inl
    extensions/imgui_node_editor/imgui_node_editor_api.cpp
    extensions/imgui_node_editor/imgui_node_editor_internal.h
    extensions/imgui_node_editor/imgui_node_editor_internal.inl
    extensions/imgui_node_editor/imgui_node_editor.cpp
    extensions/imgui_node_editor/imgui_node_editor.h

    # imnodes
    extensions/imnodes/imnodes_internal.h
    extensions/imnodes/imnodes.cpp
    extensions/imnodes/imnodes.h

    imgui.cpp
    imgui.h
    )
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ ${CMAKE_CURRENT_LIST_DIR}/backends/ ${CMAKE_CURRENT_LIST_DIR}/misc/cpp/ ${CMAKE_CURRENT_LIST_DIR}/extensions/)

find_package(OpenGL REQUIRED) # OpenGL::GL
target_link_libraries(imgui SDL3::SDL3 OpenGL::GL)