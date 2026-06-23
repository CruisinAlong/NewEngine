#include "signpch.h"
#include "EditorCommand.h"

namespace Sign {
	void EditorHistory::Record(EditorCommand* command)
	{
		m_ActionsPerformed.push(command);
	}
	void EditorHistory::Undo()
	{
		if (m_ActionsPerformed.empty()) return;

		auto action = m_ActionsPerformed.top();
		action->Undo();
		m_ActionsCancelled.push(action);
		m_ActionsPerformed.pop();
	}
	void EditorHistory::Clear()
	{
		while (!m_ActionsPerformed.empty()) {
			delete m_ActionsPerformed.top();
			m_ActionsPerformed.pop();
		}
	}
}