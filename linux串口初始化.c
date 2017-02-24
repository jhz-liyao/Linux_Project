bool CSerialInterface::initialSerial(const char *serialDev)
{
    serial_fd = open(serialDev, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd < 0) {
        PRINT("can not open serial port %s\r\n", serialDev);
        return false;
    }   

    //������Ҫ���ýṹ��termios <termios.h>  
    struct termios options;

    /**1. tcgetattr�������ڻ�ȡ���ն���صĲ�����
    *����fdΪ�ն˵��ļ������������صĽ��������termios�ṹ����
    */
    tcgetattr(serial_fd, &options);
    /**2. �޸�����õĲ���*/
    options.c_cflag |= (CLOCAL | CREAD);//���ÿ���ģʽ״̬���������ӣ�����ʹ��  
    options.c_cflag &= ~CSIZE;//�ַ����ȣ���������λ֮ǰһ��Ҫ�������λ  
    options.c_cflag &= ~CRTSCTS;//��Ӳ������  
    options.c_cflag |= CS8;//8λ���ݳ���  
    options.c_cflag &= ~CSTOPB;//1λֹͣλ  
    options.c_iflag |= IGNPAR;//����ż����λ  
    options.c_oflag = 0; //���ģʽ  
    options.c_lflag = 0; //�������ն�ģʽ  
    cfsetospeed(&options, B115200);//���ò�����  

    /**3. ���������ԣ�TCSANOW�����иı�������Ч*/
    tcflush(serial_fd, TCIFLUSH);//������ݿ��Խ��գ�������  
    tcsetattr(serial_fd, TCSANOW, &options);

    return true;
}
