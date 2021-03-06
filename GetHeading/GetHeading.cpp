// GetHeading.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

//#include <stdio.h>
//#include <stdlib.h>
//#include <atlfile.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "GetHeading.h"
#include "DataStructure.h"

using namespace std;

void getHeadingFromImu();
void getHeadingFromGps();

int main()
{
	getHeadingFromGps();
	//getHeadingFromImu();

    return 0;
}

/*void getHeadingFromImu()
{
	FILE *pFile = NULL;
	fopen_s(&pFile, "imu_log1.txt", "r");
	char *pStr;
	int j = 0;
	char* point;
	double MagData[13];
	double PI = 3.14159265359;

	if (pFile != NULL)
	{
		char strTemp[255];

		while (!feof(pFile))
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);
			point = strtok(pStr, " ");
			while (point != NULL)
			{
				if (j >= 11)
					MagData[j] = atof(point);
				j++;
				point = strtok(NULL, " ");
			}

			//float y = MagData[11];
			//float z = MagData[12];
			double heading = atan2(MagData[11], MagData[12]);
			float declination = 0.073;
			heading += declination;

			if (heading < 0)heading += 2 * PI;
			if (heading > 2 * PI)heading -= 2 * PI;

			double headingDgrees = heading * 180 / PI;


			double headingFiltered = headingFiltered*0.85 + headingDgrees*0.15;

			printf("heading : %f\n", headingFiltered);
			j = 0;


		}
		fclose(pFile);
	}
	else
	{
		"못염";
	}

	
	/////////////////////////////////////////
	float y = 1.26;
	float z = 20.15;
	heading = atan2(y, z);
	float declination = 0.073;
	heading += declination;

	if (heading < 0)heading += 2 * PI;
	if (heading > 2 * PI)heading -= 2 * PI;

	headingDgrees = heading * 180 / PI;


	headingFiltered = headingFiltered*0.85 + headingDgrees*0.15;
	
	printf("heading %f", headingFiltered);

	
}*/

void getHeadingFromGps()
{
	double lats[10000]; // 해쉬 배열
	double lons[10000];
	for (int i = 0; i < 10000; i++)
	{
		lats[i] = 0;
		lons[i] = 0;
	}

	ifstream inputStream("gps_test_track3.txt");
	GpxFileManager g1;
	g1.openFileStream("hello");
	GpsData gpsData, prevGpsData;
	//prevGpsData.latitude = 35.8869095;
	//prevGpsData.longitude = 128.611282;
	GpsData temp1, temp2;
	temp1.latitude = 35.000000;
	temp1.longitude = 35.000000;
	temp2.latitude = 35.000001;
	temp2.longitude = 35.000000;

	cout << "Distance of 0.000001 : " << getDistance(temp1, temp2) << " centimeter" << endl;

	int i = 1;
	
	inputStream >> gpsData.datetime.hours >> gpsData.datetime.minutes >> gpsData.datetime.seconds >> gpsData.datetime.milliseconds
		>> gpsData.latitude >> gpsData.longitude >> gpsData.fixtype >> gpsData.satelliteInUse >> gpsData.hdop >> gpsData.altitude;
	while (true)
	{
		// 가장 많이 나온 좌표를 구한다.
		double dTempLat = gpsData.latitude;
		double dTempLon = gpsData.longitude;
		int iTempLat = (int)((dTempLat - (int)dTempLat) * 1000000) % 10000;
		int iTempLon = (int)((dTempLon - (int)dTempLon) * 1000000) % 10000;
		lats[iTempLat]++;
		lons[iTempLon]++;
		// 가장 많이 나온 좌표를 구한다. 끗
		
		prevGpsData = gpsData;
		inputStream >> gpsData.datetime.hours >> gpsData.datetime.minutes >> gpsData.datetime.seconds >> gpsData.datetime.milliseconds
			>> gpsData.latitude >> gpsData.longitude >> gpsData.fixtype >> gpsData.satelliteInUse >> gpsData.fixtype >> gpsData.altitude;
		int hours = gpsData.datetime.hours;
		int minutes = gpsData.datetime.minutes;
		int seconds = gpsData.datetime.seconds;
		int milliseconds = gpsData.datetime.milliseconds;
		GpsData::time temp;
		double tempBearing = getBearing(prevGpsData, gpsData);
		double tempDistance = getDistance(prevGpsData, gpsData);

		cout.precision(9);
		if (tempDistance != 0)
		cout << i++ << " : " << gpsData.datetime.minutes << " " << gpsData.datetime.seconds << " "<< gpsData.datetime.milliseconds << " " << tempBearing << " " << tempDistance << endl;

		if (inputStream.eof())
			break;
	}
	// 가장 많이 나온 좌표 출력
	for (int i = 0; i < 10000; i++)
	{
		//if (lats[i] != 0)
			//cout << "Latitude " << i << " : " << lats[i] << endl;
	}
	for (int i = 0; i < 10000; i++)
	{
		//if (lons[i] != 0)
			//cout << "Longitude " << i << " : " << lons[i] << endl;
	}
	// 가장 많이 나온 좌표 출력 끗
}