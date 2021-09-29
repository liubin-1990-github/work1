#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>


int getCPUdata();
int getGPUdata();
int getDiskData();
int getMemoriData();
void getTime(char*);
int getNetS();


int main()
{
//    int CPUdata=0;
//    int memoryData=0;
//    int GPUdata=0;
//    int DiskData=0;

    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);
    int ret = connect(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1)
    {
        perror("connect");
        exit(1);
    }

    //get local addr data
    struct sockaddr_in local_addr;
    socklen_t len;
    bzero(&local_addr,sizeof(local_addr));
    getsockname(fd,(struct sockaddr*)&local_addr,&len);
    char bufff[30]="";
    printf("local ip is %s\n",inet_ntop(AF_INET,&local_addr.sin_addr,bufff,sizeof(bufff)));
    printf("local ip is %s\n",bufff);
//    strcat(bufff,"+21");

    int num=0;
    while (1)
    {

        char* cur_tiem = (char*)malloc(14*sizeof(char));
        getTime(cur_tiem);
        printf("Current time: %s\n",cur_tiem);
        int  CPUdata= getCPUdata();
        int GPUdata=getGPUdata();
        int DiskData=getDiskData();
        int memoryData= getMemoriData();
        int netSpeed=getNetS();
        char temp[20]={0};
        char buf[1024]={0};
//        strncat(cur_time,sec,3);
        strcat(buf,bufff); //ip
        strcat(buf,"22222##");
//        sprintf(temp,"%d",fd);
//        strcat(buf,temp);
//        strcat(buf,"##");
        sprintf(temp,"%d",CPUdata);//cpu
        strcat(buf,temp);        
        strcat(buf,"##");

        sprintf(temp,"%d",GPUdata);//gpu
        strcat(buf,temp);
        strcat(buf,"##");

        sprintf(temp,"%d",DiskData);//disk
        strcat(buf,temp);
        strcat(buf,"##");

        sprintf(temp,"%d",memoryData);//memory
        strcat(buf,temp);
        strcat(buf,"##");

        strcat(buf,cur_tiem);
        strcat(buf,"##");

        sprintf(temp,"%d",netSpeed);
        strcat(buf,temp);





//        fgets(buf,sizeof(buf),stdin);
//        sprintf(buf ,"data :%d\n",num++);
        write(fd,buf,sizeof(buf));
        read(fd,buf,sizeof(buf));
        printf("recv buf: %s\n",buf);
        sleep(1);
        free(cur_tiem);
    }
    close(fd);


    return 0;
}


int getCPUdata()
{
    static int num_cpu=0;
    num_cpu+=1;
    num_cpu%=100;
    return num_cpu;
}
int getGPUdata()
{
    static int num_gpu=0;
    num_gpu+=2;
    num_gpu=num_gpu%100;
    return num_gpu;
}
int getDiskData()
{
    static int num_disk=0;
    num_disk+=3;
    num_disk%=100;
    return num_disk;
}
int getMemoriData()
{
    static int num_memori=0;
    num_memori+=4;
    num_memori%=100;
    return num_memori;
}
int getNetS()
{
    int s = rand()%20+10;
    return s;
}
void getTime(char* cur_time)
{
    char Year[6]={0};
    char month[4]={0};
    char day[4]={0};
    char hour[4]={0};
    char min[4]={0};
    char sec[4]={0};

    timer_t current_time;
    struct tm* now_time;
    time(&current_time);
    now_time=localtime(&current_time);
//    current_time=time(NULL);
//    now_time=localtime(&current_time);
    printf("local time is %s",asctime(now_time));


    strftime(Year,sizeof(Year),"%Y",now_time);
    strftime(month,sizeof(month),"%m",now_time);
    strftime(day,sizeof(day),"%d",now_time);
    strftime(hour,sizeof(hour),"%H",now_time);
    strftime(min,sizeof(min),"%M",now_time);
    strftime(sec,sizeof(sec),"%S",now_time);

    strncat(cur_time,Year,5);
    strncat(cur_time,month,3);
    strncat(cur_time,day,3);
    strncat(cur_time,hour,3);
    strncat(cur_time,min,3);
    strncat(cur_time,sec,3);

}
