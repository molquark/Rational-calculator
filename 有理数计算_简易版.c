#include <stdio.h>
/*���
* ��a��b��Ӹ�ֵ��a
*/
int Add(long double* a, long double b);
/*���
* a��b�����ֵ��a
*/
int Sub(long double* a, long double b);
/*���
* a��b��˸�ֵ��a
*/
int Mul(long double* a, long double b);
/*����
* a ���� b ��ֵ��a
*/
int Div(long double* a, long double b);
/*��ȡѡ������
*/
char getItem(void);
/*��ӡ�˵�
*/
int menu(void);
/*��ȡ����������
*/
int getNum(long double* num);


int main(void) {
	long double a, b;
	char ch;
	printf("��ֱ�����a��b��ֵ��\n");
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
			printf("����������Ϊ0\n");
			break;
		}
		printf("a/b = %lf\n", a);
		break;
	default:
		printf("�����ڸ�ѡ��\n");
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
		printf("��������ĸ��ѡ����Ӧѡ�\n");
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
		printf("��������������\n");
		while (getchar() != '\n')continue;
	}
	return 1;
}







