#include <stdio.h>
#include "Rational_ADT.h"





int main(void) {
	Rational Q1, Q2;
	Rational C;
	int Base;
	char way;
	loop:
	printf("������������:\n");
	scanf(" %d", &Base);
	if (Base < 2 || Base>36) {
		printf("����Ϊ2~36");
		return 0;
	}
	getchar();
	init_Rational(&C, Base);
	printf("�������һ��������\n");
	Input_Rational(&Q1, Base);
	printf("������ڶ���������\n");
	Input_Rational(&Q2, Base);
	printf("��������㷽����\nA.dd\tB.Sub\tC.Mul\tD.iv\n");
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
		printf("û�и�ѡ��\n");
		return 0;
	}
	Output_Rational(C);
	Free_Rational(&Q1);
	Free_Rational(&Q2);
	Free_Rational(&C);
	printf("����q�˳�(�س���������\n");
	if (getchar() == 'q')goto e;
	goto loop;
	e:
	return 0;
}