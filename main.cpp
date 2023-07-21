#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "./headers/settings_term.hpp"

using namespace std;

#define WIDTH 150
#define HEIGHT 150

const char level[]             = " .-=coaA@#";
float grid[HEIGHT][WIDTH]      = {0.0f};
float grid_diff[HEIGHT][WIDTH] = {0.0f};

#define level_count (sizeof(level)/sizeof(level[0]) - 1)

void clamp(float *x, float l, float h) {
    if (*x < l) *x = l;
    if (*x > h) *x = h;
}

int emod(int a, int b) {
    return(a % b + b) % b;
}

float random_float() {
    return (float)rand()/(float)RAND_MAX;
}

float sigma(float x, float a, float alpha) {
    return 1.0f / (1.0f + expf( -(x - a) * 4 / alpha));
}

float sigma_n(float x, float a, float b, float alpha_n)
{
    return sigma(x, a, alpha_n)*(1 - sigma(x, b, alpha_n));
}

float sigma_m(float x, float y, float m, float alpha_m)
{
    return x*(1 - sigma(m, 0.5f, alpha_m)) + y*sigma(m, 0.5f, alpha_m);
}

float s(float n, float m, float b1, float b2, float d1, float d2, float alpha_n, float alpha_m)
{
    return sigma_n(n, sigma_m(b1, d1, m, alpha_m), sigma_m(b2, d2, m, alpha_m), alpha_n);
}

void random_grid()
{
    int w = WIDTH/3;
    int h = HEIGHT/3;

    for (int dy = 0; dy < h; ++dy) {
        for (int dx = 0; dx < w; ++dx) {
            int x      = dx + WIDTH/2 - w/2;
            int y      = dy + HEIGHT/2 - h/2;
            grid[y][x] = random_float();
        }
    }

}

void display_grid(float grid[HEIGHT][WIDTH])
{
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            char c = level[(int)(grid[y][x]*(level_count - 1))];
            cout << c;
            cout << c;
        }
        cout << endl;
    }
}

void compute_grid_diff(float b1, float b2, float d1, float d2, float alpha_n, float alpha_m, float ra)
{
    for (int cy = 0; cy < HEIGHT; ++cy) {
        for (int cx = 0; cx < WIDTH; ++cx) {
            float m = 0, M = 0;
            float n = 0, N = 0;
            float ri = ra/3;

            for (int dy = -(ra - 1); dy <= (ra - 1); ++dy) {
                for (int dx = -(ra - 1); dx <= (ra - 1); ++dx) {
                    int x = emod(cx + dx, WIDTH);
                    int y = emod(cy + dy, HEIGHT);
                    if (dx*dx + dy*dy <= ri*ri) {
                        m += grid[y][x];
                        M += 1;
                    } else if (dx*dx + dy*dy <= ra*ra) {
                        n += grid[y][x];
                        N += 1;
                    }
                }
            }
            m /= M;
            n /= N;
            float q = s(n, m, b1, b2, d1, d2, alpha_n, alpha_m);
            grid_diff[cy][cx] = 2*q - 1;
        }
    }
}

void apply_grid_diff(float dt)
{
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] += dt*grid_diff[y][x];
            clamp(&grid[y][x], 0, 1);
        }
    }
}

int main() {
    
    settings_term settings;
    struct timespec delay;

    settings.set_settings("settings/terminal_settings/settings.json");

    const float ra      = settings.get_ra();
    const float alpha_n = settings.get_alpha_n();
    const float alpha_m = settings.get_alpha_m();
    const float b1      = settings.get_b1();
    const float b2      = settings.get_b2();
    const float d1      = settings.get_d1();
    const float d2      = settings.get_d2();
    const float dt      = settings.get_dt();

    delay.tv_sec        = 0;
    delay.tv_nsec       = 10000000;

    srand(time(0));
    random_grid();
    display_grid(grid);

    for( ; ; ) {
        compute_grid_diff(b1, b2, d1, d2, alpha_n, alpha_m, ra);
        apply_grid_diff(dt);
        display_grid(grid);
        nanosleep(&delay, NULL);
        system("clear");
    }

    return 0;
}