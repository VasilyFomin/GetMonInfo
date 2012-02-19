#pragma once

// Данный класс отражает сущность монитора
#ifndef CMONITOR_H
#define CMONITOR_H

#include "global.h"

class CMonitor
{
	friend class CScreen;		// Делаем другом класс CScreen, для доступа к private полям
public:
	CMonitor(void);
	~CMonitor(void);

private:
	int monitorWidth;			// Ширина монитора
	int monitorHeight;			// Высота монитора
	bool isPrimary;				// Флаг основного монитора
	int monitorCoordinateX;		// X - координата монитора, в виртуальном экране
	int monitorCoordinateY;		// Y - координата монитора, в виртуальном экране
	int rotationAngle;			// Угол, на который повернут монитор
	wstring deviceName;			// Имя устройства
	wstring monitorName;		// Имя монитора

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
