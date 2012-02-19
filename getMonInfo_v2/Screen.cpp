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
	// Получаем список всех установленных в системе мониторов
	vector<CMonitor> monitorsList;
	LPARAM lParam = reinterpret_cast<LPARAM>(&monitorsList);
	EnumDisplayMonitors(0, 0, CScreen::GetDisplaysList, lParam);
	return monitorsList;
}
int CScreen::deviceIndex = 0;
BOOL CALLBACK CScreen::GetDisplaysList( HMONITOR hMon, HDC dcMon, RECT * pRcMon, LPARAM lParam )
{
	vector<CMonitor> * pMonitorsList = reinterpret_cast<vector<CMonitor> *>(lParam);
	
	CMonitor * currentMonitor = new CMonitor();				// Обьект, поля которого заполним в теле этой функции и добавим в список
	
	MONITORINFO currentMonitorInfo;							// Структура, содержащая информацию о текущем обрабатываемом мониторе
	currentMonitorInfo.cbSize = sizeof(currentMonitorInfo); // Занимаемый размер равен размеру структуры
	GetMonitorInfo(hMon, &currentMonitorInfo);				// Получаем информацию об обрабатываемом мониторе
	
	// Заполненяем поля обьекта currentMonitor полученными данными
	currentMonitor->setMonitorWidth(pRcMon->right - pRcMon->left);		// Ширина
	currentMonitor->setMonitorHeight(pRcMon->bottom - pRcMon->top);		// Высота
	currentMonitor->setCoordinateX( currentMonitorInfo.rcMonitor.left);	// Х координата
	currentMonitor->setCoordinateY(currentMonitorInfo.rcMonitor.top);	// Y координата

	// Установка флага основного монитора
	if (currentMonitorInfo.dwFlags == MONITORINFOF_PRIMARY)
	{
		currentMonitor->setIsPrimary(true);
	} 
	else
	{
		currentMonitor->setIsPrimary(false);
	}

	DISPLAY_DEVICE dispayDevice;								// Текущий обрабатываемый монитор
	dispayDevice.cb = sizeof(dispayDevice);					// Занимаемый размер равен размеру структуры	

	HRESULT hr;													// Для обработки результатов копирования строк
	wchar_t tempDeviceName[33];									// Для временного хранения имени устройства
	wchar_t tempMonitorName[128];								// Для временного хранения имени монитора
	if (EnumDisplayDevices(NULL, deviceIndex, &dispayDevice, 0))// После первого вызова получаем имя устройства
	{
		hr = StringCchCopy(tempDeviceName, 33, dispayDevice.DeviceName);
		currentMonitor->setDeviceName(tempDeviceName);			// Имя устройства
		if (FAILED(hr))
		{
			cerr << "Error in copy deviceName string" << endl;
		}

		EnumDisplayDevices(tempDeviceName, 0, &dispayDevice, 0); // После второго вызова получаем имя монитора
		hr = StringCchCopy(tempMonitorName, 129, dispayDevice.DeviceString);
		currentMonitor->setMonitorName(tempMonitorName);		// Имя монитора
		if (FAILED(hr))
		{
			cerr << "Error in copy monitorName string" << endl;
		}

		DEVMODE devMode;																// Режим работы текущего устройства
		devMode.dmSize = sizeof(DEVMODE);												// Занимаемый размер равен размеру структуры
		devMode.dmFields = DM_DISPLAYORIENTATION;										// Поле указывает на то, что при передачи определяется ориентация текущего монитора
		EnumDisplaySettingsEx(tempDeviceName, ENUM_CURRENT_SETTINGS, &devMode, NULL);	// Вызываем для получения угла поворота монитора		
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


