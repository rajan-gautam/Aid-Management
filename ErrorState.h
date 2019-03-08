

#include <iostream>

#ifndef ERRORSTATE_H
#define ERRORSTATE_H

using namespace std;

namespace AMA {
	class ErrorState
	{
		char * msg;

	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;//

		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();
		void clear();

		bool isClear() const;
		void message(const char* str);
		const char* message()const;
		ostream& printout(ostream& os);
	};
	//helper
	ostream& operator<<(ostream& os, ErrorState& error);

}

#endif // !ERRORSTATE_H


