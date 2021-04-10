#include <stdio.h>
/*相加
* 把a，b相加赋值给a
*/
int Add(long double* a, long double b);
/*相减
* a，b相减赋值给a
*/
int Sub(long double* a, long double b);
/*相乘
* a，b相乘赋值给a
*/
int Mul(long double* a, long double b);
/*除法
* a 除以 b 赋值给a
*/
int Div(long double* a, long double b);
/*获取选项输入
*/
char getItem(void);
/*打印菜单
*/
int menu(void);
/*获取有理数输入
*/
int getNum(long double* num);


int main(void) {
	long double a, b;
	char ch;
	printf("请分别输入a，b数值：\n");
	getNum(&a);
	getNum(&b);
	menu();
	getchar();
	ch = getItem();
	switch (ch) {
	case ('a'):
	case ('A'):
		Add(&a, b);
		printf("a+b = %lf\n", a);
		break;
	case ('b'):
	case ('B'):
		Sub(&a, b);
		printf("a-b = %lf\n", a);
		break;
	case ('c'):
	case ('C'):
		Mul(&a, b);
		printf("a*b = %lf\n", a);
		break;
	case ('d'):
	case ('D'):
		if (!Div(&a, b)) {
			printf("被除数不能为0\n");
			break;
		}
		printf("a/b = %lf\n", a);
		break;
	default:
		printf("不存在该选项\n");
		break;
	}






	return 0;
}
int Add(long double* a, long double b) {
	*a += b;
	return 1;
}
int Sub(long double* a, long double b) {
	*a -= b;
	return 1;
}
int Mul(long double* a, long double b) {
	*a *= b;
	return 1;
}
int Div(long double* a, long double b) {
	if (b == 0) {
		return 0;
	}
	*a /= b;
	return 1;
}
char getItem(void) {
	char ch;
	while (!(((ch = getchar()) >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
		printf("请输入字母以选择相应选项：\n");
		while (getchar() != '\n')continue;
	}
	return ch;
}
int menu(void) {
	printf("A.Add\tB.Sub\tC.Mul\nD.Div\tQ.uit\n");
	return 1;
}
int getNum(long double* num) {
	while (scanf(" %lf", num) != 1) {
		printf("请输入有理数：\n");
		while (getchar() != '\n')continue;
	}
	return 1;
}







