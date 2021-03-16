/*********************************************************************/
/*-�ļ�����des.c													 */
/*-																	 */
/*-���ܣ� ʵ��DES�����㷨�ļ��ܽ��ܹ���     						 */
/*-																	 */
/*-˵����des�㷨��ʵ�ִ���											 */
/*-		�ܹ�ʵ��56λ��56*n��Կ��des�㷨������ͨ���ó����ṩ�Ľӿ�    */
/*-		�������ݵļ��ܣ���֤�����ڴ��͹��̵İ�ȫ��					 */
/*-																	 */
/*-																	 */
/*-�ó��������Ȩ�������߱���    						             */
/*-																     */
/*-																     */
/*-�汾�ţ�1.0.0(2002.4)											 */
/*-																	 */
/*-																	 */
/*-AUTHOR:����(WUZHEN)												 */
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
	
	"����DES�ļ��ܽ��ܹ���v1.0	 ",/*0*/	
	"׷��׿Խ,���ڴ���		 ",	
	"----���� :  ����---		 ",
	"			  	 "	
};

INT8 *WZ_USE_HELP[]={
	"����5+n������:",
	"\t1.��ִ���ļ��� *.exe",
	"\t2.�������� 1:һ�����;2:һ�����;",
	"\t\t13:N�㵥��Կ����;23:N�㵥��Կ����;",
	"\t\t39:N�����Կ����;49:N�����Կ����",
	"\t3.�������ݵ��ļ���*.txt",
	"\t4.д�����ݵ��ļ���*.txt",	
	"\t5.��Կ(8�ֽ�����:wuzhen12)",	
	"\t[6].N�㵥��Կ�Ĳ�������...�������|������Կ",	
	"\t[7].�������|������Կ",
	"\t[8]. ...",
	"\t[N].N�����|������Կ",
	"\t ��1: des 1 1.txt 2.txt 12345678",
	"\t    : des 2 2.txt 3.txt 12345678",
	"\t ��2: des 13 1.txt 2.txt tiantian 5",
	"\t    : des 23 2.txt 3.txt tiantian 5",
	"\t ��3: des 39 1.txt 2.txt 12345678 tiantian gaoxinma",
	"\t    : des 49 2.txt 3.txt 12345678 tiantian gaoxinma",
	"******************************"
};



INT32 hextofile( ULONG8 *buf ,FILE *writefile, ULONG32 length);/*��16����д���ļ�*/
INT32 encodehex(ULONG8 *tobuf,ULONG8 *frombuf,ULONG32 len);/*16���ƽ���*/

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
	ULONG8 **superkey ;/*n����ܽ�����Կ*/
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
	case 1:	/*����*/
		file_enc(fp,fp2,key,0, NULL,0, DESONE);				
		printf("\n \tDES һ��������,���Ĵ���%s�ļ�\n",FILENAME2);
		break;
	case 2:
		file_dec(fp,fp2,key,0, NULL, 0,DESONE);				
		printf("\n \tDES һ��������,���Ĵ���%s�ļ�\n",FILENAME2);
		break;
	case 13:
		file_enc(fp,fp2,key,atoi(argv[5]),NULL,0,DESTHREE);				
		printf("\n \tDES %u�㵥��Կ�������,���Ĵ���%s�ļ�\n",atoi(argv[5]),FILENAME2);
		break;
	case 23:
		file_dec(fp,fp2,key,atoi(argv[5]),NULL,0,DESTHREE);				
		printf("\n \tDES %u�㵥��Կ�������,���Ĵ���%s�ļ�\n",atoi(argv[5]),FILENAME2);
		break;
	case 39:
		file_enc(fp,fp2,NULL,0,superkey,n_superkey,DESMULTI);				
		printf("\n \tDES ����Կ�������,���Ĵ���%s�ļ�\n",FILENAME2);
		free(superkey);
		superkey = NULL;
		break;
	case 49:
		file_dec(fp,fp2,NULL,0,superkey,n_superkey,DESMULTI);
		printf("\n \tDES ����Կ�������,���Ĵ���%s�ļ�\n",FILENAME2);
		free(superkey);
		superkey = NULL;
		break;
	default:
			printf("��ѡ���Ǽ���|���� plese choose encrypt|deencrypt\n");		
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
	ULONG32 totalfilelen = 0 ;/*ͳ��ʵ�ʵ��ļ��ĳ���*/	
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
		hextofile( readbuf, writefile, READFILESIZE );/*��16������ʽд���ļ�*/
		memset(readbuf,0,READFILESIZE);	
		filelen = fread( readbuf, sizeof( INT8 ), READFILESIZE, readfile );
	}	
	/*���Ǵ��ļ��ж��������һ������,���ȿ��ܻ����0,����Ҫ���ж�*/

	if ( filelen > 0 )
	{
		/*������ļ��ж����ĳ��Ȳ�����0,��ô�϶���8���ֽ����ϵĿռ�
		�ļ����ȴ������8���ֽ���*/
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
		hextofile( readbuf, writefile,READFILESIZE );/*��16������ʽд���ļ�*/		
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
		hextofile( readbuf, writefile, 8);/*��16������ʽд���ļ�*/		
	}
	return SUCCESS;
}



INT32 file_dec(FILE *readfile,FILE *writefile,
			   ULONG8 *key,ULONG32 keynum,
			   ULONG8 **superkey,ULONG32 n_superkey,
			   ULONG8 flag)
{
	INT32 filelen = 0,readlen = 0,writelen = 0;
	ULONG32 totalfilelen = 0 ;/*ͳ��ʵ�ʵ��ļ��ĳ���*/
	INT32 num = 0;
	ULONG8 readbuf[READFILESIZE] = { 0 };
	ULONG8 sendbuf[READFILESIZE*2] = { 0 };	
	
	fseek(readfile,-16,SEEK_END);/*���16���ֽڵı�ʾ�ļ����ȵĿռ�*/			
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
/*����*/
	memcpy((ULONG8*)&totalfilelen, &readbuf[0],4);/*�õ��ļ��ܳ�*/
	memset(readbuf,0 ,8);
	memset(sendbuf,0 ,16);			
    
	num = totalfilelen/READFILESIZE;/*�м���READFILESIZE��*/
	totalfilelen %= READFILESIZE;

	fseek(readfile,0,SEEK_SET);/*�����ļ�ͷ*/	
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
	if ( totalfilelen > 0 )/*���һ���ж����Ԫ��*/
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
		/*��16������ʽд���ļ�*/
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
