#include <iostream>
#include <raylib.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>

#include "./headers/settings_gpu.hpp"

using namespace std;

float rand_float(void)
{
    return (float)rand()/(float)RAND_MAX;
}

int main(int argc, char* argv[])
{   
    if(argv[1] == NULL){
        cout << "preset not specified" << endl;
        cout << "try ./smooth_life_gpu stable.json" << endl;
        return 0;
    }

    settings_gpu settings;
    settings.set_settings("./presets/gpu_presets/" + string(argv[argc - 1]));
    settings.generate_shader();

    int fps              = settings.get_fps();
    int init             = settings.get_init();
    float factor         = settings.get_factor();
    float scalar         = settings.get_scalar();
    float screen_width   = 16 * factor;
    float screen_height  = 9 * factor;
    float texture_width  = screen_width * scalar;
    float texture_height = screen_height * scalar; 

    InitWindow(screen_width, screen_height, "smooth_life");
    SetTargetFPS(fps);

    Image image;
    
    switch(init) {
        case 1:
            image = GenImagePerlinNoise(texture_width, texture_height, 0, 0, 1.0f);
            break;

        case 2:
            image = GenImageWhiteNoise(texture_width, texture_height, 0.9f);
            break;

        case 3:
            image = GenImageCellular(texture_width, texture_height, texture_height/6);
            break;
        
        case 4:
            image = GenImageGradientRadial(texture_width, texture_height, 0.5,WHITE, BLACK);
            break;

        case 5:
            image = GenImageColor(texture_width, texture_height, BLACK);
            for (int y = 0; y < texture_height*3/4; ++y) {
                for (int x = 0; x < texture_width*3/4; ++x) {
                    uint8_t v = rand_float()*255.0f;
                    Color color = { v, v, v, 255 };
                    ImageDrawPixel(&image, x, y, color);
                }
            }
            break;

        default:
            image = GenImagePerlinNoise(texture_width, texture_height, 0, 0, 1.0f);
            break;
    }
    
    RenderTexture2D state[2];

    state[0] = LoadRenderTexture(texture_width, texture_height);
    SetTextureWrap(state[0].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(state[0].texture, TEXTURE_FILTER_BILINEAR);
    
    UpdateTexture(state[0].texture, image.data);

    state[1] = LoadRenderTexture(texture_width, texture_height);
    SetTextureWrap(state[1].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(state[1].texture, TEXTURE_FILTER_BILINEAR);

    int i              = 0;
    Shader shader      = LoadShader(NULL, "./shader/smooth_life.fs");
    Vector2 resolution = {texture_width, texture_height};
    int resolution_loc = GetShaderLocation(shader, "resolution");

    SetShaderValue(shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

    while (!WindowShouldClose()) {
        BeginTextureMode(state[1 - i]);
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawTexture(state[i].texture, 0, 0, PURPLE);
            EndShaderMode();
        EndTextureMode();

        i = 1 - i;

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureEx(state[i].texture, {0.0f, 0.0f}, 0, 1/scalar, PURPLE);
        EndDrawing();
    }
    
    UnloadShader(shader);
    UnloadImage(image);
    CloseWindow();

    return 1;
}