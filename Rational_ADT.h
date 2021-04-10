#ifndef RATIONAL_ADT
#define RATIONAL_ADT 0
#define POINT -128 //����01000000��2
#define EXACT 20 //�������еľ�ȷ�ȣ�Ҳ��ɣ�
struct Rational_Node_ADT {
	char num;
	struct Rational_Node_ADT* left;
	struct Rational_Node_ADT* right;
};
typedef struct Rational_Node_ADT* Rational_Node;
struct Rational_Head_ADT {
	char sign;//��ʾ������
	int base;//��ʾ����
	int left_num;//���ڵ���
	int right_num;//�Ҳ�ڵ���
	struct Rational_Node_ADT* left_end;//���ĩ�˽ڵ�
	struct Rational_Node_ADT* right_end;//�Ҳ�ĩ�˽ڵ�
	struct Rational_Node_ADT* point;//���·���ڽڵ�
};
typedef struct Rational_Head_ADT* Rational;

////////*****�Խڵ�Ĳ���
/*����һ��Rational�ڵ�
* ��ʼ������ָ��Node������
* �������������һ��ֵΪnum��Rational�ڵ㣬��ַ����Node��
*/
int Create_Rational_Node(Rational_Node* Node, int num);
/*��ʼ���ṹ
* ��ʼ����������Rational �ͱ���Q
* ���������Qָ���ʼ�ṹ������ͷ����ڽڵ�,ȷ������B��
*/
int init_Rational(Rational* Q, int B);
/*�Խṹ�ָ�����ʼ���ṹ
* ��ʼ������Q�Ѿ���ʼ����������
* ���������Qָ���ʼ���ṹ��
*/
int ReInit_Rational(Rational Q, int B);
/*���ƽṹ
* ��ʼ������Q1��Q2���ѳ�ʼ��
* �����������Q1���Ƶ�Q2.
*/
int Copy_Rational(Rational Q1, Rational Q2);
/*���ٽṹ
* ��ʼ������Rational����Q�ѳ�ʼ��
* ���������Q��ָ��Ľṹ�ռ䱻�ͷţ�Q=NULL
*/
int Free_Rational(Rational* Q);
/*������������
* ��ʼ������Rational�ͱ���Q�ѳ�ʼ��
* �������������ڽڵ�������һ���ڵ㣬ֵΪnum��
*/
int Add_Left_LtoR(Rational Q, char num);
/*�����ҵ�������
* ��ʼ������Rational�ͱ���Q�ѳ�ʼ��
* ��������������ڵ�ĩ���Ҳ����һ���ڵ㣬ֵΪnum��
*/
int Add_Left_RtoL(Rational Q, char num);
/*�Ҳ����������
* ��ʼ������Rational�ͱ���Q�ѳ�ʼ��
* ������������Ҳ�ĩ�˽ڵ��Ҳ����һ���ڵ㣬ֵΪnum��
*/
int Add_Right_LtoR(Rational Q, char num);
/*���������Ч��ֵΪ0�Ľڵ㣬���������
* ��ʼ������Rational�ͱ���Q��������
* ���������Q�������ҵ�һ������ڵ�ǰ��������ڵ㱻ɾ��
*/
int Clear_after_Sub(Rational Q);
////////******��ͷ�ڵ�Ĳ���
/*�����ƶ�ͷ�ڵ㼰��ڽڵ�
* ��ʼ������Q�ѳ�ʼ�������ٲ���һ���ڵ�
* �����������ڽڵ���뵽����num���ڵ���࣬
* ��num�������ڵ������Զ����ֵΪ0�Ľڵ㡣
*/
int Move_Head_Left(Rational Q, int num);
/*�����ƶ�ͷ�ڵ㼰��ڽڵ�
* ��ʼ������Q�ѳ�ʼ�������ٲ���һ���ڵ�
* �����������ڽڵ���뵽�Ҳ��num���ڵ��Ҳ࣬
* ��num�����Ҳ�ڵ������Զ����ֵΪ0�Ľڵ㡣
*/
int Move_Head_Right(Rational Q, int num);
///////********��������
/*��������Rational�������
* ��ʼ������Q1��Q2�Ҳ��޽ڵ㣬���������һ�ڵ㣬C�ѳ�ʼ��
* ���������Q1��Q2��ӣ�����洢��C��
*/
int Add_Int_Rational(Rational Q1, Rational Q2, Rational C);
/*��������Rational�������
* ��ʼ������Q1>=Q2,�����Ҳ���޽ڵ㣬����������һ�ڵ㣬��Ϊ������C�ѳ�ʼ��
* ���������Q1-Q2������洢��C��
*/
int Sub_Int_Rational(Rational Q1, Rational Q2, Rational C);
/*����Rational��������num
* ��ʼ������Q�Ҳ��޽ڵ㣬�������һ�ڵ㣬C�ѳ�ʼ��
* ���������Q*num������洢��C��
*/
int Mul_Int_Rational(Rational Q, char num, Rational C);
/////////********���������������
/*����������Rational�������
* ��ʼ������C�ѳ�ʼ��
* ���������Q1+Q2������洢��C��
*/
int Add_Rational(Rational Q1, Rational Q2, Rational C);
/*����������Rational�������
* ��ʼ������C�ѳ�ʼ��
* ���������Q1-Q2������洢��C��
*/
int Sub_Rational(Rational Q1, Rational Q2, Rational C);
/*����������Rational�������
* ��ʼ������C�ѳ�ʼ��
* ���������Q1*Q2������洢��C��
*/
int Mul_Rational(Rational Q1, Rational Q2, Rational C);
/////////***********���ֱȽϴ�С
/*�ж�Rational�ͱ���Q�Ƿ�Ϊ0
* ��ʼ������Q�ѳ�ʼ��
* �����������QΪ0������1�����򷵻�0��
*/
int Is_Zero_Rational(Rational Q);
/*�ȽϾ���ֵ��С �Ƿ�|a|<|b|
* ��ʼ������a��b���������������һ���ڵ�
* �����������|a|<|b|������1�����򷵻�0��
*/
int Unsigned_lt_Rational(Rational a, Rational b);
/*�ȽϾ���ֵ��С �Ƿ�|a|>|b|
* ��ʼ������a��b���������������һ���ڵ�
* �����������|a|>|b|������1�����򷵻�0��
*/
int Unsigned_gt_Rational(Rational a, Rational b);
/*�ȽϾ���ֵ�Ƿ���� �Ƿ�|a|=|b|
* ��ʼ������a��b���������������һ���ڵ�
* �����������|a|=|b|������1�����򷵻�0��
*/
int Unsigned_eq_Rational(Rational a, Rational b);
/*�ȽϾ���ֵ��С �Ƿ�|a|<=|b|
* ��ʼ������a��b���������������һ���ڵ�
* �����������|a|<=|b|������1�����򷵻�0��
*/
int Unsigned_le_Rational(Rational a, Rational b);
/*�ȽϾ���ֵ��С �Ƿ�|a|>=|b|
* ��ʼ������a��b���������������һ���ڵ�
* �����������|a|>=|b|������1�����򷵻�0��
*/
int Unsigned_ge_Rational(Rational a, Rational b);
/*�Ƚ���������С �Ƿ�a<b
* ��ʼ������a��b���������������һ���ڵ�
* �����������a<b������1�����򷵻�0��
*/
int lt_Rational(Rational a, Rational b);
/*�Ƚ���������С �Ƿ�a>b
* ��ʼ������a��b���������������һ���ڵ�
* �����������a>b������1�����򷵻�0��
*/
int gt_Rational(Rational a, Rational b);
/*�Ƚ���������С �Ƿ�a=b
* ��ʼ������a��b���������������һ���ڵ�
* �����������a=b������1�����򷵻�0��
*/
int eq_Rational(Rational a, Rational b);
/*�Ƚ���������С �Ƿ�a<=b
* ��ʼ������a��b���������������һ���ڵ�
* �����������a<=b������1�����򷵻�0��
*/
int le_Rational(Rational a, Rational b);
/*�Ƚ���������С �Ƿ�a>=b
* ��ʼ������a��b���������������һ���ڵ�
* �����������a>=b������1�����򷵻�0��
*/
int ge_Rational(Rational a, Rational b);
////////////**************��ȡ����
/*��ȡ�����Լ�С�������벢����
* ��ʼ��������
* ������������������һ���ַ������֣�0~end����С���㣬�ͻس�
* С���㷵��POINT������Ƿ��ַ�����-1
*/
char Get_Num(int end);
/*��ȡ���֣���ĸ��С�������벢����
* ��ʼ������end Ϊĳ����ĸ
* ������������������һ���ַ������֣��Լ�A��end����ĸ���ͻس�
* С���㷵��POINT����ĸ������Ӧ�Ĵ�д,�Ƿ����뷵��-1
*/
char Get_Num_Alpha(int end);
/*��ĸת��ؽ��Ƶ�����
* ��ʼ������chΪ��д��ĸ
* �������������ch����ĸ���Ӧ�����֣���A������10
*/
char Alpha_Turn_Num(int ch);
/*����ת��ؽ��Ƶ���ĸ
* ��ʼ����:num Ϊ���ڵ���0С��36�ķǸ���
* ���������������Ӧ����ĸ�����ֵ�ASCII��
*/
char Num_Turn_Alpha(int num);
//////////////***********���������
/*����һ��������
* ��ʼ������Q��������δ��ʼ����Base�ڣ�2~36���䣬
* ��������Ϊ�޷��ŵ�������
* ���������Qָ����������������޷��ţ�������ʧ�ܻ᷵��-1��
* ���򷵻�1
*/
int Input_Rational(Rational* Q, int Base);
/*���һ��������
* ��ʼ������QΪ�����������
* �������������Ļ�ϴ�ӡ�����ݣ���������
*/
int Output_Rational(Rational Q);
////////////////***********�汾����1.0
/*��������Rational�������
* ��ʼ������Q1��Q2�Ҳ��޽ڵ㣬���������һ�ڵ㣬C�ѳ�ʼ����
* ��Q1>Q2,���߾�Ϊ����
* ���������Q1/Q2���̴洢��C������r�洢��Q1��
*/
int Div_Int_Rational(Rational Q1, Rational Q2, Rational C);
/*����������Rational�ͱ������
* ��ʼ������Q2��Ϊ0��C�ѳ�ʼ��
* ���������Q1/Q2������洢��C��
*/
int Div_Rational(Rational Q1, Rational Q2, Rational C);











#endif
