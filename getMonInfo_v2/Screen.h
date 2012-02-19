#pragma once

// Класс представляет сущность виртуального экрана Windows.
// Представляет из себя совокупность всех установленных в системе мониторов
#ifndef SCREEN_H
#define SCREEN_H
#include "global.h"
#include "Monitor.h"

class CScreen
{	
// Public Functions
public:
	CScreen(void);
	~CScreen(void);	
	vector<CMonitor> getMonitorsList(void) const;	// Функция возвращает все доступные в системе мониторы 

private:
	//vector<CMonitor> monitorsList;	// Список всех мониторов, установленных в системе
	int virtualScreenWidth;				// Ширина виртуального экрана
	int virtualScreenHeight;			// Высота виртуального экрана
	static int deviceIndex;				// Индекс текущего монитора
	//CMonitor *monitor;				// Временный обьект для заполнения списка мониторов
	

// Public Getters
public:	
	int getVirtualScreenWidth(void) const;
	int getVirtualScreenHeight(void) const;

// Private Setters
private:
	void setVirtualScreenWidth(void);
	void setVirtualScreenHeight(void);	

// Private Functions
private:
	static BOOL CALLBACK GetDisplaysList(HMONITOR hMon, HDC dcMon, RECT * pRcMon, LPARAM lParam);		
};
#endif // SCREEN_H
