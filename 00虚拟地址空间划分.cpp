//#include <iostream>
//#include <vector>
//using namespace std;
//#if 1
//int main()
//{
//	return 0;
//}
//#endif

#include <iostream>
#include <vector>
using namespace std;

#if 0
int gdata1 = 10;				//	.data	
int gdata2 = 0;					//	.bss
int gdata3;						//	.bss
static int  gdata4 = 11;		//	.data
static int  gdata5 = 0;			//	.bss
static int  gdata6;				//	.bss
int main()						//
{								//
	int a = 12;					//	.stack
	int b = 0;					//	.stack
	int c;						//	.stack
								//
	static int e = 13;			//	.data
	static int f = 0;			//	.bss
	static int g;				//	.bss
								
	return 0;					
}
#endif
