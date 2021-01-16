#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "SettingsIni.h"
#include "Message.h"
#include <System.IOUtils.hpp>

namespace ClangFormat
{
	namespace Configuration
	{
		namespace Repository
		{
			SettingsIni::SettingsIni()
			{
				appIni = std::unique_ptr<TMemIniFile>(new TMemIniFile(GetFilePath(), TEncoding::UTF8));
			}

			bool SettingsIni::CreateDirectoryIfNotExists(String path)
			{
				if (!TDirectory::Exists(path))
					TDirectory::CreateDirectory(path);

				return TDirectory::Exists(path);
			}

			String SettingsIni::GetPath()
			{
				return TPath::GetHomePath() + "/clangFormat";
			}

			String SettingsIni::GetFilePath()
			{
				return GetPath() + "/app.ini";
			}

			void SettingsIni::Read(Settings &settings)
			{
				settings.general.autoFormatting = appIni->ReadBool("General", "AutoFormatting", settings.general.autoFormatting);
				settings.general.style = appIni->ReadString("General", "Style", settings.general.style);
				settings.general.fallbackStyle = appIni->ReadString("General", "FallbackStyle", settings.general.fallbackStyle);
				settings.general.clangFormatPath = appIni->ReadString("General", "ClangFormatPath", settings.general.clangFormatPath);

				settings.shortcuts.autoFormatting = appIni->ReadInteger("Shortcuts", "AutoFormatting", settings.shortcuts.autoFormatting);
				settings.shortcuts.formatAllSources = appIni->ReadInteger("Shortcuts", "FormatAllSources", settings.shortcuts.formatAllSources);
				settings.shortcuts.formatSelectedLines = appIni->ReadInteger("Shortcuts", "FormatSelectedLines", settings.shortcuts.formatSelectedLines);
			}

			void SettingsIni::Write(Settings &settings)
			{
				try
				{
					appIni->WriteBool("General", "AutoFormatting", settings.general.autoFormatting);
					appIni->WriteString("General", "Style", settings.general.style);
					appIni->WriteString("General", "FallbackStyle", settings.general.fallbackStyle);
					appIni->WriteString("General", "ClangFormatPath", settings.general.clangFormatPath);

					appIni->WriteInteger("Shortcuts", "AutoFormatting", settings.shortcuts.autoFormatting);
					appIni->WriteInteger("Shortcuts", "FormatAllSources", settings.shortcuts.formatAllSources);
					appIni->WriteInteger("Shortcuts", "FormatSelectedLines", settings.shortcuts.formatSelectedLines);

					if (CreateDirectoryIfNotExists(GetPath()))
					{
						ClangFormat::Message().AddInfo("Saving settings at location " + appIni->FileName);
						appIni->UpdateFile();
					}
				}
				catch (Exception &ex)
				{
					ClangFormat::Message().AddError(ex.Message, __FUNC__);
				}
			}

		} // namespace Repository
	}	  // namespace Configuration
} // namespace ClangFormat
