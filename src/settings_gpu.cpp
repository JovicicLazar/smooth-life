#include "../headers/settings_gpu.hpp"

settings_gpu::settings_gpu() {
    this->init    = 1;
    this->fps     = 60;

    this->factor  = 50;
    this->scalar  = 0.6;
    
    this->ra      = 11.0;
    this->alpha_n = 0.028;
    this->alpha_m = 0.147;
    this->b1      = 0.278;
    this->b2      = 0.365;
    this->d1      = 0.267;
    this->d2      = 0.445;
    this->dt      = 0.05;
}

void settings_gpu::set_settings(string settings_path) {
    ifstream file(settings_path);
    Json::Reader reader;
    Json::Value completeJsonData;
    
    reader.parse(file, completeJsonData);

    this->init    = completeJsonData["init"].asInt();
    this->fps     = completeJsonData["fps"].asInt();

    this->factor  = completeJsonData["factor"].asFloat();
    this->scalar  = completeJsonData["scalar"].asFloat();

    this->ra      = completeJsonData["ra"].asFloat();
    this->alpha_n = completeJsonData["alpha_n"].asFloat();
    this->alpha_m = completeJsonData["alpha_m"].asFloat();
    this->b1      = completeJsonData["b1"].asFloat();
    this->b2      = completeJsonData["b2"].asFloat();
    this->d1      = completeJsonData["d1"].asFloat();
    this->d2      = completeJsonData["d2"].asFloat();
    this->dt      = completeJsonData["dt"].asFloat();
}

void settings_gpu::generate_shader() {
    fstream file("./shader/smooth_life.fs", std::ios::out);

    file << "#version 330" << std::endl;
    file << "" << std::endl;
    file << "in vec2 fragTexCoord;" << std::endl;
    file << "in vec4 fragColor;" << std::endl;
    file << "" << std::endl;
    file << "uniform sampler2D texture0;" << std::endl;
    file << "uniform vec4 colDiffuse;" << std::endl;
    file << "" << std::endl;
    file << "out vec4 finalColor;" << std::endl;
    file << "" << std::endl;
    file << "uniform vec2 resolution;" << std::endl;
    file << "" << std::endl;
    file << "#define PI 3.14159265359" << std::endl;
    file << "" << std::endl;
    file << "float ra      = " + to_string(this->ra) + ";" << std::endl;
    file << "float b1      = " + to_string(this->b1) + ";" << std::endl;
    file << "float b2      = " + to_string(this->b2) + ";" << std::endl;
    file << "float d1      = " + to_string(this->d1) + ";" << std::endl;
    file << "float d2      = " + to_string(this->d2) + ";" << std::endl;
    file << "float alpha_n = " + to_string(this->alpha_n) + ";" << std::endl;
    file << "float alpha_m = " + to_string(this->alpha_m) + ";" << std::endl;
    file << "float dt      = " + to_string(this->dt) + ";" << std::endl;
    file << "" << std::endl;
    file << "float sigma(float x, float a, float alpha)" << std::endl;
    file << "{" << std::endl;
    file << "    return 1.0/(1.0 + exp(-(x - a)*4.0/alpha));" << std::endl;
    file << "}" << std::endl;
    file << "" << std::endl;
    file << "float sigma_n(float x, float a, float b)" << std::endl;
    file << "{" << std::endl;
    file << "    return sigma(x, a, alpha_n)*(1.0 - sigma(x, b, alpha_n));" << std::endl;
    file << "}" << std::endl;
    file << "" << std::endl;
    file << "float sigma_m(float x, float y, float m)" << std::endl;
    file << "{" << std::endl;
    file << "    return x*(1 - sigma(m, 0.5, alpha_m)) + y*sigma(m, 0.5, alpha_m);" << std::endl;
    file << "}" << std::endl;
    file << "" << std::endl;
    file << "float s(float n, float m)" << std::endl;
    file << "{" << std::endl;
    file << "    return sigma_n(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));" << std::endl;
    file << "}" << std::endl;
    file << "" << std::endl;
    file << "float grid(float x, float y)" << std::endl;
    file << "{" << std::endl;
    file << "    float tx = x/resolution.x;" << std::endl;
    file << "    float ty = y/resolution.y;" << std::endl;
    file << "    vec4 t   = texture(texture0, vec2(tx, ty));" << std::endl;
    file << "    return max(max(t.x, t.y), t.z);" << std::endl;
    file << "}" << std::endl;
    file << "" << std::endl;
    file << "void main()" << std::endl;
    file << "{" << std::endl;
    file << "    float cx = fragTexCoord.x*resolution.x;" << std::endl;
    file << "    float cy = (1 - fragTexCoord.y)*resolution.y;" << std::endl;
    file << "    float ri = ra/3.0;" << std::endl;
    file << "    float m = 0;" << std::endl;
    file << "    float M = PI*ri*ri;" << std::endl;
    file << "    float n = 0;" << std::endl;
    file << "    float N = PI*ra*ra - M;" << std::endl;
    file << "" << std::endl;
    file << "    for (float dy = -ra; dy <= ra; dy += 1.0) {" << std::endl;
    file << "        for (float dx = -ra; dx <= ra; dx += 1.0) {" << std::endl;
    file << "            float x = cx + dx;" << std::endl;
    file << "            float y = cy + dy;" << std::endl;
    file << "            if (dx*dx + dy*dy <= ri*ri) {" << std::endl;
    file << "                m += grid(x, y);" << std::endl;
    file << "            } else if (dx*dx + dy*dy <= ra*ra) {" << std::endl;
    file << "                n += grid(x, y);" << std::endl;
    file << "            }" << std::endl;
    file << "        }" << std::endl;
    file << "    }" << std::endl;
    file << "" << std::endl;
    file << "    m /= M;" << std::endl;
    file << "    n /= N;" << std::endl;
    file << "    float q = s(n, m);" << std::endl;
    file << "    float diff = 2.0*q - 1.0;" << std::endl;
    file << "    float v = clamp(grid(cx, cy) + dt*diff, 0.0, 1.0);" << std::endl;
    file << "    finalColor = vec4(v, v, v, 1);" << std::endl;
    file << "}" << std::endl;

    file.close();
}

int settings_gpu::get_init() {
    return this->init;
}

int settings_gpu::get_fps() {
    return this->fps;
}

float settings_gpu::get_factor() {
    return this->factor;
}

float settings_gpu::get_scalar() {
    return this->scalar;
}