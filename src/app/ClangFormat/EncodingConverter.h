#ifndef EncodingConverterH
#define EncodingConverterH

#include <System.hpp>
#include "Message.h"

namespace ClangFormat
{
	enum class ConvertingResult
	{
		Ok,
		AlreadySavedWithDesiredEncoding,
		Failed
	};

	namespace SystemExtension
	{
		TByteDynArray Concat(TByteDynArray &first, TByteDynArray &second);
	};

	class EncodingConverter
	{
	  private:
		Message messages;
		ConvertingResult ToUTF8Bom(String filePath);

	  public:
		bool AllFilesToUTF8Bom();
	};
}; // namespace ClangFormat
#endif
