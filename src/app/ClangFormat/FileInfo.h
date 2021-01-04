#ifndef FileInfoH
#define FileInfoH

#include <System.hpp>
#include <memory>

namespace ClangFormat
{
	class FileInfo
	{
	  private:
		std::unique_ptr<wchar_t[]> verData;
		String subBlockRoot;

		void Initialize(String fileName);
		String GetStringFileInfo(String subBlockKey);

	  public:
		FileInfo(String fileName);
		String GetProductName();
		String GetProductVersion();
		String GetLegalCopyright();
		void GetBareProductVersion(int &release, int &breaking, int &feature, int &fix);
	};
} // namespace ClangFormat

#endif
