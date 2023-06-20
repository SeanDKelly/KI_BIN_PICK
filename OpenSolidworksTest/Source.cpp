#include <iostream>
#include <atlbase.h>
#import "sldworks.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids //the SOLIDWORKS type library
#import "swconst.tlb"  raw_interfaces_only, raw_native_types, no_namespace, named_guids //the SOLIDWORKS constant type library

int main()
{
    // Initialisierung der COM-Bibliothek
    CoInitialize(NULL);

    {
        // COM Pointer of Soldiworks object
        CComPtr<ISldWorks> swApp;
        CComPtr<IModelDoc2> model;

        // SolidWorks-Anwendung erstellen
        //SldWorks::ISldWorksPtr swApp;

        HRESULT hr = swApp.CoCreateInstance(__uuidof(SldWorks));
        if (swApp.CoCreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER) != S_OK)
        {
            std::cout << "Fehler beim Erstellen der SolidWorks-Anwendung!" << std::endl;
            CoUninitialize(); // COM schnittstelle schliesen
            return(0);
        }

        else {
            std::cout << "SW erfolgreich geoeffnet" << std::endl;
        }
   
        // SolidWorks-Datei öffnen


        // COM Pointer of Soldiworks Model Document
        
        BSTR dateiPfad = SysAllocString(L"C:\\Users\\theja\\Downloads\\Greifer.SLDPRT");
        BSTR config = SysAllocString(L"Default");
        CComBSTR sDefaultConfiguration(L"Default");

        int documentType = (int)swDocumentTypes_e::swDocPART;
        long lErrors;
        long lWarnings;
        long lMateError;


        swApp->OpenDoc6(
            dateiPfad,
            swDocPART,
            swOpenDocOptions_Silent,
            sDefaultConfiguration,
            &lErrors,
            &lWarnings,
            &model);
        
        swApp->put_Visible(VARIANT_TRUE);



        if (model != NULL) {
            std::wcout << "Erfolgreich geoeffnet" << std::endl;
        }

        else {
            std::wcout << "Fehler beim oeffnen" << std::endl;
            // Beenden der SolidWorks-Anwendung
            swApp->ExitApp();
        }

    

        

        // Bereinigung der COM-Bibliothek


    }
    CoUninitialize();

    return 0;
}
