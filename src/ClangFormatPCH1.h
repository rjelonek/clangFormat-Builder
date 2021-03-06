﻿#ifndef ClangFormatPCH1H
#define ClangFormatPCH1H

#ifdef _WIN32
#include <tchar.h>
#endif
#include <vcl.h>
#pragma option push
#pragma warn - 8070 // Function should return a value
#include <memory>
#pragma option pop
#include "Settings.h"
#include <System.IOUtils.hpp>
#include <ToolsAPI.hpp>
#include <boost/shared_ptr.hpp>

#endif
