#include"Car.hpp"

IMAGE cars_img[TypeofCars];

void PutAlphaImg(int x, int y, IMAGE* src) {
	DWORD* pwin = GetImageBuffer();
	DWORD* psrc = GetImageBuffer(src);
	int win_w = getwidth();
	int win_h = getheight();
	int src_w = src->getwidth();
	int src_h = src->getheight();

	int real_w = (x + src_w > win_w) ? win_w - x : src_w;
	int real_h = (x + src_h > win_h) ? win_h - x : src_h;
	if (x < 0) {
		psrc += -x;
		real_w -= -x;
		x = 0;
	}
	if (y < 0) {
		psrc += (src_w * -y);
		real_h -= -y;
		y = 0;
	}

	pwin += (win_w * y + x);

	for (int iy = 0; iy < real_h; iy++) {
		for (int ix = 0; ix < real_w; ix++) {
			byte t = (byte)(psrc[ix] >> 24);
			if (t > 100) {
				pwin[ix] = psrc[ix];
			}
		}
		pwin += win_w;
		psrc += src_w;
	}
}

void initCar(Car* car, int x, int y, int id) {
	car->x = x;
	car->y = y;
	car->id = id;
}

void LoadCars() {
	for (int i = 0; i < TypeofCars; i++) {
		WCHAR path[20] = { 0 };
		wsprintf(path, _T("./image/car%d.png"), i);
		loadimage(&cars_img[i], path, Car_WEIGHT, Car_LENGTH);
	}
}

void DrawCar(Car car) {
	PutAlphaImg(car.x, car.y, cars_img + car.id);
}

void ChangeCar() {

}