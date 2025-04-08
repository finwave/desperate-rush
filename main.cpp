/**
 * This file contains the 'main' function.
 * Program execution begins and ends there.
 */

#include "TheApp.h"

int main()
{
	HRESULT hres;
	CTheApp app;

	hres = app.Create(	1024,
						768,
						32,
						FALSE,
						_T("Desperate Rush"),
						0);

	if (FAILED(hres))
	{
		::MessageBox(	NULL,
						_T("Failed to create application"),
						_T("ERROR!"),
						MB_OK);
		return 0;
	}

	int retval = app.Run();
	return retval;
}
