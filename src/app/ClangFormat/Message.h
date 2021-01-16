#ifndef MessageH
#define MessageH

#include <System.hpp>

namespace ClangFormat
{
	class Message
	{
	  private:
		String infoGroupName;
		String errorGroupName;
		void *parent;
		void *lineRef;

		void AddMsg(String text, String prefix, String groupName);

	  public:
		Message();
		void AddError(String text);
		void AddError(String text, String prefix);
		void AddInfo(String text);
		void AddSubInfo(String text);
		void AddTitle(String text);
		void AddSeparator();
	};
} // namespace ClangFormat

#endif
