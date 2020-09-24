#ifndef SettingsH
#define SettingsH

#include "General.h"
#include "Shortcuts.h"
#include "ISettingsReader.h"
#include "ISettingsWriter.h"
#include <boost/shared_ptr.hpp>

namespace ClangFormat
{
	namespace Configuration
	{
		class Settings
		{
		  private:
			boost::shared_ptr<ISettingsReader> reader;
			boost::shared_ptr<ISettingsWriter> writer;

		  public:
			Settings(boost::shared_ptr<ISettingsReader> reader, boost::shared_ptr<ISettingsWriter> writer);
			void SetDefaultValues();
			void Save();

			General general;
			Shortcuts shortcuts;
		};
	}; // namespace Configuration
};	   // namespace ClangFormat
#endif
