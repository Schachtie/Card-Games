/*
*	Class Header: User
*/

#ifndef USER_H
#define USER_H

//Header Files
#include <string>

class User
{
public:
	//Constructors & Destructor
	User(); //default
	User(const std::string& name); //name provided
	~User() { }

	// Public Static Data Members
	static const unsigned int s_iSTARTINGCREDITS = 2500;

	// Public Get and Set Functions
	unsigned int getCredits() const;
	std::string getUserName() const;
	void setCredits(unsigned int newValue);
	void setUserName(const std::string& newName);

protected:
private:
	// Private Data Members
	std::string m_sUserName;
	unsigned int m_iCredits;
};

#endif