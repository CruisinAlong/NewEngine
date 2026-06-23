#include "signpch.h"
#include "DeleteAllCommand.h"

namespace Sign {
	void DeleteAllCommand::Execute()
	{
		m_CachedBackUp.assign(m_EntityList.begin() + m_ProtectedCount, m_EntityList.end());
		m_EntityList.erase(m_EntityList.begin() + m_ProtectedCount, m_EntityList.end());
	}
	void DeleteAllCommand::Undo()
	{
		m_EntityList.insert(m_EntityList.end(), m_CachedBackUp.begin(), m_CachedBackUp.end());
		m_CachedBackUp.clear();
	}
}