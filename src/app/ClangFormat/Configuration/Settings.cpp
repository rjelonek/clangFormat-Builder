#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "Settings.h"

namespace ClangFormat
{
	namespace Configuration
	{
		Settings::Settings(boost::shared_ptr<ISettingsReader> reader, boost::shared_ptr<ISettingsWriter> writer) : reader(reader), writer(writer)
		{
			if (reader != 0x0)
				reader->Read(*this);
		}

		void Settings::SetDefaultValues()
		{
			general.SetDefaultValues();
			shortcuts.SetDefaultValues();
		}

		void Settings::Save()
		{
			if (writer != 0x0)
				this->writer->Write(*this);
		}
	}; // namespace Configuration
};	   // namespace ClangFormat
