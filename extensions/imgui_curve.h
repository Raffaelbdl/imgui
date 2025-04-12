// [src] https://github.com/ocornut/imgui/issues/123
// [src] https://github.com/ocornut/imgui/issues/55

// v1.23 - selection index track, value range, context menu, improve manipulation controls (D.Click to add/delete, drag to add)
// v1.22 - flip button; cosmetic fixes
// v1.21 - oops :)
// v1.20 - add iq's interpolation code
// v1.10 - easing and colors
// v1.00 - jari komppa's original

#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include <cmath>

/* To use, add this prototype somewhere..
namespace ImGui
{
    int Curve(const char *label, const ImVec2& size, int maxpoints, ImVec2 *points);
    float CurveValue(float p, int maxpoints, const ImVec2 *points);
    float CurveValueSmooth(float p, int maxpoints, const ImVec2 *points);
};
*/
/*
    Example of use:
    ImVec2 foo[10];
    int selectionIdx = -1;
    ...
    foo[0].x = ImGui::CurveTerminator; // init data so editor knows to take it from here
    ...
    if (ImGui::Curve("Das editor", ImVec2(600, 200), 10, foo, &selectionIdx))
    {
        // curve changed
    }
    ...
    float value_you_care_about = ImGui::CurveValue(0.7f, 10, foo); // calculate value at position 0.7
*/

namespace ImGui
{
    static const float CurveTerminator = -10000;

    // [src] http://iquilezles.org/www/articles/minispline/minispline.htm
    // key format (for dim == 1) is (t0,x0,t1,x1 ...)
    // key format (for dim == 2) is (t0,x0,y0,t1,x1,y1 ...)
    // key format (for dim == 3) is (t0,x0,y0,z0,t1,x1,y1,z1 ...)
    template <int DIM>
    void spline(const float *key, int num, float t, float *v)
    {
        static float coefs[16] = {
            -1.0f, 2.0f, -1.0f, 0.0f,
            3.0f, -5.0f, 0.0f, 2.0f,
            -3.0f, 4.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 0.0f};

        const int size = DIM + 1;

        // find key
        int k = 0;
        while (key[k * size] < t)
            k++;

        const float key0 = key[(k - 1) * size];
        const float key1 = key[k * size];

        // interpolant
        const float h = (t - key0) / (key1 - key0);

        // init result
        for (int i = 0; i < DIM; i++)
            v[i] = 0.0f;

        // add basis functions
        for (int i = 0; i < 4; ++i)
        {
            const float *co = &coefs[4 * i];
            const float b = 0.5f * (((co[0] * h + co[1]) * h + co[2]) * h + co[3]);

            const int kn = ImClamp(k + i - 2, 0, num - 1);
            for (int j = 0; j < DIM; j++)
                v[j] += b * key[kn * size + j + 1];
        }
    }

    int Curve(const char *label, const ImVec2 &size, const int maxpoints, ImVec2 *points, int *selection = nullptr, const ImVec2 &rangeMin = ImVec2(0, 0), const ImVec2 &rangeMax = ImVec2(1, 1));
    // float CurveValue(float p, int maxpoints, const ImVec2 *points);
    // float CurveValueSmooth(float p, int maxpoints, const ImVec2 *points);
    // void ShowBezierDemo();
}; // namespace ImGui
