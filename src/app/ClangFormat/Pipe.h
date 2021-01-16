#ifndef PipeH
#define PipeH

#include <System.hpp>

namespace ClangFormat
{
	class Pipe
	{
	  private:
		HANDLE stdInRead;
		HANDLE stdInWrite;
		HANDLE stdOutRead;
		HANDLE stdOutWrite;
		HANDLE stdErrorRead;
		HANDLE stdErrorWrite;
		HANDLE openedProcess;
		const int bufferSize;

		bool OpenPipeHandles();
		void ClosePipeHandles();
		void CloseAndClearHandle(HANDLE &handle);
		void CloseProcess();
		bool CreateChildProcess(String command, String startupDirectory);
		void PrepareToReading();
		bool Read(HANDLE &bufferToRead, String &output);

	  public:
		Pipe();
		~Pipe();
		bool Open(String command, String startupDirectory);
		void Close();
		bool Write(const AnsiString &textToWrite);
		bool Read(String &output);
		bool ReadError(String &error);
	};
} // namespace ClangFormat

#endif
