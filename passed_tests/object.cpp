#include <Kinex/app.hpp>

int main(){
    knx::Core core(
        {1200, 900}, 
        {0.0f, 0.0f, 0.0f, 1.0f}, 
        "Object test", 
        {0.05f, 0.7f},
        false
    );
    core.setupCamera({{0.f, 0.f, 0.f}}, 50, 0.25f, 0.1f, 5000.f);

    core.getInputSystem().registrateAction("cursorModes", 
        {knx::MOUSE_EVENT_, [&](const knx::irl::Event &event){ if((knx::MOUSE_EVENTS)event.getCode() == knx::MOUSE_PRESSED_){
            if(event.mouseButton == 0){
                core.getInputSystem().hideCursor();
                core.getInputSystem().fixCursor(core.getWindow().getResolution() / 2.f);
            }
        }
    }});

    core.getInputSystem().registrateAction("esc",
        {knx::KEYBOARD_EVENT_, [&](const knx::irl::Event &event){
            if((knx::KEYBOARD_EVENTS)event.getCode() == knx::KEY_PRESSED_){
                if(event.key == GLFW_KEY_ESCAPE){
                    core.getInputSystem().showCursor();
                    core.getInputSystem().freeCursor();
                }
            }
        }
    });

    core.setCAController(knx::CameraController( core.getCameraPointer(), core.getInputSystemPointer(), core.getTimePointer()));
    
    auto shader = knx::irl::Shader(
            //"res/shaders/material_folder/object"
            // "res/shaders/ht_sh"
            "res/st_shaders/StandartShader"
    );
    core.addShader("objectShader",
        &shader
    );
    
    core.addMaterial("cubeMaterial",
        knx::irl::Material(
            32.0f,               // Shininess
            {1.0f, 0.5f, 0.31f}, // Diffuse
            {0.5f}               // Specular
        )
    );
    
    core.getLightScene().addPointLightSource("sun",
        knx::PointLightSource(
            knx::irl::PointLight(
                {0.2f},        // Ambient
                {0.5f},        // Diffuse
                {1.0f},        // Specular
                0.14f,         // Linear param 
                0.07f,         // Quadratic param
                {1.f}          // Color
            ), knx::irl::Transform(vec3f{0.f, 2.f, 0.f})
        )
    );

    core.getLightScene().addDirectionLightSource("sun2",
        knx::DirectLightSource(
            knx::irl::DirectionLight(
                {0.2f},
                {1.f},
                {0.5f},
                {0, 0, 1}
            ), knx::irl::Transform({-1}, {0.f, 1.f, 0.f})
        )
    );

    core.getLightScene().addSpotLightSource("sun3",
        knx::SpotLightSource(
            knx::irl::SpotLight(
                {0.1f},
                {.8f},
                {1.f},
                cos(rad(12.5)), cos(rad(17.5)), 0.09, 0.032, {0, 1, 0}
            ), knx::irl::Transform({1}, {0.f, 1.f, 0.f})
        )
    );
    
    auto mesh = knx::irl::Mesh(
            knx::irl::meshes::cubemesh_txs_nrms,
            true, true
    );
    mesh.setupBuffers(*core.getShaderPointer("objectShader"));

    core.addTexture("currtexture", knx::irl::Texture("res/floor.png"));
    knx::Object cube(
        "Cube",
        knx::irl::Transform(
            {0, 0, 0}, // Position
            {0, 0, 0}  // Rotation
        ), {{"currtexture", core.getTexture("currtexture")}},
        core.getCameraPointer(),
        core.getShaderPointer("objectShader"),
        core.getMaterialPointer("cubeMaterial")
    );
    cube.meshPtr = &mesh;
    core.addObject("Cosmo", &cube);

    while(core.isRunning()){
        core.update(
            [&](){
                // cube.getTransform().rotate(vec3f{0, 10, 0});
                // cube.getTransform().setPosition({sin(core.getWindow().getTick()*0.1)*10, 0, 5});
                // cout<<"Draw done\n";
            }, // Draw
            [&](){
                
                core.getLightScene().getSpotLightSource("sun3").getTransform().setPosition(core.getCamera().getTransform().getPosition());
                core.getLightScene().getSpotLightSource("sun3").getTransform().setRotation(core.getCamera().getTransform().getRotation());
                // cout<<"Update done\n";
            }, // Update
            [&](){
                // cout<<"Pre-draw done\n";
            }, // Pre-draw
            [&](){
                // cout<<"Post-draw done\n";
            }  // Post-draw
        );
    }
    // cout<<"Run done\n";
}