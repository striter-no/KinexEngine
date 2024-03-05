#pragma once
#include "AdtClasses.hpp"
#include <thread>
#include <mutex>
#include <variant>

namespace nsc{
using namespace adc;

template<class RT, class... Args>
function<void(RT*, Args...)> getWrapped(function<RT(Args...)> func ){
    return [func](RT* result, Args... args) {
        (*result) = func(args...);
    };
}

template<class RT, class... Args>
function<void(RT*, Args...)> getLockingWrapped(function<RT(Args...)> func, mutex *tmutex){
    return [func, tmutex](RT* result, Args... args) {
        tmutex->lock();
        (*result) = func(args...);
        tmutex->unlock();
    };
}

template<class T>
function<void(vector<T>&, vector<T>&)> makeLocking(function<void(vector<T>&, vector<T>&)> func, mutex *tmutex){
    return [func, tmutex](vector<T>& iv, vector<T>& ov) {
        tmutex->lock();
        func(iv, ov);
        tmutex->unlock();
    };
}

template<class... Args>
function<char(Args...)> getVoidWrapped(function<void(Args...)> func) {
    return [func](Args... args) -> char {
        func(args...);
        return {0};
    };
}

template<class RT, class... Args>
class future{
    private:
    std::thread* this_thread;
    function<RT(Args...)> func;
    function<void(RT*, Args...)> wrapped;
    function<void(RT*, Args...)> wrapped_locking;
    mutex this_mutex;

    RT output;

    bool is_locking = false,
         is_deffered = false;

    public:
    
    future(function<RT(Args...)> func, Args... args, bool is_locking = false, bool is_deffered = false) : 
            func(func), is_locking(is_locking), is_deffered(is_deffered)
    {
        if(!is_deffered){
        if(!is_locking){
            wrapped = getWrapped<RT, Args...>(func);
            this_thread = new std::thread(wrapped, &output, args...);
        } else {
            wrapped_locking = getLockingWrapped<RT, Args...>(func, &this_mutex);
            this_thread = new std::thread(wrapped_locking, &output, args...);
        }
        }
    }
    future(){;}

    RT get(Args... args){
        if(is_deffered){
            if(!is_locking){
                wrapped = getWrapped<RT, Args...>(func);
                this_thread = new std::thread(wrapped, &output, args...);
            } else {
                wrapped_locking = getLockingWrapped<RT, Args...>(func, &this_mutex);
                this_thread = new std::thread(wrapped_locking, &output, args...);
            }
        }
        
        this_thread->join();
        return output;
    }

    RT getDetach(Args... args){
        if(is_deffered){
            if(!is_locking){
                wrapped = getWrapped<RT, Args...>(func);
                this_thread = new std::thread(wrapped, &output, args...);
            } else {
                wrapped_locking = getLockingWrapped<RT, Args...>(func, &this_mutex);
                this_thread = new std::thread(wrapped_locking, &output, args...);
            }
        }
        
        this_thread->detach();
        return output;
    }

    ~future() {
        if(this_thread->joinable()) this_thread->detach();
        delete this_thread;
    }
};

template<class T>
class _queue{
    private:
    std::thread* this_thread;
    std::mutex this_mutex;
    vector<T> &input;
    vector<T> &output;
    function<void(vector<T>&, vector<T>&)> async_handler;

    public:
    
    _queue(vector<T> &input, vector<T> &output, function<void(vector<T>&, vector<T>&)> async_handler):
           input(input), output(output), async_handler(async_handler){
        async_handler = makeLocking(async_handler, &this_mutex);
        this_thread = new std::thread(async_handler, std::ref(input), std::ref(output));
    }

    void run_detached(){ this_thread->detach(); }
    void wait_until_done(){ this_thread->join(); }

    _queue(){;}

    ~_queue(){
        if (this_thread->joinable()) {
            this_thread->detach();
        }
        delete this_thread;
    }
};

class async{
    public:
    template<class RT, class... Args>
    nsc::future<RT> static call(RT(*func)(Args...), Args... args){
        return nsc::future<RT>((function<RT(Args...)>)func, args...);
    }

    template<class... Args>
    nsc::future<char> static call(void(*func)(Args...), Args... args){
        return nsc::future<char>(getVoidWrapped((function<void(Args...)>)func), args...);
    }
    
    template<class RT, class... Args>
    nsc::future<RT> static lock_call(RT(*func)(Args...), Args... args){
        return nsc::future<RT>((function<RT(Args...)>)func, args..., true);
    }

    template<class... Args>
    nsc::future<char> static vlock_call(void(*func)(Args...), Args... args){
        return nsc::future<char>(getVoidWrapped((function<void(Args...)>)func), args..., true);
    }
    
    template<class RT, class... Args>
    nsc::future<RT> static deffered_call(RT(*func)(Args...), Args... args){
        return nsc::future<RT>((function<RT(Args...)>)func, args..., false, true);
    }

    template<class... Args>
    nsc::future<char> static deffered_call(void(*func)(Args...), Args... args){
        return nsc::future<char>(getVoidWrapped((function<void(Args...)>)func), args..., false, true);
    }

    template<class RT, class... Args>
    nsc::future<RT> static deffered_lock_call(RT(*func)(Args...), Args... args){
        return nsc::future<RT>((function<RT(Args...)>)func, args..., true, true);
    }

    template<class... Args>
    nsc::future<char> static deffered_lock_call(void(*func)(Args...), Args... args){
        return nsc::future<char>(getVoidWrapped((function<void(Args...)>)func), args..., true, true);
    }

    template<class T>
    nsc::_queue<T> static create_queue(vector<T> &input, vector<T> &output, function<void(vector<T>&, vector<T>&)> async_handler){
        return nsc::_queue(input, output, async_handler);
    }
};
}