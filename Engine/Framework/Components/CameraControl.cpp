#include "CameraControl.h" 
#include "Engine.h" 

namespace dbf
{
	void CameraControl::update()
	{
		// update transform 
		//x Axis
		if (dbf::g_inputSystem.queryKeyState(dbf::key_left) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.x -= speed * g_time.deltaTime;
		if (dbf::g_inputSystem.queryKeyState(dbf::key_right) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.x += speed * g_time.deltaTime;
		// y Axis
		if (dbf::g_inputSystem.queryKeyState(dbf::key_up) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.y += speed * g_time.deltaTime;
		if (dbf::g_inputSystem.queryKeyState(dbf::key_down) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.y -= speed * g_time.deltaTime;
		//z Axis
		if (dbf::g_inputSystem.queryKeyState(dbf::key_paged) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.z -= speed * g_time.deltaTime;
		if (dbf::g_inputSystem.queryKeyState(dbf::key_pageu) == dbf::InpSystem::keyState::Held) m_owner->m_transform.position.z += speed * g_time.deltaTime;
	}

	bool CameraControl::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraControl::read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}

}