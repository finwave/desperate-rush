/**
 * Class offers reference between DirectInput
 * scan codes and virtual-key codes.
 */

#pragma once

class CKeyReference
{
public:
	CKeyReference(void);
	virtual ~CKeyReference(void);

	/**
	 * CreateKeyArray
	 * initializes keyArray member
	 */
	void CreateKeyArray();

	/**
	 * GetHex
	 * gets a hex value from initialized char array
	 * using a given parameter as a row reference
	 * @param element number of array row
	 * @return pointer to hex (char array)
	 */
	char* GetHex(int element);

	/**
	 * CheckValidValue
	 * checks if given hex value is valid meaning
	 * if it can be found from initialized char array
	 * @param hex value to be checked
	 * @return boolean true/false
	 */
	bool CheckValidValue(char* hex);

private:
	// holds a reference array to scan codes and
	// their respective hex decimals
	char keyArray[230][2];
};