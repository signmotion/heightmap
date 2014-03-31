#pragma once

// ����� ����������� ����� ������� � ����������� ��������� ������������ ��������,
// ��� �������
#pragma warning( disable : 4503 )

// ���������� ��������� �������, ������� ���� �������� ��� ���������� � deprecated
// @see http://lists.boost.org/Archives/boost/2006/08/109338.php 
//#pragma warning( disable : 4996 )


// (!) ��������� �������������� ������� �������� ������ ���� ���. �����
//     ����������.

// ����������� ������� �������������� "pcl::search::Search<PointT>::radiusSearch",
// ���������� ������ ����������� �� ��������� ���������������, ����� ���������
// ���������� ������ ��������������� const ��� volatile
//#pragma warning( disable : 4373 )

// �������������� double � int, �������� ������ ������
//#pragma warning( disable : 4244 )


// �������� ����������, �������� ����� ���� �� ��������� Windows
#define WIN32_LEAN_AND_MEAN


// �������� ������� ������ � WinDef.h
#define NOMINMAX

// ���������� �������������� ���������
#define _USE_MATH_DEFINES


#include <assert.h>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <list>
#include <map>
#include <math.h>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <windows.h>

#include <QApplication>
#include <QtGui>
#include <QtOpenGL>
#include <qpixmap.h>

#include "Exception.h"
