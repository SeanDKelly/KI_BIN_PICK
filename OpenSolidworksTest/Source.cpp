#include <iostream>
#include <atlbase.h>
#import "sldworks.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids //the SOLIDWORKS type library
#import "swconst.tlb"  raw_interfaces_only, raw_native_types, no_namespace, named_guids //the SOLIDWORKS constant type library

class SolidWorks {
public:
    // COM Pointer of Soldiworks object
    CComPtr<ISldWorks> SW;

    // Konstruktor
    SolidWorks() {
        // Initialisierung der COM-Bibliothek
        CoInitialize(NULL);
        // create Solidworks instance
        HRESULT hr = SW.CoCreateInstance(__uuidof(SldWorks));
        if (SW.CoCreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER) != S_OK)
        {
            std::cout << "Fehler beim öffnen von Solidworks" << std::endl;
        }

        else {
            std::cout << "Solidworks erfolgreich geoeffnet" << std::endl;
        }
        
    };

    // Destruktor
    ~SolidWorks() {
        //SW->ExitApp();// Beenden der SolidWorks-Anwendung
        CoUninitialize(); // COM schnittstelle schliesen
    }

    // Teil Öffnen
    void OpenPart(BSTR dateiPfad) {

        // Instanz von SW Bauteil Klasse welches unser zu öffnendes 
        // Bauteil halten wird
        CComPtr<IModelDoc2> model;


        // config mit der wir die Datei öffnen wir nehmen hie die
        // Default config
        BSTR config = SysAllocString(L"Default");
        CComBSTR sDefaultConfiguration(L"Default");


        // Die Öffnen Funktion will wissen ob es sich um ein Bautel,
        // Zeichnung oder Baugruppe handelt. Hier öffnen wir ein PART also
        // ein Bauteil.
        int documentType = (int)swDocumentTypes_e::swDocPART;
        
        
        // Variable um Fehler zu speichern
        long lErrors;

        // Variable um Warnunge nzu speichern
        long lWarnings;


        // Bauteil öffnen
        SW->OpenDoc6(
            dateiPfad,
            swDocPART,
            swOpenDocOptions_Silent,
            sDefaultConfiguration,
            &lErrors,
            &lWarnings,
            &model);


        if (model != NULL) {
            std::wcout << "Teil erfolgreich geoeffnet" << std::endl;
        }

        else {
            std::wcout << "Fehler beim oeffnen des Teils" << std::endl;
        }
    }
};



int main()
{
    SolidWorks SW;
    
    // Hier den Entsprechenden Dateipfad eingebn zu dem Teil das man öffnen will
    CComBSTR dateiPfad = (L"C:\\Users\\theja\\Downloads\\Greifer.SLDPRT");
    
    
    SW.OpenPart(dateiPfad);
    return 0;
}

// swApp->put_Visible(VARIANT_TRUE);
