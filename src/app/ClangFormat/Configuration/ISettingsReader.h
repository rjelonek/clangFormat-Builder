#ifndef ISettingsReaderH
#define ISettingsReaderH

namespace ClangFormat
{
	namespace Configuration
	{
		class Settings;
		class ISettingsReader
		{
		  public:
			virtual void Read(Settings &settings) = 0;
		};
	} // namespace Configuration
} // namespace ClangFormat

#endif
