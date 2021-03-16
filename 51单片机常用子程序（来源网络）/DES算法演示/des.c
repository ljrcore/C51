/*********************************************************************/
/*-文件名：des.c													 */
/*-																	 */
/*-功能： 实现DES加密算法的加密解密功能     						 */
/*-																	 */
/*-说明：des算法的实现代码											 */
/*-		能够实现56位或56*n密钥的des算法，可以通过该程序提供的接口    */
/*-		进行数据的加密，保证数据在传送过程的安全性					 */
/*-																	 */
/*-																	 */
/*-该程序的所有权利由作者保留    						             */
/*-																     */
/*-																     */
/*-版本号：1.0.0(2002.4)											 */
/*-																	 */
/*-																	 */
/*-AUTHOR:吴真(WUZHEN)												 */
/*-																	 */
/*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include "des.h"

#define SUCCESS 0 
#define FAIL -1

#define READFILESIZE 512

#define WZ_COMMEND_NUM 4
#define WZUSEHELPNUM 19
#define DESONE 1
#define DESTHREE 2
#define DESMULTI 3
INT8 *WZ_Commend_Help[] =
{
	
	"基于DES的加密解密工具v1.0	 ",/*0*/	
	"追求卓越,勇于创新		 ",	
	"----著者 :  吴真---		 ",
	"			  	 "	
};

INT8 *WZ_USE_HELP[]={
	"输入5+n个参数:",
	"\t1.可执行文件名 *.exe",
	"\t2.操作类型 1:一层加密;2:一层解密;",
	"\t\t13:N层单密钥加密;23:N层单密钥解密;",
	"\t\t39:N层多密钥加密;49:N层多密钥解密",
	"\t3.读出数据的文件名*.txt",
	"\t4.写入数据的文件名*.txt",	
	"\t5.密钥(8字节例如:wuzhen12)",	
	"\t[6].N层单密钥的层数或者...二层加密|解密密钥",	
	"\t[7].三层加密|解密密钥",
	"\t[8]. ...",
	"\t[N].N层加密|解密密钥",
	"\t 例1: des 1 1.txt 2.txt 12345678",
	"\t    : des 2 2.txt 3.txt 12345678",
	"\t 例2: des 13 1.txt 2.txt tiantian 5",
	"\t    : des 23 2.txt 3.txt tiantian 5",
	"\t 例3: des 39 1.txt 2.txt 12345678 tiantian gaoxinma",
	"\t    : des 49 2.txt 3.txt 12345678 tiantian gaoxinma",
	"******************************"
};



INT32 hextofile( ULONG8 *buf ,FILE *writefile, ULONG32 length);/*以16进制写入文件*/
INT32 encodehex(ULONG8 *tobuf,ULONG8 *frombuf,ULONG32 len);/*16进制解码*/

INT32 file_enc(FILE *readfile,FILE *writefile,
			   ULONG8 *key,ULONG32 keynum,
			   ULONG8 **superkey,ULONG32 n_superkey,
			   ULONG8 flag);
INT32 file_dec(FILE *readfile,FILE *writefile,
			   ULONG8 *key,ULONG32 keynum,
			   ULONG8 **superkey,ULONG32 n_superkey,
			   ULONG8 flag);
void wz_print_help();


INT32 main(INT32 argc,INT8 *argv[])
{
	INT8 *FILENAME1,*FILENAME2;    
	FILE *fp, *fp2;	
	ULONG8 *key ;
	ULONG8 **superkey ;/*n层加密解密密钥*/
	ULONG8 n_superkey ;
	ULONG32 num;		    
	
	
	if ( argc >= 5 && (atoi(argv[1]) == 39 || atoi(argv[1]) == 49 ) )
	{
		n_superkey = argc - 4 ;
		superkey = ( INT8 **)calloc(1, n_superkey*sizeof( void *) ) ;
		for ( num = 0 ; num < n_superkey ; num++)
		{
			superkey[num] = argv[4+num] ;
		}

	}
	else if ( argc == 6 && (atoi(argv[1]) == 13 || atoi(argv[1]) == 23 ) && (atoi(argv[5])) > 0)
	{

	}
	else if ( argc == 5 && ( atoi(argv[1]) == 1 || atoi(argv[1]) == 2 ))
	{

	}
	else
	{
		wz_print_help();
		return FAIL;	
	}
	FILENAME1 = argv[2];
	FILENAME2 = argv[3];
	if ((fp= fopen(FILENAME1,"rb")) == NULL	|| (fp2 = fopen(FILENAME2,"wb"))==NULL)
	{		
		
		printf("Can't open file\n");
		return FAIL;
	}  

    key = argv[4] ;		
	switch( atoi(argv[1] ))
	{
	case 1:	/*加密*/
		file_enc(fp,fp2,key,0, NULL,0, DESONE);				
		printf("\n \tDES 一层加密完毕,密文存于%s文件\n",FILENAME2);
		break;
	case 2:
		file_dec(fp,fp2,key,0, NULL, 0,DESONE);				
		printf("\n \tDES 一层解密完毕,密文存于%s文件\n",FILENAME2);
		break;
	case 13:
		file_enc(fp,fp2,key,atoi(argv[5]),NULL,0,DESTHREE);				
		printf("\n \tDES %u层单密钥加密完毕,密文存于%s文件\n",atoi(argv[5]),FILENAME2);
		break;
	case 23:
		file_dec(fp,fp2,key,atoi(argv[5]),NULL,0,DESTHREE);				
		printf("\n \tDES %u层单密钥解密完毕,密文存于%s文件\n",atoi(argv[5]),FILENAME2);
		break;
	case 39:
		file_enc(fp,fp2,NULL,0,superkey,n_superkey,DESMULTI);				
		printf("\n \tDES 多密钥加密完毕,密文存于%s文件\n",FILENAME2);
		free(superkey);
		superkey = NULL;
		break;
	case 49:
		file_dec(fp,fp2,NULL,0,superkey,n_superkey,DESMULTI);
		printf("\n \tDES 多密钥加密完毕,密文存于%s文件\n",FILENAME2);
		free(superkey);
		superkey = NULL;
		break;
	default:
			printf("请选择是加密|解密 plese choose encrypt|deencrypt\n");		
		break;
	}

	fclose(fp);
	fclose(fp2);
	return SUCCESS;

}

void wz_print_help()
{
	INT32 i ;
	printf("\t");
	for (  i = 0 ; i < 22 ; i++)
	{
		printf("%c ",5);
	}
	printf("\n");
	for( i = 0 ; i < WZ_COMMEND_NUM ; i++)
	{
		printf("\t%c\t%s %c\n",5,WZ_Commend_Help[i],5);	
	}
	printf("\t");
	for (  i = 0 ; i < 22 ; i++)
	{
		printf("%c ",5);
	}	
	printf("\n");
	for( i = 0 ; i < WZUSEHELPNUM ; i++)
	{
		printf("\t%s\n",WZ_USE_HELP[i]);
	}
	return ;
}

INT32 file_enc(FILE *readfile,FILE *writefile,
			   ULONG8 *key,ULONG32 keynum,
			   ULONG8 **superkey,ULONG32 n_superkey,
			   ULONG8 flag)
{
	INT32 filelen = 0,readlen = 0,writelen = 0;
	ULONG32 totalfilelen = 0 ;/*统计实际的文件的长度*/	
	ULONG8 readbuf[READFILESIZE] = { 0 };		
	filelen = fread( readbuf, sizeof( INT8 ), READFILESIZE, readfile );
	while( filelen == READFILESIZE )
	{	
		totalfilelen += READFILESIZE;
		switch(flag)
		{
		case DESONE:
			des( readbuf,key,READFILESIZE);		
			break;
		case DESTHREE:
			des3( readbuf, key ,keynum,READFILESIZE);
			break;
		case DESMULTI:
			desN( readbuf, superkey ,n_superkey,READFILESIZE);
			break;
		}		
		hextofile( readbuf, writefile, READFILESIZE );/*以16进制形式写入文件*/
		memset(readbuf,0,READFILESIZE);	
		filelen = fread( readbuf, sizeof( INT8 ), READFILESIZE, readfile );
	}	
	/*这是从文件中读出的最后一批数据,长度可能会等于0,所以要先判断*/

	if ( filelen > 0 )
	{
		/*如果从文件中读出的长度不等于0,那么肯定有8个字节以上的空间
		文件长度存在最后8个字节中*/
		totalfilelen += filelen;
		memcpy( &readbuf[READFILESIZE-8], (ULONG8*)&totalfilelen,4);	
		switch(flag)
		{
		case DESONE:
			des( readbuf,key,READFILESIZE);		
			break;
		case DESTHREE:
			des3( readbuf, key ,keynum,READFILESIZE);
			break;
		case DESMULTI:
			desN( readbuf, superkey ,n_superkey,READFILESIZE);
			break;
		}
		hextofile( readbuf, writefile,READFILESIZE );/*以16进制形式写入文件*/		
		memset(readbuf,0 ,READFILESIZE);
	}
	else /*filelen == 0*/
	{
		memcpy( &readbuf[0], (ULONG8*)&totalfilelen,4);			
		switch(flag)
		{
		case DESONE:
			des( readbuf,key,8);		
			break;
		case DESTHREE:
			des3( readbuf, key ,keynum,8);
			break;
		case DESMULTI:
			desN( readbuf, superkey ,n_superkey,8);
			break;
		}
		hextofile( readbuf, writefile, 8);/*以16进制形式写入文件*/		
	}
	return SUCCESS;
}



INT32 file_dec(FILE *readfile,FILE *writefile,
			   ULONG8 *key,ULONG32 keynum,
			   ULONG8 **superkey,ULONG32 n_superkey,
			   ULONG8 flag)
{
	INT32 filelen = 0,readlen = 0,writelen = 0;
	ULONG32 totalfilelen = 0 ;/*统计实际的文件的长度*/
	INT32 num = 0;
	ULONG8 readbuf[READFILESIZE] = { 0 };
	ULONG8 sendbuf[READFILESIZE*2] = { 0 };	
	
	fseek(readfile,-16,SEEK_END);/*最后16个字节的表示文件长度的空间*/			
	filelen = fread( sendbuf, sizeof( INT8 ), 16, readfile );	
	encodehex( readbuf,sendbuf,8);	
		switch(flag)
		{
		case DESONE:
			Ddes( readbuf,key,8);		
			break;
		case DESTHREE:
			Ddes3( readbuf, key ,keynum,8);
			break;
		case DESMULTI:
			DdesN( readbuf, superkey ,n_superkey,8);
			break;
		}
/*解密*/
	memcpy((ULONG8*)&totalfilelen, &readbuf[0],4);/*得到文件总长*/
	memset(readbuf,0 ,8);
	memset(sendbuf,0 ,16);			
    
	num = totalfilelen/READFILESIZE;/*有几个READFILESIZE组*/
	totalfilelen %= READFILESIZE;

	fseek(readfile,0,SEEK_SET);/*跳到文件头*/	
	while(num--)
	{	
		filelen = fread( sendbuf, sizeof( INT8 ), READFILESIZE*2, readfile );			
		encodehex( readbuf,sendbuf,READFILESIZE);
				switch(flag)
		{
		case DESONE:
			Ddes( readbuf,key,READFILESIZE);		
			break;
		case DESTHREE:
			Ddes3( readbuf, key ,keynum,READFILESIZE);
			break;
		case DESMULTI:
			DdesN( readbuf, superkey ,n_superkey,READFILESIZE);
			break;
		}

		writelen = fwrite(readbuf, sizeof( INT8 ), READFILESIZE, writefile);				  		
		memset(readbuf,0 ,READFILESIZE);
		memset(sendbuf,0 ,READFILESIZE*2);			
	}
	if ( totalfilelen > 0 )/*最后一块有多余的元素*/
	{
		filelen = fread( sendbuf, sizeof( INT8 ), READFILESIZE*2, readfile );	
		encodehex( readbuf,sendbuf,READFILESIZE);
		switch(flag)
		{
		case DESONE:
			Ddes( readbuf,key,READFILESIZE);		
			break;
		case DESTHREE:
			Ddes3( readbuf, key ,keynum,READFILESIZE);
			break;
		case DESMULTI:
			DdesN( readbuf, superkey ,n_superkey,READFILESIZE);
			break;
		}
		writelen = fwrite(readbuf, sizeof( INT8 ), totalfilelen, writefile);	
		memset(readbuf,0 ,READFILESIZE);
		memset(sendbuf,0 ,READFILESIZE*2);						
		
	}	
	return SUCCESS;
}

INT32 hextofile( ULONG8 *buf ,FILE *writefile, ULONG32 length)
{
	ULONG32 writelen = 0 ;
		/*以16进制形式写入文件*/
    while( writelen < length)
	{
		if(buf[writelen] == 0)
		{
			fprintf( writefile, "%x", 0 );
			fprintf( writefile, "%x", 0 );
		}
		else if (buf[writelen] < 0x10)
		{
			fprintf( writefile, "%x", 0 );
			fprintf( writefile, "%x", buf[writelen] );				
		}
		else
		{
			fprintf( writefile, "%x", buf[writelen] );
			
		}			
		writelen++;
		
	}
	return SUCCESS;
}
INT32 encodehex(ULONG8 *tobuf,ULONG8 *frombuf,ULONG32 len)
{
	ULONG8 *readfirst = frombuf ;
	ULONG8 *readend = &frombuf[1] ;	
	INT8 *s;
	ULONG8 y[2] ;		    
	ULONG32 i;
	for ( i = 0 ; i < len ; i++)
	{
		y[0] = *readfirst ;
		y[1] = *readend ;
		readfirst += 2 ;
		readend += 2 ;
		tobuf[i] = (ULONG8)strtol((INT8*)y, &s, 16);			
	}	
	return SUCCESS;
}
