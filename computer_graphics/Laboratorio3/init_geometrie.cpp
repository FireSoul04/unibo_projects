#pragma once

#include <cmath>
#include <functional>

#include "strutture.h"
#define PI 3.14159265358979323
extern float alpha;

void INIT_TRIANGLE(Figura* fig, vec4 color_top, vec4 color_bottom){
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    fig->colors.push_back(color_top);
    fig->colors.push_back(color_bottom);
    fig->colors.push_back(color_bottom);
    fig->nv = 3;
    fig->render = GL_TRIANGLES;
}

void INIT_FIGURE(float cx, float cy, float raggiox, float raggioy, Figura* fig, function<double(double)> fx, function<double(double)> fy, vec4 color_top, vec4 color_bottom) {
    float stepA = (2 * PI) / fig->nTriangles;
    fig->vertices.push_back({ cx, cy, 0.0f });
    fig->colors.push_back(color_top);
    for (int i = 0; i <= fig->nTriangles; i++) {
        float t = stepA * (double)i;
        float x = fx(t);
        float y = fy(t);
        fig->vertices.push_back({ cx + x * raggiox, cy + y * raggioy, 0.0f });
        fig->colors.push_back(color_bottom);
    }
    fig->nv = fig->vertices.size();
}

void INIT_CIRCLE(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom) {
    INIT_FIGURE(cx, cy, raggiox, raggioy, fig, [](double t) { return cos(t); }, [](double t) { return sin(t); }, color_top, color_bottom);
}

void INIT_HEART(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom) {
    INIT_FIGURE(cx, cy, raggiox, raggioy, fig,
        [](double t) { return 16 * pow(sin(t), 3); },
        [](double t) { return 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t); },
        color_top, color_bottom
    );
}

void INIT_BUTTERFLY(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom) {
    INIT_FIGURE(cx, cy, raggiox, raggioy, fig,
        [](double t) { return sin(t) * (exp(cos(t) - 2 * cos(4 * t))) + pow(sin(t / 12), 5); },
        [](double t) { return cos(t) * (exp(cos(t) - 2 * cos(4 * t))) - pow(sin(t / 12), 5); },
        color_top, color_bottom
    );
}