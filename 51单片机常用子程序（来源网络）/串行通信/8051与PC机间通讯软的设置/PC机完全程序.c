
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<io.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
void sport(char ch)
    {while(!(bioscom(3,0,0)&0x2000));
     if(bioscom(1,ch,0)&0x800)
       {printf("��ʱ����\n");
	 exit(1);
	 }
	 }
rport()
  {int a;
    while(!(bioscom(3,0,0)&0x0100))
       {if(kbhit())
	   {getch();
	     exit(1);
	     }
 a=bioscom(2,0,0)&0x00f;
 return(a);
 }
 }

void sendf(char *fname)
     {FILE *fp;
      char ch;
      int handle,count,sum=0;
      if((fp=fopen(fname,"r"))==NULL)
         {printf("���ܴ������ļ�!\n");
          exit(1);
          }
      handle=fileno(fp);
      count=filelength(handle);
     printf("׼�������ļ�...\n");
      do
         {ch='?';
            sport(ch);
            }while(rport()!='.');
      sport(count);
      rep:
        for(;count;count--)
          {ch=getc(fp);
           sum=sum+ch;
           if(ferror(fp))
             {printf("���ļ�����\n");
              break;
	      }
       sport(ch);
       }
       sport(sum);
       if(rport()=='F')
	  {count=filelength(handle);                         /*filelenth(handle); */
           sum=0;
           fseek(fp,-count,1);
           goto rep;
           }
       else
           {fclose(fp);
            printf("�����ļ�����\n");
            }
            }

  void receivef(char *fname)
     {FILE *fp;
      char ch;
      int count,temp,sum=0;
      remove(fname);
      if((fp=fopen(fname,"w"))==NULL)
         {printf("���ܴ��ļ�\n");
         exit(1);

         }
    printf("�����ļ���:%s\n",fname);
    while(rport()!='?');
    sport('$');
    ch='.';
    sport(ch);
    temp=rport();
    count=temp;
  rep:
      for(;count;count--)
        {ch=rport();
         putc(ch,fp);
         sum=sum+ch;
      if(ferror(fp))
        {printf("д�ļ�����\n");
        exit(1);
        }
        }
   if(rport()!=sum)
      {ch='F';
      sport(ch);
      count=temp;
      sum=0;
      fseek(fp,-count,1);
      goto rep;
      }
   else
        {ch='0';
         sport(ch);
          fclose(fp);
          printf("�����ļ�����\n");
          }
          }


 main(int argc,char *argv[])
  {while(argc!=3)
    {printf("�����������,again!\n");
    exit(1);
    }
    bioscom(0,0x83,0);
    if(tolower(*argv[1])=='s')
      sendf(argv[2]);
	else if (tolower(*argv[1])=='r');
           receivef(argv[2]);




           }

