#pragma once
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>

namespace knx{
    class PhysicsScene{
        map<string, irl::RigidBody*> rigidBodys;
        bool state = false;

        irl::PhysicsEnviroment enviroment;

        public:

        const bool &getState(){return state; }
        void enable(){state = true;}
        void diable(){state = false;}

        void deleteRigidBody(string name){
            rigidBodys.erase(name);
        }

        void addRigidBody(string name, irl::RigidBody *rigidBody){
            rigidBodys[name] = rigidBody;
        }

        irl::RigidBody *getRigidBody(string name){
            return rigidBodys[name];
        }

        irl::Collision isRigidBodyCollided(string name, string name2){
            return rigidBodys[name]->processCollision(*rigidBodys[name2]);
        }

        irl::Collision isRigidBodyCollided(string name){
            vector<irl::Collision> out;
            for(auto &pr: rigidBodys){ irl::RigidBody *rb = pr.second;
                rb->update(enviroment);
                for(auto &pr2: rigidBodys){ 
                    if(pr.first == pr2.first) continue;
                    auto info = rb->processCollision(*pr2.second);
                    if(info.getCollidedStatus()) return {info};
                }
            }

            return irl::Collision::NOT_COLLIDED() ;
        }

        vector<irl::Collision> getAllCollisionWithRigidBody(string name){
            vector<irl::Collision> out;
            for(auto &pr: rigidBodys){ irl::RigidBody *rb = pr.second;
                for(auto &pr2: rigidBodys){ 
                    if(pr.first == pr2.first) continue;
                    auto info = rb->processCollision(*pr2.second);
                    if(info.getCollidedStatus()) out.push_back(info);
                }
                rb->update(enviroment);
            }
            return {out};
        }

        void update(){
            if(!state) return;

            for(auto &pr: rigidBodys){ irl::RigidBody *rb = pr.second;
                if(rb->getStatic()) continue;
                cout<<"update "<<pr.first<<endl;
                rb->update(enviroment);
                cout<<"updated\n";
                for(auto &pr2: rigidBodys){ 
                    if(pr.first == pr2.first) continue;
                    cout<<"calciulating collision with "<<pr2.first<<"...\n";
                    irl::Collision collision = rb->processCollision(*pr2.second);
                    cout<<"calculated!\n";

                    cout<<"collision info: \n"<<
                        "\t"<<to_stringb(collision.getCollidedStatus())<<endl<<
                        "\t"<<collision.getVelocity().str()<<endl;
                }
            }
        }

        PhysicsScene(irl::PhysicsEnviroment enviroment, bool state): enviroment(enviroment), state(state) {}
        PhysicsScene(){}
        ~PhysicsScene(){}
    };
};