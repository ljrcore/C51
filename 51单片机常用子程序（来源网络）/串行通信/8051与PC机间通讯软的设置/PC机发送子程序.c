void sendf(char *fname)
     {FILE *fp;
      char ch;
      int handle,count,sum=0;
      if((fp=fopen(fname,"r"))==NULL)
         {printf("���ܴ�������!\n");
          exit(1);
          }
      handl=fileno(fp);
      count=filelength(handle);
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
       sport(sum);
       if(rport()=='F')
          {count=filelenth(handle);
           sum=0;
           fseek(fp,-count,1);
           goto rep;
           }
       else 
           {fclose(fp);
            printf("�����ļ�����\n");
            }
            }    
                  
                