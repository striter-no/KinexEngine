#pragma once

#include "irrk/irrKlang.h"
#include <conio.h>

#include <AdtClasses/AdtClasses.hpp>
#include <MathLib/VectorFuncs.hpp>
using namespace adm;
using namespace eml;
using namespace adc;

enum SOUND_EFFECTS{
    DISTORTION,
    ECHO,
    WAVES_REVERB,
    CHORUS,
    COMPRESSOR,
    FLANGER,
    GARGLE,
    I3DL2_REVERB,
    PARAM_EQ
};

class Sound{
    string path; 
    vector<SOUND_EFFECTS> sfx_vc; 
    bool isLooped = false, isTD = true; 
    irrklang::ISoundEngine* engine = nullptr;

    irrklang::ISound* data = nullptr;
    irrklang::ISoundEffectControl* effControl = nullptr;

    vec3f pos = {0.f, 0.f, 0.f};

    public:

    Sound(string path, vector<SOUND_EFFECTS> sfx_vc, bool isLooped, irrklang::ISoundEngine* engine, bool isTD): path(path), sfx_vc(sfx_vc), isLooped(isLooped), engine(engine), isTD(isTD){
        
    }

    void setSVolume(float val){
        data->setVolume(val);
    }

    void setPath(string path){this-> path = path;}
    void setEngine(irrklang::ISoundEngine* engine){this->engine = engine;}

    static void updateListner3D(vec3f listnerPos, vec3f listnerDir, irrklang::ISoundEngine* rengine){rengine->setListenerPosition({listnerPos.x, listnerPos.y, listnerPos.z}, {listnerDir.x, listnerDir.y, listnerDir.z});}
    void updateMusicPos3D(vec3f pos){
        this->pos = pos;
        data->setPosition({pos.x, pos.y, pos.z});
    }

    void stopPlaying(){data->stop();}
    void play(bool effectApply = false){
        if(isTD){
            data = engine->play3D(path.c_str(), {pos.x, pos.y, pos.z}, isLooped, false, true, irrklang::ESM_AUTO_DETECT, effectApply);
            if(effectApply) effControl = data->getSoundEffectControl();
        }
    }

    irrklang::ISoundEffectControl *getSFXControl(){return effControl;}
    template<class... Args> void enableDistortionSFX(Args && ...args) { effControl->enableDistortionSoundEffect(args...); }
    template<class... Args> void enableEchoSFX(Args && ...args) { effControl->enableEchoSoundEffect(args...); }
    template<class... Args> void enableWavesReverbSFX(Args && ...args) { effControl->enableWavesReverbSoundEffect(args...); }
    template<class... Args> void enableChorusSFX(Args && ...args) { effControl->enableChorusSoundEffect(args...); }
    template<class... Args> void enableCompressorSFX(Args && ...args) { effControl->enableCompressorSoundEffect(args...); }
    template<class... Args> void enableFlangerSFX(Args && ...args) { effControl->enableFlangerSoundEffect(args...); }
    template<class... Args> void enableGargleSFX(Args && ...args) { effControl->enableGargleSoundEffect(args...); }
    template<class... Args> void enableI3DL2ReverbSFX(Args && ...args) { effControl->enableI3DL2ReverbSoundEffect(args...); }
    template<class... Args> void enableParamEqSFX(Args && ...args) { effControl->enableParamEqSoundEffect(args...);}
    void disableEffect(SOUND_EFFECTS effect){
        switch(effect){
            case DISTORTION: effControl->disableDistortionSoundEffect(); break;
            case ECHO: effControl->disableEchoSoundEffect(); break;
            case WAVES_REVERB: effControl->disableWavesReverbSoundEffect(); break;
            case CHORUS: effControl->disableChorusSoundEffect(); break;
            case COMPRESSOR: effControl->disableCompressorSoundEffect(); break;
            case FLANGER: effControl->disableFlangerSoundEffect(); break;
            case GARGLE: effControl->disableGargleSoundEffect(); break;
            case I3DL2_REVERB: effControl->disableI3DL2ReverbSoundEffect(); break;
            case PARAM_EQ: effControl->disableParamEqSoundEffect(); break;
            default: cout<<"No such effect\n"; break;
        }
    }
    void disableAllEffects(){effControl->disableAllEffects();}

    Sound(){}
    ~Sound(){
        data->drop();
    }
};