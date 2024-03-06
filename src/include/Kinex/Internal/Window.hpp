#pragma once
#include <Kinex/init.hpp>
#include "Event.hpp"

namespace knx{
    namespace irl{
        namespace __internal{
            static queue<Event> GLOBAL_EVENTS;
            static vec2f GLOBAL_MOUSE_POSITION;
            void _key_callback(GLFWwindow *window, int key, int scancode, int action, int mode){
                GLOBAL_EVENTS.push(Event(
                    action == GLFW_PRESS ? KEY_PRESSED_ : KEY_RELEASED_,
                    key
                ));
            }
            void _mouse_callback(GLFWwindow* window, double xpos, double ypos){
                GLOBAL_MOUSE_POSITION = vec2f{(float)xpos, (float)ypos};
                GLOBAL_EVENTS.push(Event(
                    MOUSE_MOVED_,
                    vec2f{(float)xpos, (float)ypos}
                ));
            }
            void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
                GLOBAL_EVENTS.push(Event(
                    MOUSE_SCROLL_,
                    (float)yoffset
                ));
            }
            void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
                GLOBAL_EVENTS.push(Event(
                    action == GLFW_PRESS ? MOUSE_PRESSED_ : MOUSE_RELEASED_,
                    (float)button
                ));
            }
        }

        class Window{
            private:
            
            void glfw_init(
                int minor_opengl_ver = 3,
                int major_opengl_ver = 4
            ){
                glfwInit();
                
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_opengl_ver);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_opengl_ver);

                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            }
            
            GLFWkeyfun key_callback = __internal::_key_callback;
            GLFWcursorposfun mouse_callback = __internal::_mouse_callback;
            GLFWscrollfun scroll_callback = __internal::_scroll_callback;
            GLFWmousebuttonfun button_callback = __internal::_mouse_button_callback;
            GLFWwindow *window = nullptr;

            string name;
            vec2i res;
            vec4f bg_clr;
            int tick = 0;
            float deltaTime = 0.f;

            int frames = 0;
            float time = 0;
            int FPS;
            adc::chrono_tpoint_t begin;

            public:

            GLFWwindow *getWindow(){return window; }
            const vec2f getResolution(){ return {(float)res.x, (float)res.y};}
            const vec4f &getBackgroundColor(){ return bg_clr; }
            const int &getTick(){ return tick; }
            const string &getTitle(){ return name; }
            const int &getFPS(){ return FPS; }

            const vec2f &getMousePosition(){return __internal::GLOBAL_MOUSE_POSITION;}

            Window(
                string name,
                vec2i res,
                vec4f bg_clr 
            ): name(name), res(res), bg_clr(bg_clr){
                glfw_init();
                window = glfwCreateWindow(res.x, res.y, name.c_str(), nullptr, nullptr);

                if (window==nullptr){
                    glfwTerminate();
                    throw runtime_error("Failed to create GLFW window");
                }
                glfwMakeContextCurrent(window);

                glewExperimental = GL_TRUE;
                if (glewInit() != GLEW_OK){
                    throw runtime_error("Failed to initialize GLEW");
                }

                glfwGetFramebufferSize(window, &res.x, &res.y);
                glViewport(0, 0, res.x, res.y);
                glClearColor(bg_clr.x, bg_clr.y, bg_clr.z, bg_clr.w);

                glEnable(GL_DEPTH_TEST);

                glfwSetKeyCallback(window, this->key_callback);
                glfwSetCursorPosCallback(window, this->mouse_callback);
                glfwSetScrollCallback(window, this->scroll_callback);
                glfwSetMouseButtonCallback(window, this->button_callback);
            }

            float getDeltatime(){
                return deltaTime/1000.f;
            }
            void setKeyCallback(GLFWkeyfun callback){
                this->key_callback = callback;
                glfwSetKeyCallback(window, this->key_callback);
            }
            void setMouseCallback(GLFWcursorposfun callback){
                this->mouse_callback = callback;
                glfwSetCursorPosCallback(window, this->mouse_callback);
            }
            void setScrollCallback(GLFWscrollfun callback){
                this->scroll_callback = callback;
                glfwSetScrollCallback(window, this->scroll_callback);
            }
            void setButtonCallback(GLFWmousebuttonfun callback){
                this->button_callback = callback;
                glfwSetMouseButtonCallback(window, this->button_callback);
            }
            void setClearColor(vec4f bg_clr){
                this->bg_clr = bg_clr;
                glClearColor(this->bg_clr.x, this->bg_clr.y, this->bg_clr.z, this->bg_clr.w);
            }
            void hideCursor(){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
            void showCursor(){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            void moveCursorTo(vec2i pos){
                glfwSetCursorPos(window, pos.x, pos.y);
            }

            bool isOpen(){
                return !glfwWindowShouldClose(window);
            }

            void run(
                function<void()> drawFunc,
                function<void()> updateFunc,
                function<void()> preDrawFunc,
                function<void()> postDrawFunc
            ){
                while(isOpen()){
                    
                    if(time >= 1000){
                        FPS = frames;
                        glfwSetWindowTitle(window, (name + " | FPS: " + to_string(frames)).c_str());
                        time = 0; frames = 0;
                    }

                    begin = getChornoTimeNow();

                    pollEvents();
                    update(drawFunc, updateFunc, preDrawFunc, postDrawFunc);
                    swap();
                }
            }

            void pollEvents(){
                glfwPollEvents();
            }

            void update(function<void()> drawFunc,
                        function<void()> updateFunc,
                        function<void()> preDrawFunc,
                        function<void()> postDrawFunc){
                if(time >= 1000){
                    FPS = frames;
                    glfwSetWindowTitle(window, (name + " | FPS: " + to_string(FPS)).c_str());
                    time = 0; frames = 0;
                }
                begin = getChornoTimeNow();
                preDrawFunc();
                glEnable(GL_DEPTH_TEST);
                    glClearColor(bg_clr.x, bg_clr.y, bg_clr.z, bg_clr.w);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    updateFunc();
                    drawFunc();
                glDisable(GL_DEPTH_TEST);
                postDrawFunc();
            }

            void swap(){
                glfwSwapBuffers(window);
                deltaTime = getChronoElapsed(begin);
                time += deltaTime;
                tick++;
                frames++;
            }

            void terminate(){
                glfwTerminate();
            }

            Window(){;}
            ~Window(){}
        };
    }
}