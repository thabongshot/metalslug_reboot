#include "xmlparser.h"

// Helper function to create a VT_BSTR variant from a null terminated string. 
HRESULT VariantFromString(PCWSTR wszValue, VARIANT &Variant)
{
    HRESULT hr = S_OK;
    BSTR bstr = SysAllocString(wszValue);
    CHK_ALLOC(bstr);

    V_VT(&Variant)   = VT_BSTR;
    V_BSTR(&Variant) = bstr;

CleanUp:
    return hr;
}

// Helper function to create a DOM instance. 
HRESULT CreateAndInitDOM(IXMLDOMDocument **ppDoc)
{
    HRESULT hr = CoCreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));
    if (SUCCEEDED(hr))
    {
        // these methods should not fail so don't inspect result
        (*ppDoc)->put_async(VARIANT_FALSE);  
        (*ppDoc)->put_validateOnParse(VARIANT_FALSE);
        (*ppDoc)->put_resolveExternals(VARIANT_FALSE);
    }
    return hr;
}

// parse map data to load DOM
void ParseAndLoadMapData(TCHAR* mapDataPath, MapDataCollection* loadedData)
{
	HRESULT hr = S_OK;
    IXMLDOMDocument *pXMLDom=NULL;
    IXMLDOMParseError *pXMLErr = NULL;

    BSTR bstrXML = NULL;
    BSTR bstrErr = NULL;
    VARIANT_BOOL varStatus;
    VARIANT varFileName;
    VariantInit(&varFileName);

    CHK_HR(CreateAndInitDOM(&pXMLDom));    

    // XML file name to load
    CHK_HR(VariantFromString(mapDataPath, varFileName));
    CHK_HR(pXMLDom->load(varFileName, &varStatus));

	CHK_HR(pXMLDom->load(varFileName, &varStatus));
    if (varStatus == VARIANT_TRUE)
    {
        CHK_HR(pXMLDom->get_xml(&bstrXML));
        fprintf(stderr, "XML DOM loaded from stocks.xml:\n\n");

		// TODO: Load Data from DOM
		// TODO: Fill Below
    }
    else
    {
        // Failed to load xml, get last parsing error
        CHK_HR(pXMLDom->get_parseError(&pXMLErr));
        CHK_HR(pXMLErr->get_reason(&bstrErr));
        fprintf(stderr, "Failed to load DOM from stocks.xml %S \n", bstrErr);
    }

CleanUp:
    SAFE_RELEASE(pXMLDom);
    SAFE_RELEASE(pXMLErr);
    SysFreeString(bstrXML);
    SysFreeString(bstrErr);
    VariantClear(&varFileName);
}
