#pragma once
#include <stack>
namespace Sign {
	class EditorCommand
	{
	public:
		virtual ~EditorCommand() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};


	class EditorHistory {
	public:
		EditorHistory() = default;
		virtual ~EditorHistory() { Clear(); }
		void Record(EditorCommand* command);
		void Undo();
		void Clear();
	private:
		std::stack<EditorCommand*> m_ActionsPerformed;
		std::stack<EditorCommand*> m_ActionsCancelled;
	};
}

