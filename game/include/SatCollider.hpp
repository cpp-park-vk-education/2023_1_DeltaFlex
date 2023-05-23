#pragma once

// #include "physics/Link.hpp"
#include <DFvec2.hpp>
#include <DFRenderSystem.hpp>

class SATCollider
{
public:
    static void CalcNormal(Vector2<float> &normal,
        const Vector2<float> &p1,
        const Vector2<float> &p2)
    {
        normal.y = p1.x - p2.x;
        normal.x = p2.y - p1.y;

        normal /= normal.length();
    }
    // SATCollider(const Link &link)
    //     : p1(link.m_p1.m_pos),
    //     p2(link.m_p2.m_pos)
    // {
    // }
    SATCollider(Vector2<float> &p1, Vector2<float> &p2) :p1(p1), p2(p2) {}
    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderPoint(p1);
        render_system.RenderPoint(p2);

        for (size_t i = 0; i < 4 - 1; ++i)
            render_system.RenderLine(points[i], points[i + 1]);
        render_system.RenderLine(points[3], points[0]);
    }

    void RecalcPoints(const int width)
    {
        Vector2<float> tmp_normal;
        CalcNormal(tmp_normal, p1, p2);
        tmp_normal *= width;

        points[0] = p1 + tmp_normal;
        points[1] = p2 + tmp_normal;
        points[2] = p2 - tmp_normal;
        points[3] = p1 - tmp_normal;
    }

    bool isCollidingHelper(const Vector2<float> &normal, const SATCollider &other)
    {
        float a, b, min_other, max_other;
        a = b = normal.x * points[0].x + normal.y * points[0].y;
        for (size_t i = 1; i < 4; ++i)
        {
            float cur_dot = normal.x * points[i].x + normal.y * points[i].y;
            if (cur_dot < a)
            {
                a = cur_dot;
            }
            if (cur_dot > b)
            {
                b = cur_dot;
            }
        }

        min_other = max_other = normal.x * other.points[0].x + normal.y * other.points[0].y;
        for (size_t i = 0; i < 4; ++i)
        {
            float cur_dot = normal.x * other.points[i].x + normal.y * other.points[i].y;
            if (a <= cur_dot && cur_dot <= b)
            {
                return true;
            }
            if (cur_dot < min_other)
            {
                min_other = cur_dot;
            }
            if (cur_dot > max_other)
            {
                max_other = cur_dot;
            }
        }

        return min_other <= a && b <= max_other;
    }

    bool isColliding(const SATCollider &other)
    {
        Vector2<float> normal;
        for (size_t i = 0; i < 4 - 1; ++i)
        {
            CalcNormal(normal, points[i], points[i + 1]);
            if (!isCollidingHelper(normal, other))
            {
                return false;
            }
        }
        CalcNormal(normal, points[3], points[0]);
        if (!isCollidingHelper(normal, other))
        {
            return false;
        }

        for (size_t i = 0; i < 4 - 1; ++i)
        {
            CalcNormal(normal, other.points[i], other.points[i + 1]);
            if (!isCollidingHelper(normal, other))
            {
                return false;
            }
        }
        CalcNormal(normal, other.points[3], other.points[0]);
        if (!isCollidingHelper(normal, other))
        {
            return false;
        }

        return true;
    }

private:
    Vector2<float> &p1, &p2;
    Vector2<float> points[4];
};