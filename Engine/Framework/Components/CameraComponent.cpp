#include "CameraComponent.h"
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace dbf
{
   
    void CameraComponent::update()
    {
        //x Axis
        if (dbf::g_inputSystem.queryKeyState(dbf::key_left) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.x -= speed * g_time.deltaTime;
        if (dbf::g_inputSystem.queryKeyState(dbf::key_right) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.x += speed * g_time.deltaTime;
        // y Axis
        if (dbf::g_inputSystem.queryKeyState(dbf::key_up) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.y += speed * g_time.deltaTime;
        if (dbf::g_inputSystem.queryKeyState(dbf::key_down) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.y -= speed * g_time.deltaTime;
        //z Axis
        if (dbf::g_inputSystem.queryKeyState(dbf::key_paged) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.z -= speed * g_time.deltaTime;
        if (dbf::g_inputSystem.queryKeyState(dbf::key_pageu) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.z += speed * g_time.deltaTime;
        m_view = glm::lookAt(m_owner->m_transform.position, m_owner->m_transform.position + m_owner->m_transform.getForward(), glm::vec3{ 0, 1, 0 });

    }

    void CameraComponent::SetPerspective(float fov, float aspectRatio, float near, float far)
    {

        m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    }

    void CameraComponent::SetProgram(std::shared_ptr<Program> prog)
    {
        prog->Use();
        prog->SetUniform("view", m_view);
        prog->SetUniform("projection", m_projection);
    }
    
    bool CameraComponent::write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CameraComponent::read(const rapidjson::Value& value)
    {

        float fov;
        READ_DATA(value, fov);
        float aspect_ratio;
        if (!READ_DATA(value, aspect_ratio))
        {

            aspect_ratio = g_renderer.getWidth() / (float(g_renderer.getHeight()));

        }
        float near;
        READ_DATA(value, near);
        float far;
        READ_DATA(value, far);

        SetPerspective(fov, aspect_ratio, near, far);

        return true;
    }

}