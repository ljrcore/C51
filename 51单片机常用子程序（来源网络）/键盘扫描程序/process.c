#define uchar unsigned char
uchar scankb(void);       //����ɨ��
extern void signal(void); //P2.0����2ms����
extern void RS232(void);  //�ɼ��̽����ַ����ط�
extern void sent (void);  //��PC�����ַ���
extern void display(void);//��ʾ�ӳ���
void main(void)
{uchar key;
 for(;;)
  {key=scankb();
   switch(key)
     {case 0x88:sent();break;
      case 0x84:signal();break;
      case 0x82:display();break;
      case 0x81:RS232();break;
      case 0x48:break;
      case 0x44:break;
      case 0x42:break;
      case 0x41:break;
      case 0x28:break;
      case 0x24:break;
      case 0x22:break;
      case 0x21:break;
      case 0x18:break;
      case 0x14:break;
      case 0x12:break;
      case 0x11:break;
      default:;
     }
   }
}

