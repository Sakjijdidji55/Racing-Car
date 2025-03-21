#ifndef CAR_HPP
#define CAR_HPP
#include<easyx.h>
#define TypeofCars 6
#define Car_WEIGHT 40
#define Car_LENGTH 64


typedef struct {
	int x;
	int y;
	int id;
}Car;

void initCar(Car* car, int x, int y, int id);
void DrawCar(Car car);
void ChangeCar();
void LoadCars();
void PutAlphaImg(int x, int y, IMAGE* src);

#endif 
