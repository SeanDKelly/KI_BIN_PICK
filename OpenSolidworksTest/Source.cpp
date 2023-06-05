#include <atlbase.h>

#import "sldworks.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids  // SOLIDWORKS type library

#import "swconst.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids   // SOLIDWORKS constants type library

int main()
{
	// Initialize COM
	// Do this before using ATL smart pointers so COM is available.
	CoInitialize(NULL);

	// Use a block, so the smart pointers are destructed when the scope of this block is left
	{
		// COM Pointer of Soldiworks object
		CComPtr<ISldWorks> swApp;

		// Create an instance of Solidworks application
		// If it fails then return 0 and close program
		if (swApp.CoCreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER) != S_OK)
		{
			// Stop COM 
			CoUninitialize();
			return(0);
		}

		// If created successfully, then visible the Solidworks
		swApp->put_Visible(VARIANT_TRUE);

		// COM Style String for message to user
		CComBSTR _messageToUser(L"Hello World!!! I am from Solidworks C++ API.");

		// long type variable to store the result value by user
		long _lMessageResult;

		// Send a message to user and store the return value in _lMessageResult by referencing it
		swApp->SendMsgToUser2(_messageToUser, swMessageBoxIcon_e::swMbInformation, swMessageBoxBtn_e::swMbOk, &_lMessageResult);
	}

	// Stop COM 
	CoUninitialize();
}
