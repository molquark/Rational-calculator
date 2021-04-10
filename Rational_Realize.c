/*使用双向链表存储有理数,将其抽象为Rational型数据类型
* 加入头结构及入口节点，通过头结构存储有理数相关信息
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
		fprintf(stderr, "无法申请空间作为Rational_Node_ADT节点");
		exit(EXIT_FAILURE);
	}
	(*Node)->num = num;
	(*Node)->left = (*Node)->right = NULL;
	return 1;
}
int init_Rational(Rational* Q,int B) {
	if (!((*Q) = (Rational)malloc(sizeof(struct Rational_Head_ADT)))) {
		fprintf(stderr, "无法申请空间作为Rational_Head_ADT节点");
		exit(EXIT_FAILURE);
	}
	(*Q)->base = B;//设置进制
	(*Q)->sign = +1;//设置符号为正
	(*Q)->left_num = (*Q)->right_num = 0;//左右节点为0
	Create_Rational_Node(&((*Q)->point), POINT);//入口节点，num为POINT
	(*Q)->left_end = (*Q)->right_end = NULL;//左右末端指针为NULL
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
			Q->left_num = 0;//清除左侧节点并重置头节点数据
		}
	}
	if (Q->right_num) {
		Now = Q->right_end;
		while (Now->num != POINT) {
			Now = Now->left;
			free(Now->right);
			Q->right_end = NULL;
			Q->right_num = 0;//清除左侧节点并重置头节点数据
		}
	}
	return 1;
}
int Copy_Rational(Rational Q1, Rational Q2) {
	ReInit_Rational(Q2, Q1->base);//重置Q2
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
		//左侧有节点
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
		//右侧有节点
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
		Q->point->left = L_Node;//left指向新节点
		L_Node->left = NULL;
		L_Node->right = Q->point;//新节点右边指向入口节点
		Q->left_end = L_Node;
		Q->left_num += 1;
		return 1;
	}
	if (Q->left_num == 1) {
		L_Node = Q->left_end;
		R_Node = Q->point;
		//创建新节点并插入到L_Node和R_Node之间
		Create_Rational_Node(&New, num);
		L_Node->right = New;
		New->left = L_Node;
		R_Node->left = New;
		New->right = R_Node;
		Q->left_num += 1;
		return 1;
	}
	//以下则为Q->left_num大于1的情况
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
	/*左侧从右到左插入，直接往左侧末端节点的左侧插入*/
	Rational_Node New;
	if (!Q->left_num) {
		//如果左侧为0
		Create_Rational_Node(&New, num);
		Q->left_end = New;
		Q->point->left = New;
		New->right = Q->point;
		Q->left_num += 1;//计数加一
		return 1;
	}
	//如果左侧不为0
	Create_Rational_Node(&New, num);
	New->right = Q->left_end;
	Q->left_end->left = New;//New接在左侧末端
	Q->left_end = New;//left_end指向New
	Q->left_num += 1;//计数加一
	return 1;
}
int Add_Right_LtoR(Rational Q, char num) {
	Rational_Node New;
	if (!Q->right_num) {
		Create_Rational_Node(&New, num);
		Q->point->right = New;
		New->left = Q->point;
		Q->right_end = New;
		Q->right_num += 1;//计数加一
		return 1;
	}
	//如果右侧不为0
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
		//如果Now为NULL，直接退出
		return 1;
	}
	while (Now->num == 0) {
		Now = Now->right;
		Q->left_end = Now;//移动左侧end
		Q->left_num -= 1;//更新左侧节点数值
		free(Now->left);//Now移动到右侧节点，并释放左侧节点
		Now->left = NULL;
	}
	return 1;
}
int Move_Head_Left(Rational Q, int num) {
	if (!num)return 1;
	Rational_Node L_Node,R_Node;
	int i,all;
	//把入口节点抽离出双向链表
	if (Q->left_num && Q->right_num) {
		//如果左右节点都不为0
		Q->point->left->right = Q->point->right;//入口的左侧节点的右指针指向入口右侧节点
		Q->point->right->left = Q->point->left;//入口的右侧节点的左指针指向入口左侧节点
	}
	else if (Q->left_num && !Q->right_num) {
		//如果右边为0，左边不为0
		Q->point->left->right = NULL;//把左边第一个节点的右指针设为NULL
		Q->right_end = Q->point->left;//入口节点要左移，则右末端指针要设置
	}
	else if (!Q->left_num && Q->right_num) {
		//如果左边为0，右边不为0
		Q->point->right->left = NULL;//把右边第一个节点左指针设为NULL
	}
		//如果两边都是0节点
		//无操作
	/*分类讨论
	* 1.左移数小于左侧节点数
	* 2.左移数等于左侧节点数
	* 3.左移数大于左侧节点数*/
	//情况1，左移数小于左侧节点数
	if (num < Q->left_num) {
		if (num > (Q->left_num / 2)) {//如果左移数大于左侧节点的一半
			all = Q->left_num - num - 1;
			L_Node = Q->left_end;//从左侧末端节点开始移动
			for (i = 0; i < all; i++) {
				L_Node = L_Node->right;
			}
			R_Node = L_Node->right;
			//定位好插入的左右节点
		}
		else {//如果左移数小于左侧节点的一半
			all = num - 1;
			R_Node = Q->point->left;//从入口节点的左侧第一个节点开始
			for (i = 0; i < all; i++) {
				R_Node = R_Node->left;
			}
			L_Node = R_Node->left;
			//定位好插入的左右节点
		}
		Q->left_num -= num;
		Q->right_num += num;
		//移动头节点，左右节点数目变化
		//左右末端指针不变
		L_Node->right = Q->point;
		Q->point->left = L_Node;
		R_Node->left = Q->point;
		Q->point->right = R_Node;
		//插入入口节点
		//结束
		return 1;
	}
	//情况2，左移数等于左侧节点数
	if (num == Q->left_num) {
		//左右节点数变化
		Q->left_num = 0;
		Q->right_num += num;
		//插入入口节点
		Q->point->left = NULL;//入口左侧指针为NULL
		Q->point->right = Q->left_end;//入口右侧指向原左侧末端节点
		Q->left_end->left = Q->point;//原左侧末端节点左侧指向入口节点
		Q->left_end = NULL;//头节点左侧末端指针设为NULL
		//结束
		return 1;
	}
	//情况3，左移数大于左侧节点数
	if (num > Q->left_num) {
		/*先往左末端添加足够的值为0的节点，再递归，相当于情况2*/
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
	//把入口节点抽离出双向链表
	if (Q->left_num && Q->right_num) {
		//如果左右节点都不为0
		Q->point->left->right = Q->point->right;//入口的左侧节点的右指针指向入口右侧节点
		Q->point->right->left = Q->point->left;//入口的右侧节点的左指针指向入口左侧节点
	}
	else if (Q->left_num && !Q->right_num) {
		//如果右边为0，左边不为0
		Q->point->left->right = NULL;//把左边第一个节点的右指针设为NULL
	}
	else if (!Q->left_num && Q->right_num) {
		//如果左边为0，右边不为0
		Q->point->right->left = NULL;//把右边第一个节点左指针设为NULL
		Q->left_end = Q->point->right;//要右移，设置左末端指针，使之不为NULL
	}
	//如果两边都是0节点
	//无操作
	/*分类讨论
	* 1.右移数小于右侧节点数
	* 2.右移数等于右侧节点数
	* 3.右移数大于右侧节点数*/
	//情况1，右移数小于右侧节点数
	if (num < Q->right_num) {
		//先定位插入的位置
		if (num > (Q->right_num / 2)) {
			//如果右移数大于右侧节点一半，从右侧末端开始
			R_Node = Q->right_end;
			all = Q->right_num - num - 1;
			for (i = 0; i < all; i++) {
				R_Node = R_Node->left;
			}
			L_Node = R_Node->left;
			//定位好插入的左右节点
		}
		else {
			//如果右移数不大于右侧节点一半，从入口节点右侧第一节点开始
			L_Node = Q->point->right;
			all = num - 1;
			for (i = 0; i < all; i++) {
				L_Node = L_Node->right;
			}
			R_Node = L_Node->right;
			//定位好插入的左右节点
		}
		//改变头节点左右节点数
		Q->right_num -= num;
		Q->left_num += num;
		//插入入口节点
		Q->point->left = L_Node;
		Q->point->right = R_Node;
		L_Node->right = Q->point;
		R_Node->left = Q->point;
		//插入完成
		return 1;
	}
	//情况2，右移数等于右侧节点数
	if (num == Q->right_num) {
		//修改头节点左右节点数
		Q->right_num = 0;
		Q->left_num += num;
		//把入口节点插入右侧末端
		Q->point->right = NULL;
		Q->point->left = Q->right_end;
		Q->right_end->right = Q->point;
		Q->right_end = NULL;
		//插入完成
		return 1;
	}
	//情况3，右移数大于右侧节点数
	/*先往右侧末端添加足够节点，然后递归，相当于情况2*/
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
		//逐位相加
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
	}*///Q1大于Q2，不存在这种情况
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
		//更替到下一位数字时，D0=D1；
		D0 = D1;
		D1 = 0;
		Q = Q->left;
	}
	//Q到最大一位后，查看是否有进位
	if (D0) {
		Add_Left_RtoL(C, D0);//如果有进位，赋值
	}
	return 1;
}
int Add_Rational(Rational Q1, Rational Q2, Rational C) {
	char all_sign = 1;
	int move_point = 0;
	/*共4种情况,设Q1为a，Q2为b,
	* 1.a b 都是正
	* 2.a正b负
	* 3.a负b正
	* 4.a b 都是负
	*/
	//情况1，a b 都是正
	if (Q1->sign > 0 && Q2->sign > 0) {
		//两者都是正，把有理数化为整数，记录小数点移动数
		move_point = (Q1->right_num >= Q2->right_num) ? 
			(Q1->right_num) : (Q2->right_num);
		if (!move_point) {
			Add_Int_Rational(Q1, Q2, C);
			return 1;
		}//如果两者都是整数，直接调用整型加法
		//如果move_point不为0，则移动小数点将其变为整数
		Move_Head_Right(Q1, move_point);
		Move_Head_Right(Q2, move_point);
		Add_Int_Rational(Q1, Q2, C);
		//整型加法后再将小数点移动回来
		Move_Head_Left(Q1, move_point);
		Move_Head_Left(Q2, move_point);//此处Q1 Q2可不恢复，认为输入函数的数据均已丢弃，只需要结果
		Move_Head_Left(C, move_point);//移位后的C即为所求
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	//情况2，a正b负
	if (Q1->sign > 0 && Q2->sign < 0) {
		//即a-|b|
		//改变b的符号，引用减法
		Q2->sign = 1;//Q2变为其绝对值
		Sub_Rational(Q1, Q2, C);
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	//情况3，a负b正
	if (Q1->sign < 0 && Q2->sign > 0) {
		//相当于b减a的绝对值
		//改变a的符号为正
		Q1->sign = 1;//Q1变为其绝对值
		Sub_Rational(Q2, Q1, C);
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	//情况4，a b 都是负
	if (Q1->sign < 0 && Q2->sign < 0) {
		//提取负号，取绝对值相加
		Q1->sign = 1;
		Q2->sign = 1;
		all_sign = -1;
		Add_Rational(Q1, Q2, C);
		C->sign = all_sign;
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	return 1;
}
int Sub_Rational(Rational Q1, Rational Q2, Rational C) {
	char all_sign = 1;
	int move_point = 0;
	/*共4种情况,设Q1为a，Q2为b
	* 1.a b 都是正
	* 2.a正b负
	* 3.a负b正
	* 4.a b 都是负
	*/
	//情况1，a b 都是正
	if (Q1->sign > 0 && Q2->sign > 0) {
		//两者都是正，把有理数化为整数，记录小数点移动数
		move_point = (Q1->right_num >= Q2->right_num) ?
			(Q1->right_num) : (Q2->right_num);
		if (move_point) {
			//如果有小数部分，移动小数点，化为整数
			Move_Head_Right(Q1, move_point);
			Move_Head_Right(Q2, move_point);
		}
		//比较大小
		if (Unsigned_ge_Rational(Q1, Q2)) {
			//如果Q1大于等于Q2
			Sub_Int_Rational(Q1, Q2,C);
		}
		else {
			//如果Q2大于Q1
			all_sign = -1;//结果为负
			Sub_Int_Rational(Q2, Q1, C);
		}
		C->sign = all_sign;//确认结果符号
		if (move_point) {
			//如果原数据有小数部分，恢复小数部分
			Move_Head_Left(Q1, move_point);
			Move_Head_Left(Q2, move_point);//此处可选，可丢弃原数据不恢复
			Move_Head_Left(C, move_point);//恢复答案小数部分
		}
		Clear_after_Sub(C);
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	//情况2，a正b负
	if (Q1->sign > 0 && Q2->sign < 0) {
		//相当于a加b的绝对值
		Q2->sign = 1;
		Add_Rational(Q1, Q2, C);
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	//情况3，a负b正
	if (Q1->sign < 0 && Q2->sign > 0) {
		//相当于a的绝对值加b，再取负
		Q1->sign = 1;
		Add_Rational(Q1, Q2, C);
		C->sign = -1;//最后结果取负
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	//情况4，a b 都是负
	if (Q1->sign < 0 && Q2->sign < 0) {
		//b的绝对值减a的绝对值
		Q1->sign = Q2->sign = 1;//两个数都取绝对值
		Sub_Rational(Q2, Q1, C);
		Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
		return 1;
	}
	return 1;
}
int Mul_Rational(Rational Q1, Rational Q2, Rational C) {
	//先判断特殊情况，存在一个乘数为0，则结果为0
	if (Is_Zero_Rational(Q1) || Is_Zero_Rational(Q2)) {
		ReInit_Rational(C,Q1->base);
		return 1;
	}
	char all_sign = 1;
	int move_point = 0;
	int finish_Move_point;
	int step=0;//保存步数，确定每步移动的小数点
	Rational_Node Now;
	/*创建保存数据的C1 C2 C3*/
	Rational C1,C2,C3;
	init_Rational(&C1, Q1->base);
	init_Rational(&C2, Q1->base);
	init_Rational(&C3, Q1->base);//初始化
	//创建完毕
	all_sign = Q1->sign * Q2->sign;
	move_point = (Q1->right_num >= Q2->right_num) ?
		(Q1->right_num) : (Q2->right_num);
	Move_Head_Right(Q1, move_point);
	Move_Head_Right(Q2, move_point);//Q1 Q2化为整数
	finish_Move_point = move_point * 2;//结果移动小数点距离为乘数的两倍
	Now = Q1->point->left;
	while (Now) {//当Now不为NULL
		Mul_Int_Rational(Q2, Now->num, C2);
		Move_Head_Right(C2, step);//单次乘法，保存到C2，并移动小数点
		Add_Rational(C1, C2, C3);//上一次的C1，和本次的C2相加到C3
		Copy_Rational(C3, C1);//把C3复制到C1
		ReInit_Rational(C2, Q1->base);
		ReInit_Rational(C3, Q1->base);//重置C2，C3
		Now = Now->left;//移动到下一位
		step += 1;//步数加一
	}
	Copy_Rational(C1, C);
	Move_Head_Left(C, finish_Move_point);//整数结果复制到C，并移动小数点
	C->sign = all_sign;//修改结果符号
	//销毁函数申请的空间
	Free_Rational(&C1);
	Free_Rational(&C2);
	Free_Rational(&C3);
	Clear_Right_Rational(C);//删除移位后小数部分可能出现的末尾0
	return 1;
}
int Is_Zero_Rational(Rational Q) {
	if (!Q->left_num && !Q->right_num) {
		return 1;
	}
	Rational_Node Now;
	if (Q->left_num) {
		//如果左侧不为0，从左端开始遍历
		Now = Q->left_end;
		while (Now && (!Now->num || Now->num == POINT)) {
			Now = Now->right;
		}
		if (Now == NULL) {
			//如果整个链表都是0，则为0
			return 1;
		}
		else {
			return 0;
		}
	}
	if (Q->right_num) {
		//如果右侧不为0，从右端开始遍历
		Now = Q->right_end;
		while (Now && (!Now->num || Now->num == POINT)) {
			Now = Now->left;
		}
		if (Now == NULL) {
			//如果整个链表都是0，则为0
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
	Clear_after_Sub(b);//清除左侧无用0节点
	//比较绝对值，直接无视符号
	if (a->left_num > b->left_num) {
		return 0;
	}
	if (a->left_num < b->left_num) {
		return 1;
	}
	Rational_Node A, B;
	if (a->left_num == b->left_num) {
		/*if (!a->left_num) {
			//如果左侧为0，直接比较右侧
			A = a->point->right;
			B = b->point->right;
			while (A && B && (A->num == B->num)) {
				A = A->right;
				B = B->right;
			}//移动到第一个不相同的小数位,或有一个数到达最后一位
			if (!A && !B) {
				//A B 同时到最后一位,则两数相同
				return 0;
			}
			if (!A) {
				//如果A到最后一位,判断B后面是否都是0
				while (B && !B->num) {
					B = B->right;
				}
				if (!B) {
					//如果B为NULL，证明B后面全为0
					return 0;
				}
				else {
					//B后面不全为0，则a<b
					return 1;
				}
			}
			if (!B) {
				//若B先到最后一位，则A不可能小于B
				return 0;
			}
			//到这里则两者都没到最后一位
			if (A->num < B->num) {
				return 1;
			}
			else {
				return 0;
			}
		}///////////////////////////*/
		if(a->left_num){
			//如果左侧不为0，先比较左侧
			A = a->left_end;
			B = b->left_end;
			while ((A->num == B->num) && (A->num!=POINT)) {
				A = A->right;
				B = B->right;
			}//移动到第一个不相同的整数位
			if (A->num == POINT) {
				//如果到达小数点，比较右侧
			}
			else {
				//没到小数点，直接比较
				if (A->num < B->num) {
					return 1;
				}
				else {
					return 0;
				}
			}//////////////////////////
		}
		//以下比较右侧
		A = a->point->right;
		B = b->point->right;
		while (A && B && (A->num == B->num)) {
			A = A->right;
			B = B->right;
		}//移动到第一个不相同的小数位,或有一个数到达最后一位
		if (!A && !B) {
			//A B 同时到最后一位,则两数相同
			return 0;
		}
		if (!A) {
			//如果A到最后一位,判断B后面是否都是0
			while (B && !B->num) {
				B = B->right;
			}
			if (!B) {
				//如果B为NULL，证明B后面全为0
				return 0;
			}
			else {
				//B后面不全为0，则a<b
				return 1;
			}
		}
		if (!B) {
			//若B先到最后一位，则A不可能小于B
			return 0;
		}
		//到这里则两者都没到最后一位
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
	//大于号即小于号的数据交换
	return Unsigned_lt_Rational(b, a);
}
int Unsigned_eq_Rational(Rational a, Rational b) {
	Clear_after_Sub(a);
	Clear_after_Sub(b);//清除左侧无用0节点
	if (a->left_num != b->left_num) {
		return 0;
	}
	else {
		//a b左侧节点数相同
		Rational_Node A, B;
		if (a->left_num) {
			//a b左侧节点数不为0
			A = a->left_end;
			B = b->left_end;
			while ((A->num == B->num) && (A->num != POINT)) {
				A = A->right;
				B = B->right;
			}//移动到第一个不相同的整数位
			if (A->num != POINT) {
				//未到小数点退出，则不相同
				return 0;
			}
			//左侧节点都相同，比较右侧
		}
		//左侧节点数为0或节点相同，比较右侧
		A = a->point->right;
		B = b->point->right;
		while (A && B && (A->num == B->num)) {
			A = A->right;
			B = B->right;
		}//移动到第一个不相同的小数位,或有一个数到达最后一位
		//////////////
		if (!A && !B) {
			//A B 同时到最后一位,则两数相同
			return 1;
		}
		if (!A) {
			//如果A到最后一位,判断B后面是否都是0
			while (B && !B->num) {
				B = B->right;
			}
			if (!B) {
				//如果B为NULL，证明B后面全为0
				return 1;
			}
			else {
				//B后面不全为0，则a!=b
				return 0;
			}
		}
		if (!B) {
			//若B先到最后一位，查看A后面是否都是0
			while (A && !A->num) {
				A = A->right;
			}
			if (!A) {
				//如果A为NULL，证明A后面全为0
				return 1;
			}
			else {
				//A后面不全为0，则a!=b
				return 0;
			}
		}
		//到这里则两者都没到最后一位,则必不相同
		return 0;
	}
}
int Unsigned_le_Rational(Rational a, Rational b) {
	//小于等于即小于和等于的或
	if (Unsigned_lt_Rational(a, b) || Unsigned_eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
int Unsigned_ge_Rational(Rational a, Rational b) {
	//大于等于即大于和等于的或
	if (Unsigned_gt_Rational(a, b) || Unsigned_eq_Rational(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}
int lt_Rational(Rational a, Rational b) {
	//判断是否a<b
	if (a->sign > 0 && b->sign < 0) {
		return 0;
	}
	if (a->sign < 0 && b->sign > 0) {
		return 1;
	}
	//到此处则a b同号
	char sign = a->sign;
	if (sign < 0) {
		if (Unsigned_gt_Rational(a, b)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {//a b 都是正数
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
	//到此处则a b同号
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
	/*获取输入，处理输入，返回输入*/
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
		//如果是数字直接返回
		ch -= 48;
		return ch;
	}
	if (isalpha(ch)) {
		//如果是字母，转换成大写，再判断范围
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
	//到这里则既不是小数点，也不是数字，也不是字母，直接返回-1
	return -1;
}
char Alpha_Turn_Num(int ch) {
	char num;
	num = ch - 'A';//A是10，相对的，B是11，C是12
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
	init_Rational(Q, Base);//初始化结构
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
		//十进制以内的输入只有数字
		while ((ch = Get_Num(Base)) != '\n') {
			if (ch == -1) {
				//非法输入，退出
				return -1;
			}
			if (ch == POINT && have_Point == 0) {
				//输入小数点，以后节点加在右侧
				have_Point = 1;
				continue;
			}
			if (ch == POINT && have_Point == 1) {
				//有两个小数点，非法输入
				return -1;
			}
			if (have_Point == 0) {
				Add_Left_LtoR(*Q, ch);//插入合法数据
				continue;
			}
			if (have_Point == 1) {
				//往右侧插入数据
				Add_Right_LtoR(*Q, ch);
				continue;
			}
		}
		//此处为按下回车后，直接返回
		return 1;
	}
	if (Base > 10 && Base<=36) {
		//进制大于10
		End = 'A' + (Base - 10 - 1);
		while ((ch = Get_Num_Alpha(End)) != '\n') {
			if (ch == -1) {
				//非法输入
				return -1;
			}
			if (ch == POINT) {
				have_Point += 1;
				if (have_Point > 1) {
					//小数点超过一个，非法输入
					return -1;
				}
				continue;
			}
			
			if (isalpha(ch)) {
				//如果ch是字母，转换成数字
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
		//如果左侧不为0，从左侧末端开始
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
		printf("\n");//打印结束输出回车
		return 1;
	}
	if (Q->right_num) {
		//如果右侧不为0
		//先判断该数是否为0
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
//////*********版本更新1.0
int Div_Int_Rational(Rational Q1, Rational Q2, Rational C) {
	int bite=0, num=0;
	Rational San, Story_a,Story_b;

	init_Rational(&Story_a, Q1->base);
	init_Rational(&Story_b, Q1->base);
	init_Rational(&San, Q1->base);//相关临时变量的初始化

	bite = Q1->left_num - Q2->left_num;//bite存储两者的位数差
	while (bite>=0) {
		//当bite大于等于0时
		Copy_Rational(Q2, Story_b);
		Move_Head_Right(Story_b, bite);//Q2复制到Story_b并移动小数点作为临时减数
		while (ge_Rational(Q1, Story_b)) {
			//如果Q1大于Story_b
			Sub_Rational(Q1, Story_b,Story_a);
			num += 1;
			Copy_Rational(Story_a, Q1);//减法计数加一，差复制回Q1
			ReInit_Rational(Story_a, Q1->base);//临时变量story_a重置初始化
		}
		//退出循环后，Q1已经小于Story_b
		bite -= 1;
		Add_Left_LtoR(San, num);
		num = 0;//减法计数重置为0
	}
	//商复制到C
	Copy_Rational(San, C);
	//计算结束，销毁函数临时变量空间
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
	Move_Head_Right(Q1, exact_move + add_move);//被除数小数点往后移动，得到结果后再往前移动
	Div_Int_Rational(Q1, Q2, C);
	C->sign = all_sign;//修改结果符号
	Clear_after_Sub(C);//删除结果前面可能出现的0
	Move_Head_Left(C, exact_move + add_move);
	Clear_Right_Rational(C);//删除小数末尾可能出现的0
	return 1;
}


/*************** 版本更新1.1  *******************/

int Clear_Right_Rational(Rational Q) {
	if (Q->right_num == 0) {
		return 1;//无小数部分直接返回
	}
	Rational_Node point = Q->right_end;
	while (point->num == 0 && Q->right_num != 0) {
		Q->right_end = point->left;
		free(point);
		point = Q->right_end;//释放小数最后的0结点，并将结尾指针前移
		Q->right_end->right = NULL;
		Q->right_num--;//结尾结点右指针为NULL，小数部分计数减一
	}
	return 1;
}







