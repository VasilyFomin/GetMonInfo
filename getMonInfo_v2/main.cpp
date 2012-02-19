#include "global.h"
#include "Screen.h"
#include "Monitor.h"
#include <locale>

wstring convertIntToWstring(int number)
{		
	wstringstream wStream;
	wStream << number;
	wstring tempStr = wStream.str();	

	return tempStr;
}
wstring convertBoolToString(bool value)
{
	string str = "";	
	if(value)
	{
		str = "true";
		wstring ws(str.begin(), str.end());
		return ws;
	}
	else
	{
		str = "false";
		wstring ws(str.begin(), str.end());
		return ws;
	}
}

int main(int argc, char ** argv)
{
	wcout.imbue(locale("rus_rus.866"));		// Локаль для вывода в консоль

	//Получаемый log файл
	wfstream logFile("monitors.xml", ios::in | ios::out | ios::trunc); 
	logFile.imbue(locale("rus_rus.1251")); // Локаль для вывода в файл

	CScreen * currentScreen = new CScreen();
	vector<CMonitor> currentMonitors;
	currentMonitors = currentScreen->getMonitorsList();

	wcout
		<< "<virtualScreen width=\"" << convertIntToWstring(currentScreen->getVirtualScreenWidth()) << "\" "
		<< "height=\"" << convertIntToWstring(currentScreen->getVirtualScreenHeight()) << "\">\n\t";
	logFile 
		<< "<virtualScreen width=\"" << convertIntToWstring(currentScreen->getVirtualScreenWidth()) << "\" "
		<< "height=\"" << convertIntToWstring(currentScreen->getVirtualScreenHeight()) << "\">\n\t";
	for(unsigned int i = 0; i < currentMonitors.size(); i++)
	{
		// Вывод собранной информации
		wcout 				
			<< "<desktop id=\"" << convertIntToWstring(i) << "\" " 
			<< "name=\"" << currentMonitors[i].getDeviceName() 
			<< " Monitor name: " << currentMonitors[i].getMonitorName() << "\"" 
			<< " x=\"" << convertIntToWstring(currentMonitors[i].getMonitorCoordinateX()) << "\"" 
			<< " y=\"" << convertIntToWstring(currentMonitors[i].getMonitorCoordinateY()) << "\""
			<< " width=\"" << convertIntToWstring(currentMonitors[i].getMonitorWidth()) << "\"" 
			<< " height=\"" << convertIntToWstring(currentMonitors[i].getMonitorHeight()) << "\""
			<< " angleOfRotation=\"" << convertIntToWstring(currentMonitors[i].getRotationAngle()) << "\"" 
			<< " primary=\"" << convertBoolToString(currentMonitors[i].getIsPrimary())<< "\"/>\n";		
		logFile 			
			<< "<desktop id=\"" << convertIntToWstring(i) << "\" " 
			<< "name=\"" << currentMonitors[i].getDeviceName() 
			<< " Monitor name: " << currentMonitors[i].getMonitorName() << "\"" 
			<< " x=\"" << convertIntToWstring(currentMonitors[i].getMonitorCoordinateX()) << "\"" 
			<< " y=\"" << convertIntToWstring(currentMonitors[i].getMonitorCoordinateY()) << "\""
			<< " width=\"" << convertIntToWstring(currentMonitors[i].getMonitorWidth()) << "\"" 
			<< " height=\"" << convertIntToWstring(currentMonitors[i].getMonitorHeight()) << "\""
			<< " angleOfRotation=\"" << convertIntToWstring(currentMonitors[i].getRotationAngle()) << "\"" 
			<< " primary=\"" << convertBoolToString(currentMonitors[i].getIsPrimary())<< "\"/>\n"; 			
	}
	wcout << "</virtualScreen>" << endl;	
	logFile << "</virtualScreen>" << endl;	

	logFile.close();
	delete currentScreen;
	currentMonitors.clear();

	return 0;
}
