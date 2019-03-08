

#define _CRT_SECURE_NO_WARNINGS
#include "ErrorState.h"
#include <iostream>
#include<cstring>

using namespace std;


namespace AMA {

	ostream& ErrorState::printout(ostream& os) {
		if (msg != nullptr) os << msg;
		return os;
	}

	ostream& operator<<(ostream& os, ErrorState& error) {
		error.printout(os);
		return os;
	}

	//This function receives the address of a C-style null 
	//terminated string that holds an error message. 
	ErrorState::ErrorState(const char* errorMessage) {

		if (errorMessage == nullptr) {
			msg = nullptr;
		}
		else {
			msg = new char[strlen(errorMessage) + 1];//extra char for null terminator
			//copies the message into the allocated memory. 
			strcpy(msg, errorMessage);
		}
	}

	//default constructor
	ErrorState:: ~ErrorState() {

		if (msg != nullptr) {
			delete[] msg;
		}
		msg = nullptr;

	}
	//clears any message stored by the current object
	//and initializes the object to a safe empty state.
	void ErrorState::clear() {
		if (msg != nullptr) {
			delete[] msg;
		}
		msg = nullptr;

	}

	//returns true if the current object is in a safe empty state.
	bool ErrorState::isClear() const {
		return msg == nullptr;
	}

	//de-allocates any memory that has been dynamically allocated by the current object.
	void ErrorState::message(const char* str) {
		if (str != nullptr) {
			delete[] msg;

			msg = nullptr;
			msg = new char[strlen(str) + 1];
			strcpy(msg, str);
		}
	}
	const char* ErrorState::message()const {
		return msg;

	}


}



