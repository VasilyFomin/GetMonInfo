#pragma once

// ������ ����� �������� �������� ��������
#ifndef CMONITOR_H
#define CMONITOR_H

#include "global.h"

class CMonitor
{
	friend class CScreen;		// ������ ������ ����� CScreen, ��� ������� � private �����
public:
	CMonitor(void);
	~CMonitor(void);

private:
	int monitorWidth;			// ������ ��������
	int monitorHeight;			// ������ ��������
	bool isPrimary;				// ���� ��������� ��������
	int monitorCoordinateX;		// X - ���������� ��������, � ����������� ������
	int monitorCoordinateY;		// Y - ���������� ��������, � ����������� ������
	int rotationAngle;			// ����, �� ������� �������� �������
	wstring deviceName;			// ��� ����������
	wstring monitorName;		// ��� ��������

public:
	// Public Getters
	int getMonitorWidth(void) const;
	int getMonitorHeight(void) const;
	bool getIsPrimary(void) const;
	int getMonitorCoordinateX(void) const;
	int getMonitorCoordinateY(void) const;
	int getRotationAngle(void) const;	
	wstring getDeviceName(void) const;
	wstring getMonitorName(void) const;

private:
	// Private Setters
	void setMonitorWidth(int value);
	void setMonitorHeight(int value);
	void setIsPrimary(bool value);
	void setCoordinateX(int value);
	void setCoordinateY(int value);
	void setRotationAngle(int value);
	void setDeviceName(wstring value);
	void setMonitorName(wstring value);
};
#endif // CMONITOR_H
