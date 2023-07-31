#include <string>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class settings_gpu {

    public:
        settings_gpu();

        void set_settings(std::string settings_path);

        void generate_shader();

        int get_init();
        int get_fps();
        
        float get_factor();
        float get_scalar();

    private:
        int init;
        int fps;

        float factor;
        float scalar;

        float ra;
        float alpha_n;
        float alpha_m;
        float b1;
        float b2;
        float d1;
        float d2;
        float dt;
};
