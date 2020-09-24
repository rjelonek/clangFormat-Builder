#ifndef SettingsIniH
#define SettingsIniH

#include "Settings.h"
#include "ISettingsReader.h"
#include "ISettingsWriter.h"
#include <System.IniFiles.hpp>
#include <memory>

namespace ClangFormat
{
	namespace Configuration
	{
		namespace Repository
		{
			class SettingsIni : public ISettingsReader, public ISettingsWriter
			{
			  private:
				std::unique_ptr<TMemIniFile> appIni;
				bool CreateDirectoryIfNotExists(String path);
				String GetPath();
				String GetFilePath();

			  public:
				SettingsIni();
				void Read(Settings &settings);
				void Write(Settings &settings);
			};
		} // namespace Repository
	}	  // namespace Configuration
} // namespace ClangFormat

#endif
