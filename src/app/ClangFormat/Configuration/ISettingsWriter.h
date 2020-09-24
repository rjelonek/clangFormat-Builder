#ifndef ISettingsWriterH
#define ISettingsWriterH

namespace ClangFormat
{
	namespace Configuration
	{
		class Settings;
		class ISettingsWriter
		{
		  public:
			virtual void Write(Settings &settings) = 0;
		};
	} // namespace Configuration
} // namespace ClangFormat

#endif
