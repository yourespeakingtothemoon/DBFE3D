#include "CameraComponent.h"
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace dbf
{
    void CameraComponent::init()
    {
        setViewport(viewport_size);
    }

    void CameraComponent::update()
    {
        // create camera view matrix 
        Mat3x3 mxTranslation = Mat3x3::createTranslation(-m_owner->m_transform.position);
        Mat3x3 mxRotation = Mat3x3::createRotate(-math::DegToRad(m_owner->m_transform.rotation));

        m_view = mxTranslation * mxRotation;

        g_renderer.setViewMatrix(m_view);
    }

    void CameraComponent::setViewport(const Vector2& size)
    {
        Mat3x3 mxTranslation = Mat3x3::createTranslation(size * 0.5f);

        m_viewport = mxTranslation;
        g_renderer.setViewportMatrix(m_viewport);
    }

    bool CameraComponent::write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CameraComponent::read(const rapidjson::Value& value)
    {
        READ_DATA(value, viewport_size);

        return true;
    }

}