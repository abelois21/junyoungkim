#include <iostream>
#include <string>
#include <stdio.h>
#define GEAR_MAX 4

using namespace std;

typedef union GEAR_t {
	unsigned char all;
	struct {
		unsigned char _11 : 1;
		unsigned char _9  : 1;
		unsigned char _7  : 1;
		unsigned char _6  : 1;
		unsigned char _5  : 1;
		unsigned char _3  : 1;
		unsigned char _1  : 1;
		unsigned char _12 : 1;
	} dir;
} GEAR_t;

void cw(GEAR_t* gear, int n, int from);
void ccw(GEAR_t* gear, int n, int from);
void assign(GEAR_t* gear, const char* str);

int main(int argc, char** argv) {
	GEAR_t gears[GEAR_MAX+1];
	string str;
	int n, tmp, gear_num, rotate, result = 0;

	for (int i = 1; i <= GEAR_MAX; i++)
	{
		gears[i].all = 0;
		cin >> str;
		assign(gears + i, str.c_str());
	}
	cin >> n;

/*
	for (int i = 1; i <= 4; i++) {
		printf("12=> %d %d *%d* %d %d %d *%d* %d <=11 \n", gears[i].dir._12, gears[i].dir._1, gears[i].dir._3
			, gears[i].dir._5, gears[i].dir._6, gears[i].dir._7, gears[i].dir._9, gears[i].dir._11);
	}
*/

	for (int i = 0; i < n; i++)
	{
		cin >> gear_num >> rotate;
		if (rotate == 1) 
		{
			cw(gears, gear_num, gear_num);
		}
		else if (rotate == -1)
		{
			ccw(gears, gear_num, gear_num);
		}
		/*
		for (int i = 1; i <= 4; i++) {
			printf("12=> %d %d *%d* %d %d %d *%d* %d <=11 \n", gears[i].dir._12, gears[i].dir._1, gears[i].dir._3
				, gears[i].dir._5, gears[i].dir._6, gears[i].dir._7, gears[i].dir._9, gears[i].dir._11);
		}
		*/
	}

	for (int i = 1; i <= GEAR_MAX; i++)
	{
		result += ((gears + i)->dir._12 * (1 << (i-1)));
	}

	cout << result;

	return 0;
}

void assign(GEAR_t* gear, const char* str) {
	unsigned  char tmp = 0;

	for (int i = 0; i < 8; i++)
	{
		tmp = tmp << 1;
		tmp |= (unsigned char)(str[i]-'0');
	}
	gear->all = tmp;

	return;
}

// 시계방향
// from 연쇄적으로 호출을 방지
void cw(GEAR_t* gear, int n, int from) {
	if ((n > 1) && (from != n - 1))
	{
		if (((gear+n)->dir._9 ^ (gear+n-1)->dir._3) == 1)
		{
			ccw(gear, n - 1, n);
		}
	}

	if ((n < GEAR_MAX) && (from != n + 1)) {	// 다음 톱니에 영향
		if (((gear + n)->dir._3 ^ (gear + n + 1)->dir._9) == 1)
		{
			ccw(gear, n + 1, n);
		}
	}

	(gear + n)->all = ((gear + n)->all >> 1) | ((gear + n)->dir._11 << 7);
}

// 시계방향
void ccw(GEAR_t* gear, int n, int from) {
	if ((n > 1) && (from != n - 1))
	{
		if (((gear + n)->dir._9 ^ (gear + n - 1)->dir._3) == 1)
		{
			cw(gear, n - 1, n);
		}
	}

	if ((n < GEAR_MAX) && (from != n + 1)) {	// 다음 톱니에 영향
		if (((gear + n)->dir._3 ^ (gear + n + 1)->dir._9) == 1)
		{
			cw(gear, n + 1, n);
		}
	}

	(gear + n)->all = ((gear + n)->all << 1) | ((gear + n)->dir._12);
}
