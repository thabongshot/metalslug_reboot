#include "xmlparser.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize
    HRESULT hr = CoInitialize(NULL);
    if(SUCCEEDED(hr))
    {
		// Parse Data
		MapDataCollection* parsedData = new MapDataCollection();
        ParseAndLoadMapData(L"C:\\stocks.xml", parsedData);

		// Uninitialize
        CoUninitialize();
    }

    return 0;
}