#pragma once
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>

namespace knx{

    class Input{
        irl::Window *window;

        map<
            string, // name
            pair<EVENTS_TYPE, function<void(irl::Event)>> // type, function
        > keybinds;

        vec2f fixCursorPos;
        bool b_fixCursor = false;
        bool focus = false;

        public:

        void registrateAction(string name, pair<EVENTS_TYPE, function<void(irl::Event)>> action){ keybinds[name] = action; }
        bool isActionExists(string name){ return keybinds.find(name) != keybinds.end(); }
        bool isKeyPressed(int key){return glfwGetKey(window->getWindow(), key); }
        bool isWindowInFocus(){return focus;}

        float getAxisX(){
            if(isKeyPressed(GLFW_KEY_A) || isKeyPressed(GLFW_KEY_LEFT))  {return -1;}
            if(isKeyPressed(GLFW_KEY_D) || isKeyPressed(GLFW_KEY_RIGHT)) {return 1;}
            return 0;
        }

        float getAxisY(){
            if(isKeyPressed(GLFW_KEY_Q)) {return -1;}
            if(isKeyPressed(GLFW_KEY_E)) {return 1;}
            return 0;
        }

        float getCursorAxisX(bool fromCenter = false){
            if(fromCenter) return window->getMousePosition().x - window->getResolution().x / 2;
            return window->getMousePosition().x;
        }

        float getCursorAxisY(bool fromCenter = false){
            if(fromCenter) return window->getMousePosition().y - window->getResolution().y / 2;
            return window->getMousePosition().y;
        }


        float getAxisZ(){
            if(isKeyPressed(GLFW_KEY_W) || isKeyPressed(GLFW_KEY_UP)) { return -1;}
            if(isKeyPressed(GLFW_KEY_S) || isKeyPressed(GLFW_KEY_DOWN)) { return 1; }
            return 0;
        }

        void hideCursor(){
            focus = true;
            window->hideCursor();
        }

        void showCursor(){
            focus = false;
            window->showCursor();
        }

        void fixCursor(vec2f pos){
            // focus = true;
            fixCursorPos = pos;
            b_fixCursor = true;
        }

        void freeCursor(){
            // focus = true;
            b_fixCursor = false;
        }

        void update(){
            if(b_fixCursor){
                window->moveCursorTo(vec2f_ti(fixCursorPos));
            }
            while(!irl::__internal::GLOBAL_EVENTS.isEmpty()){
                irl::Event event = irl::__internal::GLOBAL_EVENTS.pop();
                for(auto &keybind : keybinds){
                    if(keybind.second.second && 
                       event.type == keybind.second.first){
                        keybind.second.second(event);
                    }
                }
            }
        }

        Input(irl::Window *window): window(window) {
            ;
        }

        Input(){}
        ~Input(){}
    };
};