#ifndef ThemingH
#define ThemingH

#include <System.Classes.hpp>

namespace ClangFormat
{
	class Theming
	{
	  private:
		bool themingSupported;

	  public:
		Theming();
		void RegisterFormClass(TMetaClass *classType, TComponent *component);
		bool IsThemingSupported();
	};
} // namespace ClangFormat

#endif
