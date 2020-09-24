#ifndef CodeFormatterH
#define CodeFormatterH

#include <ToolsAPI.hpp>
#include "Settings.h"
#include "Message.h"
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
		bool FormatSource(String filePath, String style, String fallbackStyle);
		void GetBookmarkList(_di_IOTASourceEditor sourceEditor, std::map<int, TOTACharPos> &bookmarkList);
		void SetBookmarkList(_di_IOTASourceEditor sourceEditor, std::map<int, TOTACharPos> &bookmarkList);

	  public:
		CodeFormatter(boost::shared_ptr<Configuration::Settings> settings);
		FormatResult FormatSource(_di_IOTASourceEditor sourceEditor);
		FormatResult FormatCurrentSource();
		bool FormatAllSources();
	};
}; // namespace ClangFormat
#endif
