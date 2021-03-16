
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
       {printf("超时错误！\n");
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
         {printf("不能打开输入文件!\n");
          exit(1);
          }
      handle=fileno(fp);
      count=filelength(handle);
     printf("准备发送文件...\n");
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
             {printf("读文件有误\n");
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
            printf("发送文件结束\n");
            }
            }

  void receivef(char *fname)
     {FILE *fp;
      char ch;
      int count,temp,sum=0;
      remove(fname);
      if((fp=fopen(fname,"w"))==NULL)
         {printf("不能打开文件\n");
         exit(1);

         }
    printf("接收文件名:%s\n",fname);
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
        {printf("写文件有误\n");
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
          printf("接收文件结束\n");
          }
          }


 main(int argc,char *argv[])
  {while(argc!=3)
    {printf("命令行命令不对,again!\n");
    exit(1);
    }
    bioscom(0,0x83,0);
    if(tolower(*argv[1])=='s')
      sendf(argv[2]);
	else if (tolower(*argv[1])=='r');
           receivef(argv[2]);




           }

