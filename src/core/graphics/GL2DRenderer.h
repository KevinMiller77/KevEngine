#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <vector>
#include <string>
#include <deque>

#include <math.h>
#include "FontManager.h"
#include "../math/math.h"


class Renderable2D;

class GL2DRenderer
{
protected:
    GL2DRenderer()
    {  
        TransformationStack.push_back(Mat4f(1.0f));
        curTransformationBack = &TransformationStack.back();
    }

protected:
    std::vector<Mat4f> TransformationStack;
    const Mat4f* curTransformationBack;

public:
    virtual ~GL2DRenderer() = default;
    
    void Push(const Mat4f &matrix, bool override = false)
    {
        if (override)
        {
            TransformationStack.push_back(matrix);
            //LOG_INF("Pushed to transformation stack with override\n");
        }
        else
        {
            TransformationStack.push_back(TransformationStack.back() * matrix);
            //LOG_INF("Pushed to transformation stack\n");
        }
        curTransformationBack = &(TransformationStack.back());
    }

    void Pop()
    {
        if (TransformationStack.size() > 1)
        {
            TransformationStack.pop_back();
            //LOG_INF("Popped transformation stack\n");
        }
        curTransformationBack = &(TransformationStack.back());
    }


    virtual void DrawString(std::string text, Vec3f position, FontInfo* font, uint32_t color) = 0;
    virtual void Submit(const Renderable2D *renderable) = 0;
    virtual void Draw() = 0;
    virtual void Begin() = 0;
    virtual void End() = 0;
};

#endif