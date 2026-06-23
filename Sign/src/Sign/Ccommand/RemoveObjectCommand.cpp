#include "signpch.h"
#include "RemoveObjectCommand.h"

namespace Sign {
	void RemoveObjectCommand::Execute()
	{
		if (!m_EntityList.empty()) {
			m_TargetEntity = m_EntityList.back();
			m_EntityList.pop_back();
		}
	}
	void RemoveObjectCommand::Undo()
	{
		if (m_TargetEntity != nullptr) {
			m_EntityList.push_back(m_TargetEntity);
		}
	}
}