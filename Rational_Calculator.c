#include <stdio.h>
#include "Rational_ADT.h"





int main(void) {
	Rational Q1, Q2;
	Rational C;
	int Base;
	char way;
	loop:
	printf("请输入计算进制:\n");
	scanf(" %d", &Base);
	if (Base < 2 || Base>36) {
		printf("进制为2~36");
		return 0;
	}
	getchar();
	init_Rational(&C, Base);
	printf("请输入第一个有理数\n");
	Input_Rational(&Q1, Base);
	printf("请输入第二个有理数\n");
	Input_Rational(&Q2, Base);
	printf("请输入计算方法：\nA.dd\tB.Sub\tC.Mul\tD.iv\n");
	scanf(" %c", &way);
	getchar();
	switch (way) {
	case('a'):
	case('A'):
		Add_Rational(Q1, Q2, C);
		printf("Q1+Q2=\n");
		break;
	case('b'):
	case('B'):
		Sub_Rational(Q1, Q2, C);
		printf("Q1-Q2=\n");
		break;
	case('c'):
	case('C'):
		Mul_Rational(Q1, Q2, C);
		printf("Q1*Q2=\n");
		break;
	case('d'):
	case('D'):
		Div_Rational(Q1, Q2, C);
		printf("Q1/Q2=\n");
		break;
	default:
		printf("没有该选项\n");
		return 0;
	}
	Output_Rational(C);
	Free_Rational(&Q1);
	Free_Rational(&Q2);
	Free_Rational(&C);
	printf("输入q退出(回车继续）：\n");
	if (getchar() == 'q')goto e;
	goto loop;
	e:
	return 0;
}