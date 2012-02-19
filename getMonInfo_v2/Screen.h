#pragma once

// ����� ������������ �������� ������������ ������ Windows.
// ������������ �� ���� ������������ ���� ������������� � ������� ���������
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
	vector<CMonitor> getMonitorsList(void) const;	// ������� ���������� ��� ��������� � ������� �������� 

private:
	//vector<CMonitor> monitorsList;	// ������ ���� ���������, ������������� � �������
	int virtualScreenWidth;				// ������ ������������ ������
	int virtualScreenHeight;			// ������ ������������ ������
	static int deviceIndex;				// ������ �������� ��������
	//CMonitor *monitor;				// ��������� ������ ��� ���������� ������ ���������
	

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
