#include "global.h"
#include "Screen.h"


CScreen::CScreen(void)
{
	setVirtualScreenWidth();
	setVirtualScreenHeight();	
}

CScreen::~CScreen(void)
{
	
}

int CScreen::getVirtualScreenWidth( void ) const
{
	return virtualScreenWidth;	
}

int CScreen::getVirtualScreenHeight( void ) const
{
	return virtualScreenHeight;
}

void CScreen::setVirtualScreenWidth( void )
{
	virtualScreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
}

void CScreen::setVirtualScreenHeight( void )
{
	virtualScreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

vector<CMonitor> CScreen::getMonitorsList( void ) const
{
	// �������� ������ ���� ������������� � ������� ���������
	vector<CMonitor> monitorsList;
	LPARAM lParam = reinterpret_cast<LPARAM>(&monitorsList);
	EnumDisplayMonitors(0, 0, CScreen::GetDisplaysList, lParam);
	return monitorsList;
}
int CScreen::deviceIndex = 0;
BOOL CALLBACK CScreen::GetDisplaysList( HMONITOR hMon, HDC dcMon, RECT * pRcMon, LPARAM lParam )
{
	vector<CMonitor> * pMonitorsList = reinterpret_cast<vector<CMonitor> *>(lParam);
	
	CMonitor * currentMonitor = new CMonitor();				// ������, ���� �������� �������� � ���� ���� ������� � ������� � ������
	
	MONITORINFO currentMonitorInfo;							// ���������, ���������� ���������� � ������� �������������� ��������
	currentMonitorInfo.cbSize = sizeof(currentMonitorInfo); // ���������� ������ ����� ������� ���������
	GetMonitorInfo(hMon, &currentMonitorInfo);				// �������� ���������� �� �������������� ��������
	
	// ����������� ���� ������� currentMonitor ����������� �������
	currentMonitor->setMonitorWidth(pRcMon->right - pRcMon->left);		// ������
	currentMonitor->setMonitorHeight(pRcMon->bottom - pRcMon->top);		// ������
	currentMonitor->setCoordinateX( currentMonitorInfo.rcMonitor.left);	// � ����������
	currentMonitor->setCoordinateY(currentMonitorInfo.rcMonitor.top);	// Y ����������

	// ��������� ����� ��������� ��������
	if (currentMonitorInfo.dwFlags == MONITORINFOF_PRIMARY)
	{
		currentMonitor->setIsPrimary(true);
	} 
	else
	{
		currentMonitor->setIsPrimary(false);
	}

	DISPLAY_DEVICE dispayDevice;								// ������� �������������� �������
	dispayDevice.cb = sizeof(dispayDevice);					// ���������� ������ ����� ������� ���������	

	HRESULT hr;													// ��� ��������� ����������� ����������� �����
	wchar_t tempDeviceName[33];									// ��� ���������� �������� ����� ����������
	wchar_t tempMonitorName[128];								// ��� ���������� �������� ����� ��������
	if (EnumDisplayDevices(NULL, deviceIndex, &dispayDevice, 0))// ����� ������� ������ �������� ��� ����������
	{
		hr = StringCchCopy(tempDeviceName, 33, dispayDevice.DeviceName);
		currentMonitor->setDeviceName(tempDeviceName);			// ��� ����������
		if (FAILED(hr))
		{
			cerr << "Error in copy deviceName string" << endl;
		}

		EnumDisplayDevices(tempDeviceName, 0, &dispayDevice, 0); // ����� ������� ������ �������� ��� ��������
		hr = StringCchCopy(tempMonitorName, 129, dispayDevice.DeviceString);
		currentMonitor->setMonitorName(tempMonitorName);		// ��� ��������
		if (FAILED(hr))
		{
			cerr << "Error in copy monitorName string" << endl;
		}

		DEVMODE devMode;																// ����� ������ �������� ����������
		devMode.dmSize = sizeof(DEVMODE);												// ���������� ������ ����� ������� ���������
		devMode.dmFields = DM_DISPLAYORIENTATION;										// ���� ��������� �� ��, ��� ��� �������� ������������ ���������� �������� ��������
		EnumDisplaySettingsEx(tempDeviceName, ENUM_CURRENT_SETTINGS, &devMode, NULL);	// �������� ��� ��������� ���� �������� ��������		
		switch (devMode.dmDisplayOrientation)
		{
		case DMDO_DEFAULT:
			currentMonitor->setRotationAngle(0);			
			break;
		case DMDO_90:
			currentMonitor->setRotationAngle(90);
			break;
		case DMDO_180:
			currentMonitor->setRotationAngle(180);
			break;
		case DMDO_270:
			currentMonitor->setRotationAngle(270);
			break;
		}
	} 
	else
	{
		cerr << "Could not get display settings!" << endl;
	}

	pMonitorsList->push_back(*currentMonitor);
	
	delete currentMonitor;

	deviceIndex++;
	return true;
}


