#include <Kinex/app.hpp>

int main(){
    knx::Core core(
        {1200, 900}, 
        {1.f, 1.f, 1.f, 1.f}, 
        "Core test", 
        {0.05f, 0.7f},
        false
    );

    while(core.isRunning()){
        core.update(
            empty_lambda,
            empty_lambda,
            empty_lambda,
            empty_lambda
        );
    }
}