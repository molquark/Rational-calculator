/*ʹ��˫������洢������,�������ΪRational����������
* ����ͷ�ṹ����ڽڵ㣬ͨ��ͷ�ṹ�洢�����������Ϣ
* author:LDY
* begin:21/03/06 10:58
* finish:21/03/07 20:47
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Rational_ADT.h"




int Create_Rational_Node(Rational_Node* Node, int num) {
	if (!((*Node) = (Rational_Node)malloc(sizeof(struct Rational_Node_ADT)))) {
		fprintf(stderr, "�޷�����ռ���ΪRational_Node_ADT�ڵ�");
		exit(EXIT_FAILURE);
	}
	(*Node)->num = num;
	(*Node)->left = (*Node)->right = NULL;
	return 1;
}
int init_Rational(Rational* Q,int B) {
	if (!((*Q) = (Rational)malloc(sizeof(struct Rational_Head_ADT)))) {
		fprintf(stderr, "�޷�����ռ���ΪRational_Head_ADT�ڵ�");
		exit(EXIT_FAILURE);
	}
	(*Q)->base = B;//���ý���
	(*Q)->sign = +1;//���÷���Ϊ��
	(*Q)->left_num = (*Q)->right_num = 0;//���ҽڵ�Ϊ0
	Create_Rational_Node(&((*Q)->point), POINT);//��ڽڵ㣬numΪPOINT
	(*Q)->left_end = (*Q)->right_end = NULL;//����ĩ��ָ��ΪNULL
	(*Q)->point->left = (*Q)->point->right = NULL;
	return 1;
}
int ReInit_Rational(Rational Q, int B) {
	if (!Q->left_num && !Q->right_num) {
		return 1;
	}
	Rational_Node Now;
	if (Q->left_num) {
		Now = Q->left_end;
		while (Now->num != POINT) {
			Now = Now->right;
			free(Now->left);
			Q->left_end = NULL;
			Q->left_num = 0;//������ڵ㲢����ͷ�ڵ�����
		}
	}
	if (Q->right_num) {
		Now = Q->right_end;
		while (Now->num != POINT) {
			Now = Now->left;
			free(Now->right);
			Q->right_end = NULL;
			Q->right_num = 0;//������ڵ㲢����ͷ�ڵ�����
		}
	}
	return 1;
}
int Copy_Rational(Rational Q1, Rational Q2) {
	ReInit_Rational(Q2, Q1->base);//����Q2
	if (!Q1->left_num && !Q1->right_num) {
		return 1;
	}
	Rational_Node Now;
	if (Q1->left_num) {
		Now = Q1->left_end;
		while (Now->num != POINT) {
			Add_Left_LtoR(Q2, Now->num);
			Now = Now->right;
		}
	}
	if (Q1->right_num) {
		Now = Q1->point->right;
		while (Now) {
			Add_Right_LtoR(Q2, Now->num);
			Now = Now->right;
		}
	}
	return 1;
}
int Free_Rational(Rational* Q) {
	if ((*Q)->left_num == 0 && (*Q)->right_num == 0) {
		free((*Q)->point);
		free(*Q);
		*Q = NULL;
		return 1;
	}
	Rational_Node Now;
	if ((*Q)->left_num != 0) {
		//����нڵ�
		Now = (*Q)->left_end;
		while (Now->right) {
			Now = Now->right;
			free(Now->left);
		}
		free(Now);
		free(*Q);
		*Q = NULL;
		return 1;
	}
	if ((*Q)->right_num != 0) {
		//�Ҳ��нڵ�
		Now = (*Q)->right_end;
		while (Now->left) {
			Now = Now->left;
			free(Now->right);
		}
		free(Now);
		free(*Q);
		*Q = NULL;
		return 1;
	}
	free(*Q);
	*Q = NULL;
	return 1;
}
int Add_Left_LtoR(Rational Q, char num) {
	Rational_Node R_Node, L_Node, New;
	if (Q->left_num == 0) {
		Create_Rational_Node(&L_Node, num);
		Q->point->left = L_Node;//leftָ���½ڵ�
		L_Node->left = NULL;
		L_Node->right = Q->point;//�½ڵ��ұ�ָ����ڽڵ�
		Q->left_end = L_Node;
		Q->left_num += 1;
		return 1;
	}
	if (Q->left_num == 1) {
		L_Node = Q->left_end;
		R_Node = Q->point;
		//�����½ڵ㲢���뵽L_Node��R_Node֮��
		Create_Rational_Node(&New, num);
		L_Node->right = New;
		New->left = L_Node;
		R_Node->left = New;
		New->right = R_Node;
		Q->left_num += 1;
		return 1;
	}
	//������ΪQ->left_num����1�����
	R_Node = Q->point;
	L_Node = R_Node->left;
	Create_Rational_Node(&New, num);
	L_Node->right = New;
	New->left = L_Node;
	R_Node->left = New;
	New->right = R_Node;
	Q->left_num += 1;
	return 1;
}
int Add_Left_RtoL(Rational Q, char num) {
	/*�����ҵ�����룬ֱ�������ĩ�˽ڵ��������*/
	Rational_Node New;
	if (!Q->left_num) {
		//������Ϊ0
		Create_Rational_Node(&New, num);
		Q->left_end = New;
		Q->point->left = New;
		New->right = Q->point;
		Q->left_num += 1;//������һ
		return 1;
	}
	//�����಻Ϊ0
	Create_Rational_Node(&New, num);
	New->right = Q->left_end;
	Q->left_end->left = New;//New�������ĩ��
	Q->left_end = New;//left_endָ��New
	Q->left_num += 1;//������һ
	return 1;
}
int Add_Right_LtoR(Rational Q, char num) {
	Rational_Node New;
	if (!Q->right_num) {
		Create_Rational_Node(&New, num);
		Q->point->right = New;
		New->left = Q->point;
		Q->right_end = New;
		Q->right_num += 1;//������һ
		return 1;
	}
	//����Ҳ಻Ϊ0
	Create_Rational_Node(&New, num);
	Q->right_end->right = New;
	New->left = Q->right_end;
	Q->right_end = New;
	Q->right_num += 1;
	return 1;
}
int Clear_after_Sub(Rational Q) {
	Rational_Node Now;
	Now = Q->left_end;
	if (!Now) {
		//���NowΪNULL��ֱ���˳�
		return 1;
	}
	while (Now->num == 0) {
		Now = Now->right;
		Q->left_end = Now;//�ƶ����end
		Q->left_num -= 1;//�������ڵ���ֵ
		free(Now->left);//Now�ƶ����Ҳ�ڵ㣬���ͷ����ڵ�
		Now->left = NULL;
	}
	return 1;
}
int Move_Head_Left(Rational Q, int num) {
	if (!num)return 1;
	Rational_Node L_Node,R_Node;
	int i,all;
	//����ڽڵ�����˫������
	if (Q->left_num && Q->right_num) {
		//������ҽڵ㶼��Ϊ0
		Q->point->left->right = Q->point->right;//��ڵ����ڵ����ָ��ָ������Ҳ�ڵ�
		Q->point->right->left = Q->point->left;//��ڵ��Ҳ�ڵ����ָ��ָ��������ڵ�
	}
	else if (Q->left_num && !Q->right_num) {
		//����ұ�Ϊ0����߲�Ϊ0
		Q->point->left->right = NULL;//����ߵ�һ���ڵ����ָ����ΪNULL
		Q->right_end = Q->point->left;//��ڽڵ�Ҫ���ƣ�����ĩ��ָ��Ҫ����
	}
	else if (!Q->left_num && Q->right_num) {
		//������Ϊ0���ұ߲�Ϊ0
		Q->point->right->left = NULL;//���ұߵ�һ���ڵ���ָ����ΪNULL
	}
		//������߶���0�ڵ�
		//�޲���
	/*��������
	* 1.������С�����ڵ���
	* 2.�������������ڵ���
	* 3.�������������ڵ���*/
	//���1��������С�����ڵ���
	if (num < Q->left_num) {
		if (num > (Q->left_num / 2)) {//����������������ڵ��һ��
			all = Q->left_num - num - 1;
			L_Node = Q->left_end;//�����ĩ�˽ڵ㿪ʼ�ƶ�
			for (i = 0; i < all; i++) {
				L_Node = L_Node->right;
			}
			R_Node = L_Node->right;
			//��λ�ò�������ҽڵ�
		}
		else {//���������С�����ڵ��һ��
			all = num - 1;
			R_Node = Q->point->left;//����ڽڵ������һ���ڵ㿪ʼ
			for (i = 0; i < all; i++) {
				R_Node = R_Node->left;
			}
			L_Node = R_Node->left;
			//��λ�ò�������ҽڵ�
		}
		Q->left_num -= num;
		Q->right_num += num;
		//�ƶ�ͷ�ڵ㣬���ҽڵ���Ŀ�仯
		//����ĩ��ָ�벻��
		L_Node->right = Q->point;
		Q->point->left = L_Node;
		R_Node->left = Q->point;
		Q->point->right = R_Node;
		//������ڽڵ�
		//����
		return 1;
	}
	//���2���������������ڵ���
	if (num == Q->left_num) {
		//���ҽڵ����仯
		Q->left_num = 0;
		Q->right_num += num;
		//������ڽڵ�
		Q->point->left = NULL;//������ָ��ΪNULL
		Q->point->right = Q->left_end;//����Ҳ�ָ��ԭ���ĩ�˽ڵ�
		Q->left_end->left = Q->point;//ԭ���ĩ�˽ڵ����ָ����ڽڵ�
		Q->left_end = NULL;//ͷ�ڵ����ĩ��ָ����ΪNULL
		//����
		return 1;
	}
	//���3���������������ڵ���
	if (num > Q->left_num) {
		/*������ĩ������㹻��ֵΪ0�Ľڵ㣬�ٵݹ飬�൱�����2*/
		all = num - Q->left_num;
		for (i = 0; i < all; i++) {
			Add_Left_RtoL(Q, 0);
		}
		Move_Head_Left(Q, num);
		return 1;
	}
	return 1;
}
int Move_Head_Right(Rational Q, int num) {
	if (!num)return 1;
	Rational_Node  L_Node, R_Node;
	int i, all;
	if (!num) {
		return 1;
	}
	//����ڽڵ�����˫������
	if (Q->left_num && Q->right_num) {
		//������ҽڵ㶼��Ϊ0
		Q->point->left->right = Q->point->right;//��ڵ����ڵ����ָ��ָ������Ҳ�ڵ�
		Q->point->right->left = Q->point->left;//��ڵ��Ҳ�ڵ����ָ��ָ��������ڵ�
	}
	else if (Q->left_num && !Q->right_num) {
		//����ұ�Ϊ0����߲�Ϊ0
		Q->point->left->right = NULL;//����ߵ�һ���ڵ����ָ����ΪNULL
	}
	else if (!Q->left_num && Q->right_num) {
		//������Ϊ0���ұ߲�Ϊ0
		Q->point->right->left = NULL;//���ұߵ�һ���ڵ���ָ����ΪNULL
		Q->left_end = Q->point->right;//Ҫ���ƣ�������ĩ��ָ�룬ʹ֮��ΪNULL
	}
	//������߶���0�ڵ�
	//�޲���
	/*��������
	* 1.������С���Ҳ�ڵ���
	* 2.�����������Ҳ�ڵ���
	* 3.�����������Ҳ�ڵ���*/
	//���1��������С���Ҳ�ڵ���
	if (num < Q->right_num) {
		//�ȶ�λ�����λ��
		if (num > (Q->right_num / 2)) {
			//��������������Ҳ�ڵ�һ�룬���Ҳ�ĩ�˿�ʼ
			R_Node = Q->right_end;
			all = Q->right_num - num - 1;
			for (i = 0; i < all; i++) {
				R_Node = R_Node->left;
			}
			L_Node = R_Node->left;
			//��λ�ò�������ҽڵ�
		}
		else {
			//����������������Ҳ�ڵ�һ�룬����ڽڵ��Ҳ��һ�ڵ㿪ʼ
			L_Node = Q->point->right;
			all = num - 1;
			for (i = 0; i < all; i++) {
				L_Node = L_Node->right;
			}
			R_Node = L_Node->right;
			//��λ�ò�������ҽڵ�
		}
		//�ı�ͷ�ڵ����ҽڵ���
		Q->right_num -= num;
		Q->left_num += num;
		//������ڽڵ�
		Q->point->left = L_Node;
		Q->point->right = R_Node;
		L_Node->right = Q->point;
		R_Node->left = Q->point;
		//�������
		return 1;
	}
	//���2�������������Ҳ�ڵ���
	if (num == Q->right_num) {
		//�޸�ͷ�ڵ����ҽڵ���
		Q->right_num = 0;
		Q->left_num += num;
		//����ڽڵ�����Ҳ�ĩ��
		Q->point->right = NULL;
		Q->point->left = Q->right_end;
		Q->right_end->right = Q->point;
		Q->right_end = NULL;
		//�������
		return 1;
	}
	//���3�������������Ҳ�ڵ���
	/*�����Ҳ�ĩ������㹻�ڵ㣬Ȼ��ݹ飬�൱�����2*/
	if (num > Q->right_num) {
		all = num - Q->right_num;
		for (i = 0; i < all; i++) {
			Add_Right_LtoR(Q, 0);
		}
		Move_Head_Right(Q, num);
		return 1;
	}
	return 1;
}
int Add_Int_Rational(Rational Rational1, Rational Rational2, Rational C) {
	int D = 0;
	int B = Rational1->base;
	Rational_Node Q1, Q2;
	Q1 = Rational1->point->left;
	Q2 = Rational2->point->left;
	while (Q1 && Q2) {
		if (Q1->num + Q2->num + D < B) {
			Add_Left_RtoL(C, Q1->num + Q2->num + D);
			D = 0;
		}
		else {
			Add_Left_RtoL(C, Q1->num + Q2->num + D - B);
			D = 1;
		}
		Q1 = Q1->left;
		Q2 = Q2->left;
		//��λ���
	}
	while (Q1) {
		if (Q1->num + D < B) {
			Add_Left_RtoL(C, Q1->num + D);
			D = 0;
		}
		else {
			Add_Left_RtoL(C, Q1->num + D - B);
			D = 1;
		}
		Q1 = Q1->left;
	}
	while (Q2) {
		if (Q2->num + D < B) {
			Add_Left_RtoL(C, Q2->num + D);
			D = 0;
		}
		else {
			Add_Left_RtoL(C, Q2->num + D - B);
			D = 1;
		}
		Q2 = Q2->left;
	}
	return 1;
}
int Sub_Int_Rational(Rational Rational1, Rational Rational2, Rational C) {
	int D = 0;
	int B = Rational1->base;
	Rational_Node Q1, Q2;
	Q1 = Rational1->point->left;
	Q2 = Rational2->point->left;
	while (Q1 && Q2) {
		if (Q1->num - D >= Q2->num) {
			Add_Left_RtoL(C, Q1->num - D - Q2->num);
			D = 0;
		}
		else {
			Add_Left_RtoL(C, Q1->num + B - D - Q2->num);
			D = 1;
		}
		Q1 = Q1->left;
		Q2 = Q2->left;
	}
	while (Q1) {
		if (Q1->num - D >= 0) {
			Add_Left_RtoL(C, Q1->num - D);
			D = 0;
		}
		else {
			Add_Left_RtoL(C, Q1->num + B - D);
			D = 1;
		}
		Q1 = Q1->left;
	}
	/*while (Q2) {
		if (Q2->num - D > 0) {
			Add_Left_RtoL(C, Q2->num - D);
			D = 0;
		}
		else {
			Add_Left_RtoL(C, Q2->num + B - D);
			D = 1;
		}
		Q2 = Q2->left;
	}*///Q1����Q2���������������
	return 1;
}
int Mul_Int_Rational(Rational Rational1, char num, Rational C) {
	int D0 = 0, D1 = 0;
	Rational_Node Q;
	int B = Rational1->base;
	Q = Rational1->point->left;
	while (Q) {
		if (Q->num * num + D0 < B) {
			Add_Left_RtoL(C, Q->num * num + D0);
			D1 = 0;
		}
		else {
			D1 = (Q->num * num + D0) / B;
			Add_Left_RtoL(C, (Q->num * num + D0) % B);
		}
		//���浽��һλ����ʱ��D0=D1��
		D0 = D1;
		D1 = 0;
		Q = Q->left;
	}
	//Q�����һλ�󣬲鿴�Ƿ��н�λ
	if (D0) {
		Add_Left_RtoL(C, D0);//����н�λ����ֵ
	}
	return 1;
}
int Add_Rational(Rational Q1, Rational Q2, Rational C) {
	char all_sign = 1;
	int move_point = 0;
	/*��4�����,��Q1Ϊa��Q2Ϊb,
	* 1.a b ������
	* 2.a��b��
	* 3.a��b��
	* 4.a b ���Ǹ�
	*/
	//���1��a b ������
	if (Q1->sign > 0 && Q2->sign > 0) {
		//���߶�����������������Ϊ��������¼С�����ƶ���
		move_point = (Q1->right_num >= Q2->right_num) ? 
			(Q1->right_num) : (Q2->right_num);
		if (!move_point) {
			Add_Int_Rational(Q1, Q2, C);
			return 1;
		}//������߶���������ֱ�ӵ������ͼӷ�
		//���move_point��Ϊ0�����ƶ�С���㽫���Ϊ����
		Move_Head_Right(Q1, move_point);
		Move_Head_Right(Q2, move_point);
		Add_Int_Rational(Q1, Q2, C);
		//���ͼӷ����ٽ�С�����ƶ�����
		Move_Head_Left(Q1, move_point);
		Move_Head_Left(Q2, move_point);//�˴�Q1 Q2�ɲ��ָ�����Ϊ���뺯�������ݾ��Ѷ�����ֻ��Ҫ���
		Move_Head_Left(C, move_point);//��λ���C��Ϊ����
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	//���2��a��b��
	if (Q1->sign > 0 && Q2->sign < 0) {
		//��a-|b|
		//�ı�b�ķ��ţ����ü���
		Q2->sign = 1;//Q2��Ϊ�����ֵ
		Sub_Rational(Q1, Q2, C);
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	//���3��a��b��
	if (Q1->sign < 0 && Q2->sign > 0) {
		//�൱��b��a�ľ���ֵ
		//�ı�a�ķ���Ϊ��
		Q1->sign = 1;//Q1��Ϊ�����ֵ
		Sub_Rational(Q2, Q1, C);
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	//���4��a b ���Ǹ�
	if (Q1->sign < 0 && Q2->sign < 0) {
		//��ȡ���ţ�ȡ����ֵ���
		Q1->sign = 1;
		Q2->sign = 1;
		all_sign = -1;
		Add_Rational(Q1, Q2, C);
		C->sign = all_sign;
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	return 1;
}
int Sub_Rational(Rational Q1, Rational Q2, Rational C) {
	char all_sign = 1;
	int move_point = 0;
	/*��4�����,��Q1Ϊa��Q2Ϊb
	* 1.a b ������
	* 2.a��b��
	* 3.a��b��
	* 4.a b ���Ǹ�
	*/
	//���1��a b ������
	if (Q1->sign > 0 && Q2->sign > 0) {
		//���߶�����������������Ϊ��������¼С�����ƶ���
		move_point = (Q1->right_num >= Q2->right_num) ?
			(Q1->right_num) : (Q2->right_num);
		if (move_point) {
			//�����С�����֣��ƶ�С���㣬��Ϊ����
			Move_Head_Right(Q1, move_point);
			Move_Head_Right(Q2, move_point);
		}
		//�Ƚϴ�С
		if (Unsigned_ge_Rational(Q1, Q2)) {
			//���Q1���ڵ���Q2
			Sub_Int_Rational(Q1, Q2,C);
		}
		else {
			//���Q2����Q1
			all_sign = -1;//���Ϊ��
			Sub_Int_Rational(Q2, Q1, C);
		}
		C->sign = all_sign;//ȷ�Ͻ������
		if (move_point) {
			//���ԭ������С�����֣��ָ�С������
			Move_Head_Left(Q1, move_point);
			Move_Head_Left(Q2, move_point);//�˴���ѡ���ɶ���ԭ���ݲ��ָ�
			Move_Head_Left(C, move_point);//�ָ���С������
		}
		Clear_after_Sub(C);
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	//���2��a��b��
	if (Q1->sign > 0 && Q2->sign < 0) {
		//�൱��a��b�ľ���ֵ
		Q2->sign = 1;
		Add_Rational(Q1, Q2, C);
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	//���3��a��b��
	if (Q1->sign < 0 && Q2->sign > 0) {
		//�൱��a�ľ���ֵ��b����ȡ��
		Q1->sign = 1;
		Add_Rational(Q1, Q2, C);
		C->sign = -1;//�����ȡ��
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	//���4��a b ���Ǹ�
	if (Q1->sign < 0 && Q2->sign < 0) {
		//b�ľ���ֵ��a�ľ���ֵ
		Q1->sign = Q2->sign = 1;//��������ȡ����ֵ
		Sub_Rational(Q2, Q1, C);
		Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
		return 1;
	}
	return 1;
}
int Mul_Rational(Rational Q1, Rational Q2, Rational C) {
	//���ж��������������һ������Ϊ0������Ϊ0
	if (Is_Zero_Rational(Q1) || Is_Zero_Rational(Q2)) {
		ReInit_Rational(C,Q1->base);
		return 1;
	}
	char all_sign = 1;
	int move_point = 0;
	int finish_Move_point;
	int step=0;//���沽����ȷ��ÿ���ƶ���С����
	Rational_Node Now;
	/*�����������ݵ�C1 C2 C3*/
	Rational C1,C2,C3;
	init_Rational(&C1, Q1->base);
	init_Rational(&C2, Q1->base);
	init_Rational(&C3, Q1->base);//��ʼ��
	//�������
	all_sign = Q1->sign * Q2->sign;
	move_point = (Q1->right_num >= Q2->right_num) ?
		(Q1->right_num) : (Q2->right_num);
	Move_Head_Right(Q1, move_point);
	Move_Head_Right(Q2, move_point);//Q1 Q2��Ϊ����
	finish_Move_point = move_point * 2;//����ƶ�С�������Ϊ����������
	Now = Q1->point->left;
	while (Now) {//��Now��ΪNULL
		Mul_Int_Rational(Q2, Now->num, C2);
		Move_Head_Right(C2, step);//���γ˷������浽C2�����ƶ�С����
		Add_Rational(C1, C2, C3);//��һ�ε�C1���ͱ��ε�C2��ӵ�C3
		Copy_Rational(C3, C1);//��C3���Ƶ�C1
		ReInit_Rational(C2, Q1->base);
		ReInit_Rational(C3, Q1->base);//����C2��C3
		Now = Now->left;//�ƶ�����һλ
		step += 1;//������һ
	}
	Copy_Rational(C1, C);
	Move_Head_Left(C, finish_Move_point);//����������Ƶ�C�����ƶ�С����
	C->sign = all_sign;//�޸Ľ������
	//���ٺ�������Ŀռ�
	Free_Rational(&C1);
	Free_Rational(&C2);
	Free_Rational(&C3);
	Clear_Right_Rational(C);//ɾ����λ��С�����ֿ��ܳ��ֵ�ĩβ0
	return 1;
}
int Is_Zero_Rational(Rational Q) {
	if (!Q->left_num && !Q->right_num) {
		return 1;
	}
	Rational_Node Now;
	if (Q->left_num) {
		//�����಻Ϊ0������˿�ʼ����
		Now = Q->left_end;
		while (Now && (!Now->num || Now->num == POINT)) {
			Now = Now->right;
		}
		if (Now == NULL) {
			//�������������0����Ϊ0
			return 1;
		}
		else {
			return 0;
		}
	}
	if (Q->right_num) {
		//����Ҳ಻Ϊ0�����Ҷ˿�ʼ����
		Now = Q->right_end;
		while (Now && (!Now->num || Now->num == POINT)) {
			Now = Now->left;
		}
		if (Now == NULL) {
			//�������������0����Ϊ0
			return 1;
		}
		else {
			return 0;
		}
	}
	return 1;
}
int Unsigned_lt_Rational(Rational a, Rational b) {
	Clear_after_Sub(a);
	Clear_after_Sub(b);//����������0�ڵ�
	//�ȽϾ���ֵ��ֱ�����ӷ���
	if (a->left_num > b->left_num) {
		return 0;
	}
	if (a->left_num < b->left_num) {
		return 1;
	}
	Rational_Node A, B;
	if (a->left_num == b->left_num) {
		/*if (!a->left_num) {
			//������Ϊ0��ֱ�ӱȽ��Ҳ�
			A = a->point->right;
			B = b->point->right;
			while (A && B && (A->num == B->num)) {
				A = A->right;
				B = B->right;
			}//�ƶ�����һ������ͬ��С��λ,����һ�����������һλ
			if (!A && !B) {
				//A B ͬʱ�����һλ,��������ͬ
				return 0;
			}
			if (!A) {
				//���A�����һλ,�ж�B�����Ƿ���0
				while (B && !B->num) {
					B = B->right;
				}
				if (!B) {
					//���BΪNULL��֤��B����ȫΪ0
					return 0;
				}
				else {
					//B���治ȫΪ0����a<b
					return 1;
				}
			}
			if (!B) {
				//��B�ȵ����һλ����A������С��B
				return 0;
			}
			//�����������߶�û�����һλ
			if (A->num < B->num) {
				return 1;
			}
			else {
				return 0;
			}
		}///////////////////////////*/
		if(a->left_num){
			//�����಻Ϊ0���ȱȽ����
			A = a->left_end;
			B = b->left_end;
			while ((A->num == B->num) && (A->num!=POINT)) {
				A = A->right;
				B = B->right;
			}//�ƶ�����һ������ͬ������λ
			if (A->num == POINT) {
				//�������С���㣬�Ƚ��Ҳ�
			}
			else {
				//û��С���㣬ֱ�ӱȽ�
				if (A->num < B->num) {
					return 1;
				}
				else {
					return 0;
				}
			}//////////////////////////
		}
		//���±Ƚ��Ҳ�
		A = a->point->right;
		B = b->point->right;
		while (A && B && (A->num == B->num)) {
			A = A->right;
			B = B->right;
		}//�ƶ�����һ������ͬ��С��λ,����һ�����������һλ
		if (!A && !B) {
			//A B ͬʱ�����һλ,��������ͬ
			return 0;
		}
		if (!A) {
			//���A�����һλ,�ж�B�����Ƿ���0
			while (B && !B->num) {
				B = B->right;
			}
			if (!B) {
				//���BΪNULL��֤��B����ȫΪ0
				return 0;
			}
			else {
				//B���治ȫΪ0����a<b
				return 1;
			}
		}
		if (!B) {
			//��B�ȵ����һλ����A������С��B
			return 0;
		}
		//�����������߶�û�����һλ
		if (A->num < B->num) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return -1;
}
int Unsigned_gt_Rational(Rational a, Rational b) {
	//���ںż�С�ںŵ����ݽ���
	return Unsigned_lt_Rational(b, a);
}
int Unsigned_eq_Rational(Rational a, Rational b) {
	Clear_after_Sub(a);
	Clear_after_Sub(b);//����������0�ڵ�
	if (a->left_num != b->left_num) {
		return 0;
	}
	else {
		//a b���ڵ�����ͬ
		Rational_Node A, B;
		if (a->left_num) {
			//a b���ڵ�����Ϊ0
			A = a->left_end;
			B = b->left_end;
			while ((A->num == B->num) && (A->num != POINT)) {
				A = A->right;
				B = B->right;
			}//�ƶ�����һ������ͬ������λ
			if (A->num != POINT) {
				//δ��С�����˳�������ͬ
				return 0;
			}
			//���ڵ㶼��ͬ���Ƚ��Ҳ�
		}
		//���ڵ���Ϊ0��ڵ���ͬ���Ƚ��Ҳ�
		A = a->point->right;
		B = b->point->right;
		while (A && B && (A->num == B->num)) {
			A = A->right;
			B = B->right;
		}//�ƶ�����һ������ͬ��С��λ,����һ�����������һλ
		//////////////
		if (!A && !B) {
			//A B ͬʱ�����һλ,��������ͬ
			return 1;
		}
		if (!A) {
			//���A�����һλ,�ж�B�����Ƿ���0
			while (B && !B->num) {
				B = B->right;
			}
			if (!B) {
				//���BΪNULL��֤��B����ȫΪ0
				return 1;
			}
			else {
				//B���治ȫΪ0����a!=b
				return 0;
			}
		}
		if (!B) {
			//��B�ȵ����һλ���鿴A�����Ƿ���0
			while (A && !A->num) {
				A = A->right;
			}
			if (!A) {
				//���AΪNULL��֤��A����ȫΪ0
				return 1;
			}
			else {
				//A���治ȫΪ0����a!=b
				return 0;
			}
		}
		//�����������߶�û�����һλ,��ز���ͬ
		return 0;
	}
}
int Unsigned_le_Rational(Rational a, Rational b) {
	//С�ڵ��ڼ�С�ں͵��ڵĻ�
	if (Unsigned_lt_Rational(a, b) || Unsigned_eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
int Unsigned_ge_Rational(Rational a, Rational b) {
	//���ڵ��ڼ����ں͵��ڵĻ�
	if (Unsigned_gt_Rational(a, b) || Unsigned_eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
int lt_Rational(Rational a, Rational b) {
	//�ж��Ƿ�a<b
	if (a->sign > 0 && b->sign < 0) {
		return 0;
	}
	if (a->sign < 0 && b->sign > 0) {
		return 1;
	}
	//���˴���a bͬ��
	char sign = a->sign;
	if (sign < 0) {
		if (Unsigned_gt_Rational(a, b)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {//a b ��������
		if (Unsigned_lt_Rational(a, b)) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
int gt_Rational(Rational a, Rational b) {
	return lt_Rational(b, a);
}
int eq_Rational(Rational a, Rational b) {
	if (a->sign != b->sign ) {
		return 0;
	}
	//���˴���a bͬ��
	if (Unsigned_eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
int le_Rational(Rational a, Rational b) {
	if (lt_Rational(a, b) || eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
int ge_Rational(Rational a, Rational b) {
	if (gt_Rational(a, b) || eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
char Get_Num(int end) {
	/*��ȡ���룬�������룬��������*/
	end = (int)end;
	if (end<0||end>36) {
		return -1;
	}
	char ch;
	ch = getchar();
	if (isdigit(ch)) {
		ch -= 48;
		if (ch <= end) {
			return ch;
		}
		else return -1;
	}
	if (ch == '.') {
		return POINT;
	}
	if (ch == '\n') {
		return '\n';
	}
	return -1;
}
char Get_Num_Alpha(int end) {
	if (!isalpha(end)) {
		return -1;
	}
	char ch;
	if ((ch = getchar()) == '.') {
		return POINT;
	}
	if (isdigit(ch)) {
		//���������ֱ�ӷ���
		ch -= 48;
		return ch;
	}
	if (isalpha(ch)) {
		//�������ĸ��ת���ɴ�д�����жϷ�Χ
		ch = (char)toupper(ch);
		end = (int)toupper(end);
		if (ch <= end) {
			return ch;
		}
		else {
			return -1;
		}
	}
	if (ch == '\n') {
		return '\n';
	}
	//��������Ȳ���С���㣬Ҳ�������֣�Ҳ������ĸ��ֱ�ӷ���-1
	return -1;
}
char Alpha_Turn_Num(int ch) {
	char num;
	num = ch - 'A';//A��10����Եģ�B��11��C��12
	return num + 10;
}
char Num_Turn_Alpha(int num) {
	if (num >= 0 && num <= 9) {
		return 48 + num;
	}
	if (num >= 10) {
		return 'A' + num - 10;
	}
	return -1;
}
int Input_Rational(Rational* Q, int Base) {
	init_Rational(Q, Base);//��ʼ���ṹ
	char ch;
	char End;
	char have_Point = 0;
	ch = getchar();
	if (ch == '-') {
		(*Q)->sign = -1;
	}
	else if (ch == '+') {
		(*Q)->sign = 1;
	}
	else {
		ungetc(ch, stdin);
	}
	if (Base <= 10) {
		//ʮ�������ڵ�����ֻ������
		while ((ch = Get_Num(Base)) != '\n') {
			if (ch == -1) {
				//�Ƿ����룬�˳�
				return -1;
			}
			if (ch == POINT && have_Point == 0) {
				//����С���㣬�Ժ�ڵ�����Ҳ�
				have_Point = 1;
				continue;
			}
			if (ch == POINT && have_Point == 1) {
				//������С���㣬�Ƿ�����
				return -1;
			}
			if (have_Point == 0) {
				Add_Left_LtoR(*Q, ch);//����Ϸ�����
				continue;
			}
			if (have_Point == 1) {
				//���Ҳ��������
				Add_Right_LtoR(*Q, ch);
				continue;
			}
		}
		//�˴�Ϊ���»س���ֱ�ӷ���
		return 1;
	}
	if (Base > 10 && Base<=36) {
		//���ƴ���10
		End = 'A' + (Base - 10 - 1);
		while ((ch = Get_Num_Alpha(End)) != '\n') {
			if (ch == -1) {
				//�Ƿ�����
				return -1;
			}
			if (ch == POINT) {
				have_Point += 1;
				if (have_Point > 1) {
					//С���㳬��һ�����Ƿ�����
					return -1;
				}
				continue;
			}
			
			if (isalpha(ch)) {
				//���ch����ĸ��ת��������
				ch = Alpha_Turn_Num(ch);
			}
			if (have_Point == 0) {
				Add_Left_LtoR(*Q, ch);
				continue;
			}
			if (have_Point == 1) {
				Add_Right_LtoR(*Q, ch);
				continue;
			}
		}
		return 1;
	}
	return -1;
}
int Output_Rational(Rational Q) {
	if (Q->sign > 0) {
		putchar('+');
	}if (Q->sign < 0) {
		putchar('-');
	}
	Rational_Node Now;
	if (Q->left_num) {
		//�����಻Ϊ0�������ĩ�˿�ʼ
		Now = Q->left_end;
		while (Now) {
			if (Now->num != POINT) {
				printf("%c", Num_Turn_Alpha(Now->num));
			}
			else {
				printf(".");
			}
			Now = Now->right;
		}
		printf("\n");//��ӡ��������س�
		return 1;
	}
	if (Q->right_num) {
		//����Ҳ಻Ϊ0
		//���жϸ����Ƿ�Ϊ0
		if (Is_Zero_Rational(Q)) {
			printf("0\n");
			return 1;
		}
		Now = Q->point->right;
		printf("0.");
		while (Now) {
			printf("%c", Num_Turn_Alpha(Now->num));
			Now = Now->right;
		}
		printf("\n");
		return 1;
	}
	printf("0\n");
	return 1;
}
//////*********�汾����1.0
int Div_Int_Rational(Rational Q1, Rational Q2, Rational C) {
	int bite=0, num=0;
	Rational San, Story_a,Story_b;

	init_Rational(&Story_a, Q1->base);
	init_Rational(&Story_b, Q1->base);
	init_Rational(&San, Q1->base);//�����ʱ�����ĳ�ʼ��

	bite = Q1->left_num - Q2->left_num;//bite�洢���ߵ�λ����
	while (bite>=0) {
		//��bite���ڵ���0ʱ
		Copy_Rational(Q2, Story_b);
		Move_Head_Right(Story_b, bite);//Q2���Ƶ�Story_b���ƶ�С������Ϊ��ʱ����
		while (ge_Rational(Q1, Story_b)) {
			//���Q1����Story_b
			Sub_Rational(Q1, Story_b,Story_a);
			num += 1;
			Copy_Rational(Story_a, Q1);//����������һ����ƻ�Q1
			ReInit_Rational(Story_a, Q1->base);//��ʱ����story_a���ó�ʼ��
		}
		//�˳�ѭ����Q1�Ѿ�С��Story_b
		bite -= 1;
		Add_Left_LtoR(San, num);
		num = 0;//������������Ϊ0
	}
	//�̸��Ƶ�C
	Copy_Rational(San, C);
	//������������ٺ�����ʱ�����ռ�
	Free_Rational(&Story_a);
	Free_Rational(&Story_b);
	Free_Rational(&San);
	return 1;
}
int Div_Rational(Rational Q1, Rational Q2, Rational C) {
	int all_sign, move_point, add_move=0, exact_move=EXACT;
	all_sign = Q1->sign * Q2->sign;
	move_point = (Q1->right_num >= Q2->right_num) ? 
		(Q1->right_num) : (Q2->right_num);
	Move_Head_Right(Q1, move_point);
	Move_Head_Right(Q2, move_point);
	if (Q1->left_num < Q2->left_num) {
		add_move = Q2->left_num - Q1->left_num;
	}
	Move_Head_Right(Q1, exact_move + add_move);//������С���������ƶ����õ����������ǰ�ƶ�
	Div_Int_Rational(Q1, Q2, C);
	C->sign = all_sign;//�޸Ľ������
	Clear_after_Sub(C);//ɾ�����ǰ����ܳ��ֵ�0
	Move_Head_Left(C, exact_move + add_move);
	Clear_Right_Rational(C);//ɾ��С��ĩβ���ܳ��ֵ�0
	return 1;
}


/*************** �汾����1.1  *******************/

int Clear_Right_Rational(Rational Q) {
	if (Q->right_num == 0) {
		return 1;//��С������ֱ�ӷ���
	}
	Rational_Node point = Q->right_end;
	while (point->num == 0 && Q->right_num != 0) {
		Q->right_end = point->left;
		free(point);
		point = Q->right_end;//�ͷ�С������0��㣬������βָ��ǰ��
		Q->right_end->right = NULL;
		Q->right_num--;//��β�����ָ��ΪNULL��С�����ּ�����һ
	}
	return 1;
}







