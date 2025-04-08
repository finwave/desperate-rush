/**
 * Class offers reference between DirectInput
 * scan codes and virtual-key codes.
 */

#include "KeyReference.h"

CKeyReference::CKeyReference(void)
{
	this->CreateKeyArray();
}

CKeyReference::~CKeyReference(void)
{
}

void CKeyReference::CreateKeyArray()
{
	// first clears all the array values
	for(int i = 0; i < 230; i++)
	{
		keyArray[i][0] = 'Í';
		keyArray[i][1] = 'Í';
	}

	// key button = 1
	keyArray[1][0] = '3';
	keyArray[1][1] = '1';

	// key button = 2
	keyArray[2][0] = '3';
	keyArray[2][1] = '2';

	// key button = 3
	keyArray[3][0] = '3';
	keyArray[3][1] = '3';

	// key button = 4
	keyArray[4][0] = '3';
	keyArray[4][1] = '4';

	// key button = 5
	keyArray[5][0] = '3';
	keyArray[5][1] = '5';

	// key button = 6
	keyArray[6][0] = '3';
	keyArray[6][1] = '6';

	// key button = 7
	keyArray[7][0] = '3';
	keyArray[7][1] = '7';

	// key button = 8
	keyArray[8][0] = '3';
	keyArray[8][1] = '8';

	// key button = 9
	keyArray[9][0] = '3';
	keyArray[9][1] = '9';

	// key button = 0
	keyArray[10][0] = '3';
	keyArray[10][1] = '0';

	// key button = +
	keyArray[11][0] = 'B';
	keyArray[11][1] = 'B';

	// key button = BACKSPACE
	keyArray[13][0] = '0';
	keyArray[13][1] = '8';

	// key button = TAB
	keyArray[14][0] = '0';
	keyArray[14][1] = '9';

	// key button = Q
	keyArray[15][0] = '5';
	keyArray[15][1] = '1';

	// key button = W
	keyArray[16][0] = '5';
	keyArray[16][1] = '7';

	// key button = E
	keyArray[17][0] = '4';
	keyArray[17][1] = '5';

	// key button = R
	keyArray[18][0] = '5';
	keyArray[18][1] = '2';

	// key button = T
	keyArray[19][0] = '5';
	keyArray[19][1] = '4';

	// key button = Y
	keyArray[20][0] = '5';
	keyArray[20][1] = '9';

	// key button = U
	keyArray[21][0] = '5';
	keyArray[21][1] = '5';

	// key button = I
	keyArray[22][0] = '4';
	keyArray[22][1] = '9';

	// key button = O
	keyArray[23][0] = '4';
	keyArray[23][1] = 'F';

	// key button = P
	keyArray[24][0] = '5';
	keyArray[24][1] = '0';

	// key button = ENTER
	keyArray[27][0] = '0';
	keyArray[27][1] = 'D';

	// key button = LEFT CTRL
	keyArray[28][0] = '1';
	keyArray[28][1] = '1';

	// key button = A
	keyArray[29][0] = '4';
	keyArray[29][1] = '1';

	// key button = S
	keyArray[30][0] = '5';
	keyArray[30][1] = '3';

	// key button = D
	keyArray[31][0] = '4';
	keyArray[31][1] = '4';

	// key button = F
	keyArray[32][0] = '4';
	keyArray[32][1] = '6';

	// key button = G
	keyArray[33][0] = '4';
	keyArray[33][1] = '7';

	// key button = H
	keyArray[34][0] = '4';
	keyArray[34][1] = '8';

	// key button = J
	keyArray[35][0] = '4';
	keyArray[35][1] = 'A';

	// key button = K
	keyArray[36][0] = '4';
	keyArray[36][1] = 'B';

	// key button = L
	keyArray[37][0] = '4';
	keyArray[37][1] = 'C';

	// key button = LEFT SHIFT
	keyArray[41][0] = '1';
	keyArray[41][1] = '0';

	// key button = Z
	keyArray[43][0] = '5';
	keyArray[43][1] = 'A';

	// key button = X
	keyArray[44][0] = '5';
	keyArray[44][1] = '8';

	// key button = C
	keyArray[45][0] = '4';
	keyArray[45][1] = '3';

	// key button = V
	keyArray[46][0] = '5';
	keyArray[46][1] = '6';

	// key button = B
	keyArray[47][0] = '4';
	keyArray[47][1] = '2';

	// key button = N
	keyArray[48][0] = '4';
	keyArray[48][1] = 'E';

	// key button = M
	keyArray[49][0] = '4';
	keyArray[49][1] = 'D';

	// key button = ,
	keyArray[50][0] = 'B';
	keyArray[50][1] = 'C';

	// key button = .
	keyArray[51][0] = 'B';
	keyArray[51][1] = 'E';

	// key button = -
	keyArray[52][0] = 'B';
	keyArray[52][1] = 'D';

	// key button = RIGHT SHIFT
	keyArray[53][0] = '1';
	keyArray[53][1] = '0';

	// key button = LEFT ALT
	keyArray[55][0] = '1';
	keyArray[55][1] = '2';

	// key button = SPACEBAR
	keyArray[56][0] = '2';
	keyArray[56][1] = '0';

	// key button = RIGHT CTRL
	keyArray[156][0] = '1';
	keyArray[156][1] = '1';

	// key button = RIGHT ALT
	keyArray[183][0] = '1';
	keyArray[183][1] = '2';

	// key button = UP ARROW
	keyArray[199][0] = '2';
	keyArray[199][1] = '6';

	// key button = LEFT ARROW
	keyArray[202][0] = '2';
	keyArray[202][1] = '5';

	// key button = RIGHT ARROW
	keyArray[204][0] = '2';
	keyArray[204][1] = '7';

	// key button = DOWN ARROW
	keyArray[207][0] = '2';
	keyArray[207][1] = '8';
}

char* CKeyReference::GetHex(int element)
{
	// holds a fetched hex decimal value
	char *hex = new char[4];

	hex[0] = '0';
	hex[1] = 'x';
	hex[2] = this->keyArray[element - 1][0];
	hex[3] = this->keyArray[element - 1][1];

	return hex;
}

bool CKeyReference::CheckValidValue(char* hex)
{
	bool bValid = false;

	for(int i = 0; i < 208; i++)
	{
		// found a matching value
		if(	(hex[2] == keyArray[i][0]) && 
			(hex[3] == keyArray[i][1]))
		{
			bValid = true;
			i = 208;
		}
	}

	return bValid;
}
