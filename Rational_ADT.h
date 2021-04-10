#ifndef RATIONAL_ADT
#define RATIONAL_ADT 0
#define POINT -128 //即（01000000）2
#define EXACT 20 //除法进行的精确度（也许吧）
struct Rational_Node_ADT {
	char num;
	struct Rational_Node_ADT* left;
	struct Rational_Node_ADT* right;
};
typedef struct Rational_Node_ADT* Rational_Node;
struct Rational_Head_ADT {
	char sign;//表示正负号
	int base;//表示进制
	int left_num;//左侧节点数
	int right_num;//右侧节点数
	struct Rational_Node_ADT* left_end;//左侧末端节点
	struct Rational_Node_ADT* right_end;//右侧末端节点
	struct Rational_Node_ADT* point;//正下方入口节点
};
typedef struct Rational_Head_ADT* Rational;

////////*****对节点的操作
/*创建一个Rational节点
* 初始条件：指针Node已声明
* 操作结果：创建一个值为num的Rational节点，地址赋给Node。
*/
int Create_Rational_Node(Rational_Node* Node, int num);
/*初始化结构
* 初始条件：声明Rational 型变量Q
* 操作结果：Q指向初始结构，包括头及入口节点,确定进制B。
*/
int init_Rational(Rational* Q, int B);
/*对结构恢复到初始化结构
* 初始条件：Q已经初始化或有数据
* 操作结果：Q指向初始化结构。
*/
int ReInit_Rational(Rational Q, int B);
/*复制结构
* 初始条件：Q1，Q2均已初始化
* 操作结果：将Q1复制到Q2.
*/
int Copy_Rational(Rational Q1, Rational Q2);
/*销毁结构
* 初始条件：Rational变量Q已初始化
* 操作结果：Q所指向的结构空间被释放，Q=NULL
*/
int Free_Rational(Rational* Q);
/*左侧从左到右输入
* 初始条件：Rational型变量Q已初始化
* 操作结果：往入口节点左侧插入一个节点，值为num。
*/
int Add_Left_LtoR(Rational Q, char num);
/*左侧从右到左输入
* 初始条件：Rational型变量Q已初始化
* 操作结果：往左侧节点末端右侧插入一个节点，值为num。
*/
int Add_Left_RtoL(Rational Q, char num);
/*右侧从左到右输入
* 初始条件：Rational型变量Q已初始化
* 操作结果：往右侧末端节点右侧插入一个节点，值为num。
*/
int Add_Right_LtoR(Rational Q, char num);
/*清理左侧无效的值为0的节点，减法后进行
* 初始条件：Rational型变量Q存在数据
* 操作结果：Q从左往右第一个非零节点前的所有零节点被删除
*/
int Clear_after_Sub(Rational Q);
////////******对头节点的操作
/*向左移动头节点及入口节点
* 初始条件：Q已初始化并至少插入一个节点
* 操作结果：入口节点插入到左侧第num个节点左侧，
* 若num大于左侧节点数，自动填充值为0的节点。
*/
int Move_Head_Left(Rational Q, int num);
/*向右移动头节点及入口节点
* 初始条件：Q已初始化并至少插入一个节点
* 操作结果：入口节点插入到右侧第num个节点右侧，
* 若num大于右侧节点数，自动填充值为0的节点。
*/
int Move_Head_Right(Rational Q, int num);
///////********整型运算
/*两个整型Rational变量相加
* 初始条件：Q1，Q2右侧无节点，左侧至少有一节点，C已初始化
* 操作结果：Q1，Q2相加，结果存储到C。
*/
int Add_Int_Rational(Rational Q1, Rational Q2, Rational C);
/*两个整型Rational变量相减
* 初始条件：Q1>=Q2,两者右侧均无节点，左侧均至少有一节点，均为正数，C已初始化
* 操作结果：Q1-Q2，结果存储到C。
*/
int Sub_Int_Rational(Rational Q1, Rational Q2, Rational C);
/*整型Rational变量乘以num
* 初始条件：Q右侧无节点，左侧至少一节点，C已初始化
* 操作结果：Q*num，结果存储到C。
*/
int Mul_Int_Rational(Rational Q, char num, Rational C);
/////////********抽象出有理数运算
/*两个有理数Rational变量相加
* 初始条件：C已初始化
* 操作结果：Q1+Q2，结果存储到C。
*/
int Add_Rational(Rational Q1, Rational Q2, Rational C);
/*两个有理数Rational变量相减
* 初始条件：C已初始化
* 操作结果：Q1-Q2，结果存储到C。
*/
int Sub_Rational(Rational Q1, Rational Q2, Rational C);
/*两个有理数Rational变量相乘
* 初始条件：C已初始化
* 操作结果：Q1*Q2，结果存储到C。
*/
int Mul_Rational(Rational Q1, Rational Q2, Rational C);
/////////***********各种比较大小
/*判断Rational型变量Q是否为0
* 初始条件：Q已初始化
* 操作结果：若Q为0，返回1，否则返回0。
*/
int Is_Zero_Rational(Rational Q);
/*比较绝对值大小 是否|a|<|b|
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若|a|<|b|，返回1，否则返回0。
*/
int Unsigned_lt_Rational(Rational a, Rational b);
/*比较绝对值大小 是否|a|>|b|
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若|a|>|b|，返回1，否则返回0。
*/
int Unsigned_gt_Rational(Rational a, Rational b);
/*比较绝对值是否相等 是否|a|=|b|
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若|a|=|b|，返回1，否则返回0。
*/
int Unsigned_eq_Rational(Rational a, Rational b);
/*比较绝对值大小 是否|a|<=|b|
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若|a|<=|b|，返回1，否则返回0。
*/
int Unsigned_le_Rational(Rational a, Rational b);
/*比较绝对值大小 是否|a|>=|b|
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若|a|>=|b|，返回1，否则返回0。
*/
int Unsigned_ge_Rational(Rational a, Rational b);
/*比较有理数大小 是否a<b
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若a<b，返回1，否则返回0。
*/
int lt_Rational(Rational a, Rational b);
/*比较有理数大小 是否a>b
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若a>b，返回1，否则返回0。
*/
int gt_Rational(Rational a, Rational b);
/*比较有理数大小 是否a=b
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若a=b，返回1，否则返回0。
*/
int eq_Rational(Rational a, Rational b);
/*比较有理数大小 是否a<=b
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若a<=b，返回1，否则返回0。
*/
int le_Rational(Rational a, Rational b);
/*比较有理数大小 是否a>=b
* 初始条件：a，b左右两侧均至少有一个节点
* 操作结果：若a>=b，返回1，否则返回0。
*/
int ge_Rational(Rational a, Rational b);
////////////**************获取输入
/*获取数字以及小数点输入并返回
* 初始条件：无
* 操作结果：返回输入的一个字符，数字（0~end）或小数点，和回车
* 小数点返回POINT，其余非法字符返回-1
*/
char Get_Num(int end);
/*获取数字，字母及小数点输入并返回
* 初始条件：end 为某个字母
* 操作结果：返回输入的一个字符，数字，以及A到end的字母，和回车
* 小数点返回POINT，字母返回相应的大写,非法输入返回-1
*/
char Get_Num_Alpha(int end);
/*字母转相关进制的数字
* 初始条件：ch为大写字母
* 操作结果：返回ch该字母相对应的数字，如A，返回10
*/
char Alpha_Turn_Num(int ch);
/*数字转相关进制的字母
* 初始条件:num 为大于等于0小于36的非负数
* 操作结果：返回相应的字母或数字的ASCII码
*/
char Num_Turn_Alpha(int num);
//////////////***********抽象出操作
/*输入一个有理数
* 初始条件：Q被声明，未初始化，Base在（2~36）间，
* 输入流中为无符号的有理数
* 操作结果：Q指向输入的有理数（无符号），输入失败会返回-1，
* 否则返回1
*/
int Input_Rational(Rational* Q, int Base);
/*输出一个有理数
* 初始条件：Q为已输入的数据
* 操作结果：在屏幕上打印出数据，包括符号
*/
int Output_Rational(Rational Q);
////////////////***********版本更新1.0
/*两个整型Rational变量相除
* 初始条件：Q1，Q2右侧无节点，左侧至少有一节点，C已初始化，
* 且Q1>Q2,两者均为正数
* 操作结果：Q1/Q2，商存储到C，余数r存储到Q1。
*/
int Div_Int_Rational(Rational Q1, Rational Q2, Rational C);
/*两个有理数Rational型变量相除
* 初始条件：Q2不为0，C已初始化
* 操作结果：Q1/Q2，结果存储到C，
*/
int Div_Rational(Rational Q1, Rational Q2, Rational C);











#endif
