#include <string>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class settings_term {

    public:
        settings_term();

        void set_settings(std::string settings_path);

        float get_ra();
        float get_alpha_n();
        float get_alpha_m();
        float get_b1();
        float get_b2();
        float get_d1();
        float get_d2();
        float get_dt();

    private:
        float ra;
        float alpha_n;
        float alpha_m;
        float b1;
        float b2;
        float d1;
        float d2;
        float dt;
};
