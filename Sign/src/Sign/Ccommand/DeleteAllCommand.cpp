#include "signpch.h"
#include "DeleteAllCommand.h"

namespace Sign {
	void DeleteAllCommand::Execute()
	{
		if (m_EntityListECS) {
			if ((int)m_EntityListECS->size() > m_ProtectedCount) {
				m_CachedBackUp.assign(m_EntityListECS->begin() + m_ProtectedCount, m_EntityListECS->end());
				m_EntityListECS->erase(m_EntityListECS->begin() + m_ProtectedCount, m_EntityListECS->end());
			}
			return;
		}
		if (m_LegacyList) {
			if ((int)m_LegacyList->size() > m_ProtectedCount) {
				m_CachedLegacyBackUp.assign(m_LegacyList->begin() + m_ProtectedCount, m_LegacyList->end());
				m_LegacyList->erase(m_LegacyList->begin() + m_ProtectedCount, m_LegacyList->end());
			}
		}
	}
	void DeleteAllCommand::Undo()
	{
		if (m_EntityListECS) {
			if (!m_CachedBackUp.empty()) {
				m_EntityListECS->insert(m_EntityListECS->end(), m_CachedBackUp.begin(), m_CachedBackUp.end());
				m_CachedBackUp.clear();
			}
			return;
		}
		if (m_LegacyList) {
			if (!m_CachedLegacyBackUp.empty()) {
				m_LegacyList->insert(m_LegacyList->end(), m_CachedLegacyBackUp.begin(), m_CachedLegacyBackUp.end());
				m_CachedLegacyBackUp.clear();
			}
		}
	}
}