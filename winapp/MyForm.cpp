#define _WIN32_DCOM
#include <iostream>
#include "MyForm.h"
#include <comdef.h>
#include <Wbemidl.h>
#include <intrin.h>
#include <comutil.h>
#include "string"
#include <windows.h>
#include <tchar.h>
using namespace std;
using namespace winapp;
#pragma comment(lib, "wbemuuid.lib")

#pragma region COM Intialization



HRESULT COMInitialize(){
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		/*cout << "Failed to initialize COM library. Error code = 0x"
			<< hex << hr << endl;*/
		System::Windows::Forms::MessageBox::Show("Failed to initialize COM library");
		return 1;                  // Program has failed.
	}



	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hr))
	{
		/*cout << "Failed to initialize security. Error code = 0x"
			<< hex << hr << endl;*/
		System::Windows::Forms::MessageBox::Show("Failed to initialize COM library");
		CoUninitialize();
		return 1;                    // Program has failed.
	}
	return hr;
}



#pragma endregion





#pragma region Stucture

struct myTest{

	string manufacturer;
	string name;
	string serial;
	string osCaption;
	string osManufacturer;
	string osBuildNumber;
	string procCurrentVoltage;
	string procTemp;
	string HDcaption;
	string HDserialNumber;




}info;

#pragma endregion



#pragma region All About Operating System

HRESULT GetOperatingSystemInfo(HRESULT h)

{
	HRESULT hr = h;
	//string manufacturer,name,sr,product;
	if (!SUCCEEDED(hr))
	{
		/*cout << "Error" << endl;*/
		System::Windows::Forms::MessageBox::Show("Error!");
	}
	else
	{

		IWbemLocator *pLocator;
		hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
		if (SUCCEEDED(hr))
		{

			IWbemServices *pServices;
			BSTR ns = SysAllocString(L"root\\cimv2");
			hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
			pLocator->Release();
			SysFreeString(ns);

			if (SUCCEEDED(hr))
			{
				BSTR query = SysAllocString(L"SELECT * FROM Win32_OperatingSystem");
				BSTR wql = SysAllocString(L"WQL");
				IEnumWbemClassObject *pEnum;
				hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
				SysFreeString(wql);
				SysFreeString(query);
				pServices->Release();
				if (SUCCEEDED(hr))
				{
					IWbemClassObject *pObject;
					ULONG returned;
					hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
					pEnum->Release();


					if (SUCCEEDED(hr))
					{

						VARIANT v, v1, v2;
						HRESULT hr1, hr2;
						VariantInit(&v);
						VariantInit(&v1);
						VariantInit(&v2);

						hr = pObject->Get(L"Caption", 0, &v, NULL, NULL);
						hr1 = pObject->Get(L"Manufacturer", 0, &v1, NULL, NULL);
						hr2 = pObject->Get(L"BuildNumber", 0, &v2, NULL, NULL);


						if (SUCCEEDED(hr) && SUCCEEDED(hr1) && SUCCEEDED(hr2) && v.vt == VT_BSTR && v1.vt == VT_BSTR && v2.vt == VT_BSTR)
						{
							info.osCaption = (const char*)_bstr_t(V_BSTR(&v));
							info.osManufacturer = (const char*)_bstr_t(V_BSTR(&v1));
							info.osBuildNumber = (const char*)_bstr_t(V_BSTR(&v2));
							VariantClear(&v);
							VariantClear(&v1);
							VariantClear(&v2);
						}
						pObject->Release();

					}
				}
			}
			if (hr == S_OK)
			{
				CoUninitialize();
			}
		}
	}
	return hr;
}




#pragma endregion




#pragma region All About Motherboard


HRESULT GetMotherboardInfo(HRESULT h)

{
	HRESULT hr = h;
	//string manufacturer,name,sr,product;
	if (!SUCCEEDED(hr))
	{
		/*cout << "Error" << endl;*/
		System::Windows::Forms::MessageBox::Show("Error");
	}
	else
	{
		
		IWbemLocator *pLocator;
		hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
		if (SUCCEEDED(hr))
		{

			IWbemServices *pServices;
			BSTR ns = SysAllocString(L"root\\cimv2");
			hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
			pLocator->Release();
			SysFreeString(ns);

			if (SUCCEEDED(hr))
			{
				BSTR query = SysAllocString(L"SELECT * FROM Win32_BaseBoard");
				BSTR wql = SysAllocString(L"WQL");
				IEnumWbemClassObject *pEnum;
				hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
				SysFreeString(wql);
				SysFreeString(query);
				pServices->Release();
				if (SUCCEEDED(hr))
				{
					IWbemClassObject *pObject;
					ULONG returned;
					hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
					pEnum->Release();


					if (SUCCEEDED(hr))
					{

						VARIANT v, v1, v2, v3;
						HRESULT hr1, hr2, hr3;
						VariantInit(&v);
						VariantInit(&v1);
						VariantInit(&v2);
						VariantInit(&v3);
						hr = pObject->Get(L"Manufacturer", 0, &v, NULL, NULL);
						hr1 = pObject->Get(L"Name", 0, &v1, NULL, NULL);
						hr2 = pObject->Get(L"SerialNumber", 0, &v2, NULL, NULL);
						hr3 = pObject->Get(L"product", 0, &v3, NULL, NULL);


						if (SUCCEEDED(hr) && SUCCEEDED(hr1) && SUCCEEDED(hr2) && SUCCEEDED(hr3) && v.vt == VT_BSTR && v1.vt == VT_BSTR && v2.vt == VT_BSTR && v3.vt == VT_BSTR)
						{
							info.manufacturer = (const char*)_bstr_t(V_BSTR(&v));
							info.name = (const char*)_bstr_t(V_BSTR(&v1));
							info.serial = (const char*)_bstr_t(V_BSTR(&v2));
							VariantClear(&v);
							VariantClear(&v1);
							VariantClear(&v2);
							VariantClear(&v3);
						}
						pObject->Release();

					}
				}
			}
			if (hr == S_OK)
			{
				CoUninitialize();
			}
		}
	}
	return hr;
}


#pragma endregion



#pragma region All About CPU


string GetCpuName(){

	// Get extended ids.
	int CPUInfo[4] = { -1 };
	__cpuid(CPUInfo, 0x80000000);
	unsigned int nExIds = CPUInfo[0];

	// Get the information associated with each extended ID.
	char CPUBrandString[0x40] = { 0 };
	for (unsigned int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);

		// Interpret CPU brand string and cache information.
		if (i == 0x80000002)
		{
			memcpy(CPUBrandString,
				CPUInfo,
				sizeof(CPUInfo));
		}
		else if (i == 0x80000003)
		{
			memcpy(CPUBrandString + 16,
				CPUInfo,
				sizeof(CPUInfo));
		}
		else if (i == 0x80000004)
		{
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}
	}

	return CPUBrandString;
}



HRESULT GetCpuTemperature(LPLONG pTemperature, HRESULT h)
{
	HRESULT hr = h;
	if (pTemperature == NULL)
		return E_INVALIDARG;
	*pTemperature = -1;

	
	if (!SUCCEEDED(hr)){
		/*cout << "Error" << endl;*/
		System::Windows::Forms::MessageBox::Show("Error!");
	}
	else
	{
		IWbemLocator *pLocator;
		hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
		if (SUCCEEDED(hr))
		{

			IWbemServices *pServices;
			BSTR ns = SysAllocString(L"root\\wmi");
			hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
			pLocator->Release();
			SysFreeString(ns);

			if (SUCCEEDED(hr))
			{
				BSTR query = SysAllocString(L"SELECT * FROM MSAcpi_ThermalZoneTemperature");
				BSTR wql = SysAllocString(L"WQL");
				IEnumWbemClassObject *pEnum;
				hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
				SysFreeString(wql);
				SysFreeString(query);
				pServices->Release();
				if (SUCCEEDED(hr))
				{
					IWbemClassObject *pObject;
					ULONG returned;
					hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
					pEnum->Release();


					if (SUCCEEDED(hr))
					{
						BSTR temp = SysAllocString(L"CurrentTemperature");
						VARIANT v;
						VariantInit(&v);
						hr = pObject->Get(temp, 0, &v, NULL, NULL);
						pObject->Release();
						SysFreeString(temp);
						if (SUCCEEDED(hr))
						{
							*pTemperature = V_I4(&v);
							*pTemperature = ((long)*pTemperature / 10) - 273.15;
						}

						VariantClear(&v);
					}
				}
			}
			if (hr == S_OK)
			{
				CoUninitialize();
			}
		}
	}
	return hr;
}




HRESULT GetCpuVoltage(LPLONG pVolt, HRESULT h)
{
	HRESULT hr = h;
	if (pVolt == NULL)
		return E_INVALIDARG;
	*pVolt = NULL;

	if (!SUCCEEDED(hr)){
		/*cout << "Error" << endl;*/
		System::Windows::Forms::MessageBox::Show("Error!");
	}
	else
	{
		IWbemLocator *pLocator;
		hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
		if (SUCCEEDED(hr))
		{

			IWbemServices *pServices;
			BSTR ns = SysAllocString(L"root\\wmi");
			hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
			pLocator->Release();
			SysFreeString(ns);

			if (SUCCEEDED(hr))
			{
				BSTR query = SysAllocString(L"SELECT * FROM Win32_Processor");
				BSTR wql = SysAllocString(L"WQL");
				IEnumWbemClassObject *pEnum;
				hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
				SysFreeString(wql);
				SysFreeString(query);
				pServices->Release();
				if (SUCCEEDED(hr))
				{
					IWbemClassObject *pObject;
					ULONG returned;
					hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
					pEnum->Release();


					if (SUCCEEDED(hr))
					{
						BSTR temp = SysAllocString(L"CurrentVoltage");
						VARIANT v;
						VariantInit(&v);
						hr = pObject->Get(temp, 0, &v, NULL, NULL);
						pObject->Release();
						SysFreeString(temp);
						if (SUCCEEDED(hr))
						{
							*pVolt = V_I4(&v);
						}

						VariantClear(&v);
					}
				}
			}
			if (hr == S_OK)
			{
				CoUninitialize();
			}
		}
	}
	return hr;
}





#pragma endregion



#pragma region All About Hard Disk




HRESULT GetHardDriveInfo(HRESULT h, LPLONG HDsize)

{
	HRESULT hr = h;
	if (*HDsize == NULL)
		return E_INVALIDARG;
	*HDsize = -1;
	//string manufacturer,name,sr,product;
	if (!SUCCEEDED(hr)){
		//cout << "Error" << endl;
		System::Windows::Forms::MessageBox::Show("Error!");
	}
	else
	{

		IWbemLocator *pLocator;
		hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
		if (SUCCEEDED(hr))
		{

			IWbemServices *pServices;
			BSTR ns = SysAllocString(L"root\\cimv2");
			hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
			pLocator->Release();
			SysFreeString(ns);

			if (SUCCEEDED(hr))
			{
				BSTR query = SysAllocString(L"SELECT * FROM Win32_DiskDrive");
				BSTR wql = SysAllocString(L"WQL");
				IEnumWbemClassObject *pEnum;
				hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
				SysFreeString(wql);
				SysFreeString(query);
				pServices->Release();
				if (SUCCEEDED(hr))
				{
					IWbemClassObject *pObject;
					ULONG returned;
					hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
					pEnum->Release();


					if (SUCCEEDED(hr))
					{
						VARIANT v, v1, v2;
						HRESULT hr1, hr2;
						VariantInit(&v);
						VariantInit(&v1);
						VariantInit(&v2);

						hr = pObject->Get(L"Caption", 0, &v, NULL, NULL);
						hr1 = pObject->Get(L"SerialNumber", 0, &v1, NULL, NULL);
						hr2 = pObject->Get(L"Partitions", 0, &v2, NULL, NULL);


						if (SUCCEEDED(hr) && SUCCEEDED(hr1) && SUCCEEDED(hr2) && v.vt == VT_BSTR && v1.vt == VT_BSTR)
						{
							info.HDcaption = (const char*)_bstr_t(V_BSTR(&v));
							info.HDserialNumber = (const char*)_bstr_t(V_BSTR(&v1));
							*HDsize = V_I4(&v2);
							VariantClear(&v);
							VariantClear(&v1);
							VariantClear(&v2);
						}
						pObject->Release();

					}
				}
			}
			if (hr == S_OK)
			{
				CoUninitialize();
			}
		}
	}
	return hr;
}



#pragma endregion



int main(array<System::String ^> ^args)
{
	FreeConsole();

	HRESULT hr=COMInitialize();
	
		// Enabling Windows XP visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		//........... Bussiness Logic..............//

		MyForm^ myForm = gcnew MyForm();

#pragma region CPU Informaton

		//cpu name
		string cpuname = GetCpuName();
		String^ str2 = gcnew String(cpuname.c_str());
		myForm->label9->Text = str2->Trim();


		//cpu temperature
		LONG temp;
		GetCpuTemperature(&temp, hr);
		myForm->label6->Text = temp + " \xB0" + "C";



		//cpu voltages
		LONG voltage;
		GetCpuVoltage(&voltage, hr);
		myForm->label20->Text = voltage.ToString();


#pragma endregion


#pragma region Operating System Information

		GetOperatingSystemInfo(hr);

		String^ strOsCaption = gcnew String(info.osCaption.c_str());
		String^ strOsMenuf = gcnew String(info.osManufacturer.c_str());
		String^ strOsBuildN = gcnew String(info.osBuildNumber.c_str());

		myForm->label8->Text = strOsCaption;
		myForm->label15->Text = strOsMenuf;
		myForm->label16->Text = strOsBuildN;




#pragma endregion



#pragma region Motherboard Information

		GetMotherboardInfo(hr);

		String^ strManf = gcnew String(info.manufacturer.c_str());
		String^ strName = gcnew String(info.name.c_str());
		String^ strSerial = gcnew String(info.serial.c_str());

		myForm->label12->Text = strManf;
		myForm->label13->Text = strName;
		myForm->label14->Text = strSerial;


#pragma endregion



#pragma region Hard Disk Information
		long hdSize;
		GetHardDriveInfo(hr, &hdSize);

		String^ hdCaption = gcnew String(info.HDcaption.c_str());
		String^ hdSerial = gcnew String(info.HDserialNumber.c_str());
		myForm->label25->Text = hdCaption;
		myForm->label26->Text = hdSerial->Trim();
		myForm->label27->Text = hdSize.ToString();




#pragma endregion



		// Create the main window and run it
		Application::Run(myForm);
	
	return 0;
}
