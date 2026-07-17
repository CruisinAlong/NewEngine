#include "signpch.h"
#include "RemoveObjectCommand.h"

namespace Sign {
	void RemoveObjectCommand::Execute()
	{
		if (m_EntityListECS) {
			if (!m_EntityListECS->empty()) {
				m_TargetEntity = m_EntityListECS->back();
				m_EntityListECS->pop_back();
			}
			return;
		}
		if (m_LegacyList) {
			if (!m_LegacyList->empty()) {
				m_LegacyTarget = m_LegacyList->back();
				m_LegacyList->pop_back();
			}
		}
	}
	void RemoveObjectCommand::Undo()
	{
		if (m_EntityListECS) {
			if (m_TargetEntity) {
				m_EntityListECS->push_back(m_TargetEntity);
			}
			return;
		}
		if (m_LegacyList) {
			if (m_LegacyTarget) {
				m_LegacyList->push_back(m_LegacyTarget);
			}
		}
	}
}