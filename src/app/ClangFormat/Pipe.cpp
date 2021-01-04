#pragma hdrstop

#include "Pipe.h"
#include <memory>
#include <System.SysUtils.hpp>

namespace ClangFormat
{
	Pipe::Pipe()
		: stdInRead(0x0),
		  stdInWrite(0x0),
		  stdOutRead(0x0),
		  stdOutWrite(0x0),
		  stdErrorRead(0x0),
		  stdErrorWrite(0x0),
		  openedProcess(0x0),
		  bufferSize(4096)
	{
	}

	Pipe::~Pipe()
	{
		Close();
	}

	bool Pipe::Open(String command, String startupDirectory)
	{
		bool retVal = false;
		if (!command.IsEmpty())
		{
			retVal = OpenPipeHandles();
			if (retVal)
				retVal = CreateChildProcess(command, startupDirectory);
		}

		return retVal;
	}

	void Pipe::Close()
	{
		ClosePipeHandles();
		CloseProcess();
	}

	bool Pipe::Write(const AnsiString &textToWrite)
	{
		bool retVal = false;
		if (stdInWrite)
		{
			unsigned long writtenSize;
			const char *buffer = textToWrite.c_str();
			unsigned long sizeToWrite = static_cast<unsigned long>(textToWrite.Length());
			retVal = WriteFile(stdInWrite, buffer, sizeToWrite, &writtenSize, 0x0);
		}

		return retVal;
	}

	bool Pipe::Read(HANDLE &bufferToRead, String &output)
	{
		bool retVal = false;
		output = EmptyStr;
		PrepareToReading();
		if (bufferToRead)
		{
			retVal = true;
			unsigned long readSize;
			std::unique_ptr<char[]> buffer(new char[bufferSize]);
			memset(buffer.get(), 0x0, bufferSize);
			bool readFileResult = false;
			do
			{
				readFileResult = ReadFile(bufferToRead, buffer.get(), bufferSize, &readSize, 0x0);
				if (!readFileResult || readSize == 0)
					break;

				output += String(buffer.get(), readSize);
			} while (readSize > 0);
		}

		return retVal;
	}

	bool Pipe::Read(String &output)
	{
		return Read(stdOutRead, output);
	}

	bool Pipe::ReadError(String &error)
	{
		return Read(stdErrorRead, error);
	}

	bool Pipe::OpenPipeHandles()
	{
		bool retVal = true;
		ClosePipeHandles();
		SECURITY_ATTRIBUTES securityAttributes;
		securityAttributes.nLength = sizeof(securityAttributes);
		securityAttributes.bInheritHandle = true;
		securityAttributes.lpSecurityDescriptor = 0x0;
		if (!CreatePipe(&stdOutRead, &stdOutWrite, &securityAttributes, 0))
			retVal = false;

		if (retVal && !SetHandleInformation(stdOutRead, HANDLE_FLAG_INHERIT, 0))
			retVal = false;

		if (retVal && !CreatePipe(&stdInRead, &stdInWrite, &securityAttributes, 0))
			retVal = false;

		if (retVal && !SetHandleInformation(stdInWrite, HANDLE_FLAG_INHERIT, 0))
			retVal = false;

		if (retVal && !CreatePipe(&stdErrorRead, &stdErrorWrite, &securityAttributes, 0))
			retVal = false;

		if (retVal && !SetHandleInformation(stdErrorRead, HANDLE_FLAG_INHERIT, 0))
			retVal = false;

		if (!retVal)
			ClosePipeHandles();

		return retVal;
	}

	void Pipe::ClosePipeHandles()
	{
		CloseAndClearHandle(stdOutRead);
		CloseAndClearHandle(stdOutWrite);
		CloseAndClearHandle(stdInRead);
		CloseAndClearHandle(stdInWrite);
		CloseAndClearHandle(stdErrorRead);
		CloseAndClearHandle(stdErrorWrite);
	}

	void Pipe::CloseAndClearHandle(HANDLE &handle)
	{
		if (handle && handle != INVALID_HANDLE_VALUE)
			CloseHandle(handle);

		handle = 0x0;
	}

	void Pipe::CloseProcess()
	{
		if (openedProcess && openedProcess != INVALID_HANDLE_VALUE)
		{
			DWORD exitCode;
			GetExitCodeProcess(openedProcess, &exitCode);
			if (exitCode == STILL_ACTIVE)
				TerminateProcess(openedProcess, 1);
		}

		CloseAndClearHandle(openedProcess);
	}

	bool Pipe::CreateChildProcess(String command, String startupDirectory)
	{
		bool retVal = false;
		CloseProcess();
		if (!command.IsEmpty() && stdOutWrite && stdInRead && stdErrorWrite)
		{
			PROCESS_INFORMATION processInfo;
			STARTUPINFO startupInfo;
			memset(&processInfo, 0x0, sizeof(processInfo));
			memset(&startupInfo, 0x0, sizeof(startupInfo));

			startupInfo.cb = sizeof(startupInfo);
			startupInfo.hStdError = stdErrorWrite;
			startupInfo.hStdOutput = stdOutWrite;
			startupInfo.hStdInput = stdInRead;
			startupInfo.dwFlags |= STARTF_USESTDHANDLES;

			wchar_t *startupDirectoryTemp = 0x0;
			if (!startupDirectory.IsEmpty())
				startupDirectoryTemp = startupDirectory.c_str();

			retVal = CreateProcess(0x0, command.c_str(), 0x0, 0x0, true, CREATE_NO_WINDOW, 0x0, startupDirectoryTemp, &startupInfo, &processInfo);
			if (retVal)
			{
				openedProcess = processInfo.hProcess;
				CloseAndClearHandle(processInfo.hThread);
				CloseAndClearHandle(stdOutWrite);
				CloseAndClearHandle(stdInRead);
				CloseAndClearHandle(stdErrorWrite);
			}
		}

		return retVal;
	}

	void Pipe::PrepareToReading()
	{
		if (stdInWrite)
			CloseAndClearHandle(stdInWrite);
	}
} // namespace ClangFormat
