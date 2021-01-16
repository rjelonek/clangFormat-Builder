#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "IDEObserver.h"
#include "ISettingsReader.h"
#include "ISettingsWriter.h"
#include "Menu.h"
#include "Settings.h"
#include "SettingsIni.h"
#include <boost/shared_ptr.hpp>

#pragma package(smart_init)
#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

namespace ClangFormat
{
	boost::shared_ptr<Configuration::Settings> settings;
	std::unique_ptr<Observer::IDEObserver> ideObserver;
	std::unique_ptr<Menu> menu;
	void Register()
	{
		boost::shared_ptr<Configuration::Repository::SettingsIni> settingsRepo(new Configuration::Repository::SettingsIni());
		settings = boost::shared_ptr<Configuration::Settings>(new Configuration::Settings(settingsRepo, settingsRepo));
		ideObserver = std::unique_ptr<Observer::IDEObserver>(new Observer::IDEObserver(settings));
		menu = std::unique_ptr<Menu>(new Menu(settings));

		ideObserver->RegisterIDE();
		menu->Add();
	}

	void Remove() {}

#pragma startup Register
#pragma exit Remove
} // namespace ClangFormat
