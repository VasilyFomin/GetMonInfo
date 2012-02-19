#include "Monitor.h"

CMonitor::CMonitor(void)
{
	monitorWidth = monitorHeight = 0;
	isPrimary = false;
	monitorCoordinateX = monitorCoordinateY = 0;
	rotationAngle = 0;	
}

CMonitor::~CMonitor(void)
{
}

int CMonitor::getMonitorWidth( void ) const
{
	return monitorWidth;
}

int CMonitor::getMonitorHeight( void ) const
{
	return monitorHeight;
}

bool CMonitor::getIsPrimary( void ) const
{	
	return isPrimary;
}

int CMonitor::getMonitorCoordinateX( void ) const
{
	return monitorCoordinateX;
}

int CMonitor::getMonitorCoordinateY( void ) const
{
	return monitorCoordinateY;
}

int CMonitor::getRotationAngle( void ) const
{
	return rotationAngle;	
}

wstring CMonitor::getDeviceName( void ) const
{
	return deviceName;
}

wstring CMonitor::getMonitorName( void ) const
{
	return monitorName;
}

void CMonitor::setRotationAngle(int value)
{
	rotationAngle = value;
}

void CMonitor::setDeviceName(std::wstring value)
{
	deviceName = value;
}

void CMonitor::setMonitorName(std::wstring value)
{
	monitorName = value;
}

void CMonitor::setCoordinateX(int value)
{
	monitorCoordinateX = value;
}

void CMonitor::setCoordinateY(int value)
{
	monitorCoordinateY = value;
}

void CMonitor::setIsPrimary(bool value)
{
	isPrimary = value;
}

void CMonitor::setMonitorWidth(int value)
{
	monitorWidth = value; 
}

void CMonitor::setMonitorHeight(int value)
{
	monitorHeight = value;
}



