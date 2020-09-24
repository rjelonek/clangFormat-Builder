#pragma hdrstop

#include "Message.h"
#include <ToolsAPI.hpp>

namespace ClangFormat
{
	Message::Message() : infoGroupName("clangFormat"), errorGroupName("clangFormat - errors"), parent(0x0), lineRef(0x0) {}

	void Message::AddMsg(String text, String prefix, String groupName)
	{
		_di_IOTAMessageServices services;
		if (BorlandIDEServices && BorlandIDEServices->Supports(services))
		{
			_di_IOTAMessageGroup messageGroup = services->GetGroup(groupName);
			if (!messageGroup)
			{
				messageGroup = services->AddMessageGroup(groupName);
				messageGroup->AutoScroll = true;
				services->ShowMessageView(messageGroup);
			}
			else
				services->ShowMessageView(0x0);

			services->AddToolMessage("", text, prefix, 0, 0, parent, lineRef, messageGroup);
		}
	}

	void Message::AddError(String text)
	{
		AddMsg(text, "", errorGroupName);
	}

	void Message::AddError(String text, String prefix)
	{
		AddMsg(text, prefix, errorGroupName);
	}

	void Message::AddInfo(String text)
	{
		AddMsg(text, "", infoGroupName);
	}

	void Message::AddSubInfo(String text)
	{
		AddInfo("\t" + text);
	}

	void Message::AddTitle(String text)
	{
		String groupName = infoGroupName;
		_di_IOTAMessageServices services;
		if (BorlandIDEServices && BorlandIDEServices->Supports(services))
		{
			_di_IOTAMessageGroup messageGroup = services->GetGroup(groupName);
			if (!messageGroup)
			{
				messageGroup = services->AddMessageGroup(groupName);
				messageGroup->AutoScroll = true;
				services->ShowMessageView(messageGroup);
			}

			services->AddTitleMessage(text, messageGroup);
		}
	}

	void Message::AddSeparator()
	{
		AddInfo("_________________________________________");
	}
} // namespace ClangFormat
