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

        // SolidWorks-Anwendung erstellen
        //SldWorks::ISldWorksPtr swApp;

        HRESULT hr = swApp.CoCreateInstance(__uuidof(SldWorks));
        if (FAILED(hr))
        {
            std::cout << "Fehler beim Erstellen der SolidWorks-Anwendung!" << std::endl;
            CoUninitialize();
            return -1;
        }
   
        // SolidWorks-Datei �ffnen


        // COM Pointer of Soldiworks Model Document
        CComPtr<IModelDoc2> model;
        VARIANT_BOOL status = VARIANT_FALSE;
        BSTR dateiPfad = SysAllocString(L"C:\\Users\\theja\\Downloads\\Greifer.SLDPRT");
        BSTR config = SysAllocString(L"");

        swApp->OpenDoc6(
            dateiPfad, // Pfad zur SolidWorks-Datei
            1,      // Dateityp: 1 f�r Teil, 2 f�r Baugruppe, usw.
            1,      // Optionen: 1 f�r Aktualisieren des Ansichtsbereichs, 0 f�r Standardoptionen
            config, // Keine spezifische Konfiguration
            0,   // Keine Fehler-R�ckgabe
            0,   // Keine Warnungen-R�ckgabe
            &model
        );
        

        if (model != NULL) {
            std::wcout << "Erfolgreich geoeffnet" << std::endl;
        }

        else {
            std::wcout << "Fehler beim oeffnen" << std::endl;
        }

    

        // Beenden der SolidWorks-Anwendung
        swApp->ExitApp();

        // Bereinigung der COM-Bibliothek


    }
    CoUninitialize();

    return 0;
}
