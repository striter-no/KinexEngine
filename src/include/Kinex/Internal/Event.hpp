#pragma once
#include <Kinex/init.hpp>

namespace knx::irl{
    class Event{
        bool v_isActive = true;
        bool v_isCalled = false;
        

        KEYBOARD_EVENTS keyboard_event;
        MOUSE_EVENTS mouse_event;
        WINDOW_EVENTS window_event;

        public:
        
        int key = -1;
        int mouseButton = -1;
        int scroll = -1;
        EVENTS_TYPE type;
        vec2f mousePos = -1.f;

        const int getCode() const {
            switch(type){
                case EVENTS_TYPE::KEYBOARD_EVENT_:
                    return (int)keyboard_event;
                case EVENTS_TYPE::MOUSE_EVENT_:
                    return (int)mouse_event;
                case EVENTS_TYPE::WINDOW_EVENT_:
                    return (int)window_event;
            }
            return -1;
        }

        void setEvent(EVENTS_TYPE type, int code){
            this->type = type;
            switch(type){
                case EVENTS_TYPE::KEYBOARD_EVENT_:
                    keyboard_event = (KEYBOARD_EVENTS)code;
                case EVENTS_TYPE::MOUSE_EVENT_:
                    mouse_event = (MOUSE_EVENTS)code;
                case EVENTS_TYPE::WINDOW_EVENT_:
                    window_event = (WINDOW_EVENTS)code;
            }
        }

        bool isActive(){ return v_isActive; }
        bool isCalled(){ return v_isCalled; }
        void callThis(){ v_isCalled = true; }
        void setActive(bool active){ v_isActive = active; }
        
        Event(KEYBOARD_EVENTS keyboard_event, int key): type(EVENTS_TYPE::KEYBOARD_EVENT_), keyboard_event(keyboard_event), v_isCalled(true), key(key) {}
        Event(MOUSE_EVENTS mouse_event, float data): 
            type(EVENTS_TYPE::MOUSE_EVENT_), 
            mouse_event(mouse_event), 
            v_isCalled(true) {
            if(mouse_event == MOUSE_SCROLL_){
                scroll = data;
            } else {
                mouseButton = (int)data;
            }
        }
        Event(MOUSE_EVENTS mouse_event, vec2f pos): 
            type(EVENTS_TYPE::MOUSE_EVENT_), 
            mouse_event(mouse_event), 
            v_isCalled(true) {
            mousePos = pos;
        }
        Event(WINDOW_EVENTS window_event): type(EVENTS_TYPE::WINDOW_EVENT_), window_event(window_event), v_isCalled(true) {}

        Event(EVENTS_TYPE type): type(type), v_isCalled(false) {}
        Event(): type(EVENTS_TYPE::NONE_EVENT_), v_isCalled(false) {}
        ~Event(){}

    };
}