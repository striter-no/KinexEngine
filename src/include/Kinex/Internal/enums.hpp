#pragma once
namespace knx{
    
    enum MESH_TYPE{
        ONLY_VERTEXES,
        VERTEX_NORMALS,
        VERTEX_TEXTURES,
        VERTEX_NORMALS_TEXTURES,
    };

    enum TEXTURE_TYPE{
        STANDART_GL_TEXTURE,
        EMPTY_GL_TEXTURE,
        DATA_TEXTURE,
        GL_DATA_TEXTURE,
        PTR_DATA_TEXTURE
    };

    enum OBJECT_TYPE{
        RAW_OBJECT,
        MESH_OBJECT,
        MESH_TEXTURES_OBJECT,
        OPTIMIZED_OBJECT,
        OPTIMIZED_TEXTURED_OBJECT
    };

    enum EVENTS_TYPE{
        KEYBOARD_EVENT_,
        MOUSE_EVENT_,
        WINDOW_EVENT_,
        NONE_EVENT_
    };

    enum KEYBOARD_EVENTS{
        KEY_PRESSED_,
        KEY_RELEASED_
    };

    enum MOUSE_EVENTS{
        MOUSE_MOVED_,
        MOUSE_PRESSED_,
        MOUSE_RELEASED_,
        MOUSE_SCROLL_
    };

    enum WINDOW_EVENTS{
        WINDOW_RESIZED_,
        WINDOW_CLOSED_,
        WINDOW_FOCUSED_,
        WINDOW_LOST_FOCUS_,
        WINDOW_MOVED_
    };

    enum LIGHT_TYPE{
        DIRECTION_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT
    };
}