/******************************************************************************
 * 文件名：base_fun.h
 * 功能：  
******************************************************************************/

#include "dip_header/base_fun.h"



/******************************************************************************
  * 功能：指定输入的小数点后面的位数
  * 参数：number    输入的浮点数
  *       n			保留的位数
  * 返回：转换后的指定位数的浮点数
******************************************************************************/
//double my_round(double number, int n)
//{
//	char str[10];
//	double result;
//	//宽度任意,小数点后面位数为*(由后面的参数n决定)
//	sprintf(str, "%.*f", n, number); //设置format,然后将整形数转换为字符串
//	//sprintf(str, "%*.*f", width, bits, number);
//	result = atof(str);				//字符串转换为浮点数
//	return result;
//}

/******************************************************************************
  * 功能：对一维数组排序,unsigned char, unsigned int
  * 参数：value     输入数组指针
  *       length	输入数组的长度
  * 返回：返回数组的中值
  * 说明: 注意目前只支持unsigned char, unsigned int
******************************************************************************/
//void my_sort(void *val, unsigned int length)
//{
//	unsigned int *value = (unsigned int *)val;
//	unsigned int i, j;
//	unsigned int k;
//	unsigned char temp;
//
//#if 0
//	//用冒泡法对数组进行排序
//	//思路:
//	//		将相邻的两个数比较,将小的调到前头.
//	//		如果有n个数,第一轮要比较(n-1)次,
//	//		则第j轮则要进行(n-1-j)次比较
//	//		共要比较(n-1)轮,第j轮要比较(n-1-j)次
//
//	for (j = 0; j < length - 1; j++) {			//共进行(n-1)轮比较
//		for (i = 0; i < length - 1 - j; i++) {	//第j轮要进行(n-1-j)次比较
//			if (value[i] > value[i+1]) {		//如果前面的数大于后面的数
//												//交换两个数的位置,
//												//使小数上浮,最大数沉底
//				temp = value[i];
//				value[i] = value[i+1];
//				value[i+1] = temp;
//
//			}
//		}
//	}
//#endif
//
//#if 1
//	//用选择法对数组进行排序
//	//思路:
//	//		将n个数中最小的数与第1个数(a[0])对换
//	//		在将剩下的(n-1)个数中最小的数与第2个数(a[1])对换...
//	//		每比较一轮,找出一个未经排序的数中最小的一个
//	//		共比较(n-1)轮,第j轮要比较(n-1-j)次
//	for (j = 0; j < length -1; j++) {			//共进行(n-1)轮比较
//		k = j;									//第j轮要交换的位置编号为j
//		for (i = j+1; i < length; i++) {		//第j轮要进行(n-1-j)次比较
//			if (value[i] < value[k])			//
//				k = i;							//记录未经排序的数中最小值编号k
//		}
//		temp = value[k];						//交换
//		value[k] = value[j];
//		value[j] = temp;						//位置j获得最小值
//	}
//#endif
//}

/******************************************************************************
  * 功能：对一维数组排序,double型
  * 参数：value     输入数组指针
  *       length	输入数组的长度
  * 返回：返回数组的中值
  * 说明: 注意目前只支持unsigned char, unsigned int
******************************************************************************/
//void my_sort_d(void *val, unsigned int length)
//{
//	double *value = (double *)val;
//	unsigned int i, j;
//	unsigned int k;
//	double temp;
//
//#if 0
//
//#endif
//
//#if 1
//	//用选择法对数组进行排序
//	//思路:
//	//		将n个数中最小的数与第1个数(a[0])对换
//	//		在将剩下的(n-1)个数中最小的数与第2个数(a[1])对换...
//	//		每比较一轮,找出一个未经排序的数中最小的一个
//	//		共比较(n-1)轮,第j轮要比较(n-1-j)次
//	for (j = 0; j < length -1; j++) {			//共进行(n-1)轮比较
//		k = j;									//第j轮要交换的位置编号为j
//		for (i = j+1; i < length; i++) {		//第j轮要进行(n-1-j)次比较
//			if (value[i] < value[k])			//
//				k = i;							//记录未经排序的数中最小值编号k
//		}
//		temp = value[k];						//交换
//		value[k] = value[j];
//		value[j] = temp;						//位置j获得最小值
//	}
//#endif
//}

/******************************************************************************
  * 功能：对一维数组排序,并返回数组的中值(unsigned char型数组)
  * 参数：value     输入数组指针
  *       length	输入数组的长度
  * 返回：返回数组的中值
  * 说明: 注意目前只支持字节
******************************************************************************/
//unsigned char get_median_num(unsigned char *value, unsigned int length)
//{
//	//unsigned int i, j;
//	//unsigned int k;
//	unsigned char temp;
//
////#if 0
//
////#endif
////
////#if 1
////	//用选择法对数组进行排序
////	//思路:
////	//		将n个数中最小的数与第1个数(a[0])对换
////	//		在将剩下的(n-1)个数中最小的数与第2个数(a[1])对换...
////	//		每比较一轮,找出一个未经排序的数中最小的一个
////	//		共比较(n-1)轮,第j轮要比较(n-1-j)次
////	for (j = 0; j < length -1; j++) {			//共进行(n-1)轮比较
////		k = j;									//第j轮要交换的位置编号为j
////		for (i = j+1; i < length; i++) {		//第j轮要进行(n-1-j)次比较
////			if (value[i] < value[k])			//
////				k = i;							//记录未经排序的数中最小值编号k
////		}
////		temp = value[k];						//交换
////		value[k] = value[j];
////		value[j] = temp;						//位置j获得最小值
////	}
////#endif
//
//	my_sort(value, length);
//
//	//printf("%s", value);
//	//计算中值
//	if ((length & 0x01) == 1) //数组个数为奇数
//		temp = value[length >> 1];
//	else					  //数组个数为偶数
//		temp = (value[(length >> 1) - 1] + value[length >> 1]) >> 1;
//	return temp;
//}

/******************************************************************************
  * 功能：对一维数组排序,并返回数组的中值(double型数组)
  * 参数：value     输入数组指针
  *       length	输入数组的长度
  * 返回：返回数组的中值
  * 说明: 
******************************************************************************/
//double get_median_num_d(double *value, unsigned int length)
//{
//	//unsigned int i, j;
//	//unsigned int k;
//	double temp;
//
//
////
////#if 1
////	//用选择法对数组进行排序
////	//思路:
////	//		将n个数中最小的数与第1个数(a[0])对换
////	//		在将剩下的(n-1)个数中最小的数与第2个数(a[1])对换...
////	//		每比较一轮,找出一个未经排序的数中最小的一个
////	//		共比较(n-1)轮,第j轮要比较(n-1-j)次
////	for (j = 0; j < length -1; j++) {			//共进行(n-1)轮比较
////		k = j;									//第j轮要交换的位置编号为j
////		for (i = j+1; i < length; i++) {		//第j轮要进行(n-1-j)次比较
////			if (value[i] < value[k])			//
////				k = i;							//记录未经排序的数中最小值编号k
////		}
////		temp = value[k];						//交换
////		value[k] = value[j];
////		value[j] = temp;						//位置j获得最小值
////	}
////#endif
//	my_sort_d(value, length);
//
//	//printf("%s", value);
//	//计算中值
//	if ((length & 0x01) == 1) //数组个数为奇数
//		temp = value[length/2];
//	else					  //数组个数为偶数
//		temp = (value[(length/2) - 1] + value[length/2]) /2 ;
//	return temp;
//}

/******************************************************************************
  * 功能：对一维数组排序,并返回排序后第pos个值(double型数组)
  * 参数：value     输入数组指针
  *       length	输入数组的长度
  *		  pos		排序后pos位置(0~length-1)
  * 返回：返回数组的中值
  * 说明: 
******************************************************************************/
//double get_array_num_d(double *value, unsigned int length, unsigned int pos)
//{
//	//unsigned int i, j;
//	//unsigned int k;
//	double temp;
//
//
////#if 1
////	//用选择法对数组进行排序
////	//思路:
////	//		将n个数中最小的数与第1个数(a[0])对换
////	//		在将剩下的(n-1)个数中最小的数与第2个数(a[1])对换...
////	//		每比较一轮,找出一个未经排序的数中最小的一个
////	//		共比较(n-1)轮,第j轮要比较(n-1-j)次
////	for (j = 0; j < length -1; j++) {			//共进行(n-1)轮比较
////		k = j;									//第j轮要交换的位置编号为j
////		for (i = j+1; i < length; i++) {		//第j轮要进行(n-1-j)次比较
////			if (value[i] < value[k])			//
////				k = i;							//记录未经排序的数中最小值编号k
////		}
////		temp = value[k];						//交换
////		value[k] = value[j];
////		value[j] = temp;						//位置j获得最小值
////	}
////#endif
//	my_sort_d(value, length);
//
//	//printf("%s", value);
//	//计算中值
//	if (pos >= length)
//		pos = length - 1;
//	if (pos <= 0)
//		pos = 0;
//	temp = value[pos];
//	return temp;
//}

//int Compare(const void *elem1, const void *elem2) 
//{ 
//	return *((int *)(elem1)) - *((int *)(elem2));
//} 

//double compare(void *elem1, void *elem2)
//{
//	return *((double*)(elem1)) - *((double*)(elem2));
//}


/******************************************************************************
  * 功能：返回a,b中的最大者(double型数组)
  * 参数：value     输入数组指针
  *       length	输入数组的长度
  *		  pos		排序后pos位置(0~length-1)
  * 返回：
  * 说明: 
******************************************************************************/
//double get_max_d(double a, double b)
//{
//	return (a>b) ? a : b;
//}


/*************************************************************************
  * 功能：生成一维的高斯函数数据
  * 参数：sigma			高斯函数的标准差
  *       gauss_data	指向高斯数据数组的指针,即:归一化后的高斯系数
  *						exp(-0.5*(x-u)^2/sigma^2) /( sqrt(2*PI)*sigma)
  *		  data_len		数据的长度
  * 返回：
  * 说明: 
  *   这个函数可以生成一个一维的高斯函数的数字数据，理论上高斯数据的长度应
  *   该是无限长的，但是为了计算的简单和速度，实际的高斯数据只能是有限长的
  *   data_len就是数据长度
  *	注意: 调用此函数前,要先计算出data_len,并且为gauss_data分配好内存,如
  *		  int gauss_data_len = 2*((int)(3 * sigma) + 1) + 1;	
  *		  double *pGaussData = malloc(sizeof(double)*gauss_data_len);
  *       cal_gauss_filter_data_v1(0.4, gauss_data, gauss_data_len);
  *       ...
  *       free(pGaussData);
  *       ...
 **************************************************************************/
//void calc_gauss_filter_data(double sigma, double *gauss_data, int data_len)
//{
//	// 循环控制变量
//	int i;	
//	// 数组的中心点
//	int center;
//	// 数组的某一点到中心点的距离
//	double x_u; 
//	// 中间变量
//	double value; 
//	double  sum;
//	//int ceil_3sigma;
//	sum = 0 ; 
//	
//	// 数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
//	// 这些数据会覆盖绝大部分的滤波系数
//	//ceil_3sigma = (int)(3 * sigma) + 1;	//使用ceil函数则为:ceil(3*sigma);
//	//*data_len = (int)(1 + 2 * ceil_3sigma);
//	
//	// 中心
//	center = data_len / 2;
//	
//	for(i=0; i< (data_len); i++) {
//		x_u = (double)(i - center);
//		//exp(-0.5*(x-u)^2/sigma^2) /( sqrt(2*PI)*sigma)
//		//value = exp(-(0.5)*x_u*x_u/(sigma*sigma)) / (sqrt(2 * M_PI) * sigma);
//		value = exp(-(1/2)*x_u*x_u/(sigma*sigma)) / (sqrt(2.0 * M_PI) * sigma);
//		gauss_data[i] = value ;
//		sum += value;
//	}
//	
//	// 归一化
//	for(i=0; i<(data_len) ; i++) {
//		gauss_data[i] /= sum;
//	}
//}

/*************************************************************************
  * 功能：生成一维的高斯函数数据
  * 参数：sigma			高斯函数的标准差
  *       gauss_data	指向高斯数据数组的指针,即:归一化后的高斯系数
  *						exp(-0.5*(x-u)^2/sigma^2) /( sqrt(2*PI)*sigma)
  *		  data_len		数据的长度
  * 返回：
  * 说明: 
  *   这个函数可以生成一个一维的高斯函数的数字数据，理论上高斯数据的长度应
  *   该是无限长的，但是为了计算的简单和速度，实际的高斯数据只能是有限长的
  *   data_len就是数据长度
  *	注意: 调用此函数前,要先计算出data_len,并且为gauss_data是一个指向数组的
  *		  指针(即指针的指针),在使用完之后,要记得释放,如
  *		  double *pGaussData;
  *		  int gauss_data_len;
  *       cal_gauss_filter_data_v1(0.4, &gauss_data, &gauss_data_len);
  *       ...
  *       free(pGaussData);
  *       ...
 **************************************************************************/
//void calc_gauss_filter_data_v1(double sigma, double **gauss_data, int *data_len)
//{
//	// 循环控制变量
//	int i;
//	// 数组的中心点
//	int center;
//	// 数组的某一点到中心点的距离
//	double x_u; 
//	// 中间变量
//	double value; 
//	double sum;
//	int ceil_3sigma;
//	sum = 0; 
//	
//	// 数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
//	// 这些数据会覆盖绝大部分的滤波系数
//	ceil_3sigma = (int)(3 * sigma) + 1;	//使用ceil函数则为:ceil(3*sigma);
//	*data_len = (int)(1 + 2 * ceil_3sigma);
//	//*data_len = (int)(1 + 2 * ceil(3 * sigma));
//	
//	// 中心
//	center = (*data_len) / 2;
//	
//	// 分配内存
//	//*gauss_data = new double[*data_len] ;
//	*gauss_data = (double *)malloc(sizeof(double)*(*data_len));
//	
//	for(i=0; i< (*data_len); i++)
//	{
//		x_u = (double)(i - center);
//		//exp(-0.5*(x-u)^2/sigma^2) /( sqrt(2*PI)*sigma)
//		//value = exp(-(0.5)*x_u*x_u/(sigma*sigma)) / (sqrt(2 * M_PI) * sigma);
//		value = exp(-(1/2)*x_u*x_u/(sigma*sigma)) / (sqrt(2.0 * M_PI) * sigma);
//		(*gauss_data)[i] = value ;
//		sum += value;
//	}
//	
//	// 归一化
//	for(i=0; i<(*data_len) ; i++)
//	{
//		(*gauss_data)[i] /= sum;
//	}
//}

int sin_10000[91] = 
{
	0,     //0
	175,   //1
	349,   //2
	523,   //3
	698,   //4
	872,   //5
	1045,  //6
	1219,  //7
	1392,  //8
	1564,  //9
	1736,  //10
	1908,  //11
	2079,  //12
	2250,  //13
	2419,  //14
	2588,  //15
	2756,  //16
	2924,  //17
	3090,  //18
	3256,  //19
	3420,  //20
	3584,  //21
	3746,  //22
	3907,  //23
	4067,  //24
	4226,  //25
	4384,  //26
	4540,  //27
	4695,  //28
	4848,  //29
	5000,  //30
	5150,  //31
	5299,  //32
	5446,  //33
	5592,  //34
	5736,  //35
	5878,  //36
	6018,  //37
	6157,  //38
	6293,  //39
	6428,  //40
	6561,  //41
	6691,  //42
	6820,  //43
	6947,  //44
	7071,  //45
	7193,  //46
	7314,  //47
	7431,  //48
	7547,  //49
	7660,  //50
	7771,  //51
	7880,  //52
	7986,  //53
	8090,  //54
	8192,  //55
	8290,  //56
	8387,  //57
	8480,  //58
	8572,  //59
	8660,  //60
	8746,  //61
	8829,  //62
	8910,  //63
	8988,  //64
	9063,  //65
	9135,  //66
	9205,  //67
	9272,  //68
	9336,  //69
	9397,  //70
	9455,  //71
	9511,  //72
	9563,  //73
	9613,  //74
	9659,  //75
	9703,  //76
	9744,  //77
	9781,  //78
	9816,  //79
	9848,  //80
	9877,  //81
	9903,  //82
	9925,  //83
	9945,  //84
	9962,  //85
	9976,  //86
	9986,  //87
	9994,  //88
	9998,  //89
	10000  //90
};



//int angle ,value;
//value = get_sin_cos(30, 1);
//printf("%d\n", value);
//value = get_sin_cos(150, 1);
//printf("%d\n", value);
//value = get_sin_cos(210, 1);
//printf("%d\n", value);
//value = get_sin_cos(330, 1);
//printf("%d\n", value);
//printf("\ncos\n");
//value = get_sin_cos(60, 0);
//printf("%d\n", value);
//value = get_sin_cos(120, 0);
//printf("%d\n", value);
//value = get_sin_cos(240, 0);
//printf("%d\n", value);
//value = get_sin_cos(300, 0);

//printf("%d\n", value);
int get_sin_cos(int angle, int flag)
{
	if (flag == 1) {
		if (angle <= 90) {
			return sin_10000[angle];
		} else if (angle <= 180) {
			return sin_10000[180-angle];
		} else if (angle <= 270) {
			return -sin_10000[angle-180];
		} else {
			return -sin_10000[360-angle];
		}
	} else {
		if (angle <= 90) {
			return sin_10000[90-angle];
		} else if (angle <= 180) {
			return -sin_10000[angle-90];
		} else if (angle <= 270) {
			return -sin_10000[270-angle];
		} else {
			return sin_10000[angle-270];
		}
	}
}

//
//	GetAngle90In180: 求两个角度的夹角(0 - 90)
//	
/////////////////////////////////////////////////////////////////////////
//	angle1: [in] 角度一(0 - 180)
//	angle2: [in] 角度二(0 - 180)
/////////////////////////////////////////////////////////////////////////
int GetAngle90In180(int angle1, int angle2)
{
	int a;
	a = abs(angle1-angle2);
	if(a > 90) {
		a = 180-a;
	}
	return a;
}

//
//	GetAngle180In360: 求两个角度的夹角(0 - 180)
//
/////////////////////////////////////////////////////////////////////////
//	angle1: [in] 角度一(0 - 360)
//	angle2: [in] 角度二(0 - 360)
/////////////////////////////////////////////////////////////////////////
int GetAngle180In360(int angle1, int angle2)
{
	int a;
	a = abs(angle1 - angle2);
	if(a > 180) {
		return (360 - a);
	} else {
		return a;
	}
}

//
//	GetAngle360In360： 两个角度间的距离(0-360)  (逆时针方向)
//
/////////////////////////////////////////////////////////////////////////
//	angleBegin: [in] 起始角度(0-360)
//	angleEnd: [in] 终结角度(0-360)
/////////////////////////////////////////////////////////////////////////
int GetAngle360In360(int angleBegin, int angleEnd)
{
	int  a;
	a = angleEnd-angleBegin;
	if(a < 0) {
		a += 360;
	}
	return a;
}

//
//	XY2Angle： 两个点连线与x轴方向的角度
//
/////////////////////////////////////////////////////////////////////////
//	x0: [in] 第一个点横坐标
//	y0: [in] 第一个点纵坐标
//	x1: [in] 第二个点横坐标
//	y1: [in] 第二个点纵坐标
/////////////////////////////////////////////////////////////////////////
int XY2Angle(int x0, int y0, int x1, int y1)
{
	double angle;
	angle = atan2((double)(y1-y0), (double)(x1-x0));
	// 弧度转化到0 - 2*M_PI
	if(angle < 0) {
		angle += 2*M_PI;
	}
	// 弧度转化为角度
	return (int)(angle*M_EPI + 0.5);
}

/******************************************************************************
  * 功能：数据拷贝
  * 参数：pDst		数据拷贝目标区域
  *       pSrc		数据拷贝源区域
  *		  size		拷贝大小
  * 返回：
******************************************************************************/
void BufferCopy(unsigned char *pDst, unsigned char *pSrc, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++) {
		*(pDst+i) = *(pSrc+i);
	}
}






