/*********************************************************************/
/*-�ļ�����des.c													 */
/*-																	 */
/*-���ܣ� ʵ��DES�����㷨�ļ��ܽ��ܹ���     						 */
/*-																	 */
/*-˵����des�㷨��ʵ�ִ���											 */
/*-		�ܹ�ʵ��56λ��56*3��Կ��des�㷨������ͨ���ó����ṩ�Ľӿ�    */
/*-		�������ݵļ��ܣ���֤�����ڴ��͹��̵İ�ȫ��					 */
/*-																	 */
/*-																	 */
/*-�ó��������Ȩ�������߱���							             */
/*-																     */
/*-																     */
/*-�汾�ţ�1.0.0(2002.4)											 */
/*-																	 */
/*-																	 */
/*-AUTHOR:����(WUZHEN)												 */
/*-																	 */
/*********************************************************************/

typedef  int INT32;
typedef  char INT8;
typedef  unsigned char  ULONG8;
typedef  unsigned short ULONG16;
typedef  unsigned long  ULONG32;

/*�������c++�������Ļ��������º궨��
	#define DllExport extern "C" __declspec(dllexport)
*/

#define DllExport  __declspec(dllexport)


/*���ܽӿں���*/
DllExport INT32 DdesN(ULONG8 *data, ULONG8 **key, ULONG32 n_key,ULONG32 readlen);
DllExport INT32 desN(ULONG8 *data, ULONG8 **key, ULONG32 n_key,ULONG32 readlen);
DllExport INT32 des3(ULONG8 *data, ULONG8 *key,ULONG32 n ,ULONG32 readlen);
DllExport INT32 Ddes3(ULONG8 *data,ULONG8 *key,ULONG32 n ,ULONG32 readlen);
DllExport INT32 des(ULONG8 *data, ULONG8 *key,INT32 readlen);
DllExport INT32 Ddes(ULONG8 *data,ULONG8 *key,INT32 readlen);