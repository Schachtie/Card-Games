/*
*	Class Definitions: User
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Holds user's data between games and in main program.
* 
*			Provides the following functionalities:
*				- Set and Get functions: credits, userName
*/


// Header Files
#include "User.h"

using namespace std;



// Constructors

User::User() {
	setCredits(s_iSTARTINGCREDITS);
} //end of "Default Constructor"


User::User(const string& name) {
	this->User::User();
	setUserName(name);
} //end of "Name Constructor"



// Public Get and Set Functions

/*	Public Get Functions
*
*	@note:	All get functions have the following parameters and respective return types.
*
*	@param: void
*
*	@return: Respective type of each private/protected data member.
*/

unsigned int User::getCredits() const {
	return m_iCredits;
} //end of "getCredits"


string User::getUserName() const {
	return m_sUserName;
} //end of "getUserName"


/*	Public Set Functions
*
*	@note:	All set functions have the following parameters and respective return types.
*
*	@param: Respective type of each private/protected data member.
*
*	@return: void
*/

void User::setCredits(unsigned int newValue) {
	m_iCredits = newValue;
} //end of "setCredits"


void User::setUserName(const string& newName) {
	m_sUserName = newName;
} //end of "setUserName"