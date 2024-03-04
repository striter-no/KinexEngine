#pragma once
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>

namespace knx{
    class Time{
        map<string, adc::chrono_tpoint_t> timers;
        irl::Window *window = nullptr;

        public:

        int getCurrentFPS(){
            return window->getFPS();
        }

        float getDeltaTime(){
            return window->getDeltatime();
        }

        long long getTicksFromStart(){
            return window->getTick();
        }

        void startTimer(string name){
            timers[name] = adc::getChornoTimeNow();
        }
        float getTimerState(string name){
            return getChronoElapsed(timers[name]);
        }
        float endTimer(string name){
            float val = getTimerState(name);
            timers.erase(name);
            return {val};
        }

        bool isTimerExists(string name){
            return timers.find(name) != timers.end();
        }

        Time(irl::Window *window): window(window) {}
        Time(){}
        ~Time(){}
    };
}