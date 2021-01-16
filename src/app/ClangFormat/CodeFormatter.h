#ifndef CodeFormatterH
#define CodeFormatterH

#include "Message.h"
#include "Settings.h"
#include <ToolsAPI.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

namespace ClangFormat
{
	enum class FormatResult
	{
		Ok,
		NotSupportedFile,
		FormattingFailed,
		EditorNotAvailable
	};

	class CodeFormatter
	{
	  private:
		boost::shared_ptr<Configuration::Settings> settings;
		Message messages;

		String GetText(_di_IOTASourceEditor sourceEditor, int &editorSize);
		void SetText(_di_IOTASourceEditor sourceEditor, int editorSize, String textToSet);
		FormatResult FormatSource(_di_IOTASourceEditor sourceEditor, unsigned int startLine, unsigned int endLine);
		void GetBookmarkList(_di_IOTASourceEditor sourceEditor, std::map<int, TOTACharPos> &bookmarkList);
		void SetBookmarkList(_di_IOTASourceEditor sourceEditor, std::map<int, TOTACharPos> &bookmarkList);

	  public:
		CodeFormatter(boost::shared_ptr<Configuration::Settings> settings);
		FormatResult FormatSource(_di_IOTASourceEditor sourceEditor);
		FormatResult FormatCurrentSource();
		FormatResult FormatSelectedLines();
		bool FormatAllSources();
	};
}; // namespace ClangFormat

#endif
