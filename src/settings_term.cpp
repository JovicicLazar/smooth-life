#include "../headers/settings_term.hpp"

settings_term::settings_term() {
    this->ra      = 11.0;
    this->alpha_n = 0.028;
    this->alpha_m = 0.147;
    this->b1      = 0.278;
    this->b2      = 0.365;
    this->d1      = 0.267;
    this->d2      = 0.445;
    this->dt      = 0.05;
}

void settings_term::set_settings(string settings_path) {
    ifstream file(settings_path);
    Json::Reader reader;
    Json::Value completeJsonData;
    
    reader.parse(file, completeJsonData);

    this->ra      = completeJsonData["ra"].asFloat();
    this->alpha_n = completeJsonData["alpha_n"].asFloat();
    this->alpha_m = completeJsonData["alpha_m"].asFloat();
    this->b1      = completeJsonData["b1"].asFloat();
    this->b2      = completeJsonData["b2"].asFloat();
    this->d1      = completeJsonData["d1"].asFloat();
    this->d2      = completeJsonData["d2"].asFloat();
    this->dt      = completeJsonData["dt"].asFloat();
}

float settings_term::get_ra(){
    return this->ra;
}

float settings_term::get_alpha_n(){
    return this->alpha_n;
}

float settings_term::get_alpha_m(){
    return this->alpha_m;
}

float settings_term::get_b1(){
    return this->b1;
}

float settings_term::get_b2(){
    return this->b2;
}

float settings_term::get_d1(){
    return this->d1;
}

float settings_term::get_d2(){
    return this->d2;
}

float settings_term::get_dt(){
    return this->dt;
}