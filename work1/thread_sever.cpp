#include "thread_sever.h"
#include <QDebug>


thread_sever::thread_sever(QWidget *parent) : QThread(parent)
{

}

void thread_sever::run()
{
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(9999);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    int ret = bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    ret=listen(lfd,64);

    //readset init
    fd_set redset;
    FD_ZERO(&redset);
    FD_SET(lfd,&redset);
    fd_set temp;
    int maxfd=lfd;

    while(1)
    {
        temp=redset;
        int ret = select(maxfd+1,&temp,NULL,NULL,NULL);
        if(FD_ISSET(lfd,&temp))
        {
            //connnect
            struct sockaddr_in client_addr;
            memset(&client_addr,0,sizeof(client_addr));

            socklen_t client_len=sizeof(client_addr);
            int cfd = accept(lfd,(struct sockaddr*)&client_addr,&client_len);//second parameter client addr data
            FD_SET(cfd,&redset);
            maxfd =cfd>maxfd?cfd:maxfd;
            //add a button
            addButtonToList(&client_addr,cfd);
        }
        //no new connect  use for conmmunicate
        for(int i=0;i<=maxfd;++i)
        {
            if(i!=lfd&&FD_ISSET(i,&temp))
            {
                char buf[1024]={0};
                int len =recv(i,buf,sizeof(buf),0);
                QString str=QString(QLatin1String(buf));

                QString ip =str.section("##",0,0);
                int CPUdata=str.section("##",1,1).toInt();
                int GPUdata=str.section("##",2,2).toInt();
                int diskData=str.section("##",3,3).toInt();
                int memData=str.section("##",4,4).toInt();
                QString time =str.section("##",5,5);
                int netSpeed = str.section("##",6,6).toInt();



//                qDebug()<<"disk "<<diskData;
//                qDebug()<<"mem  "<<memData;
//                qDebug()<<"time"<<time;
//                printf("speed \n",netSpeed);
                Data data;
                data.init(i,ip,CPUdata,GPUdata,diskData,memData,time,netSpeed);
                emit sendData(data);
                msleep(0);

                if(len == -1)
                {
                    perror("recv error");
                    exit(1);
                }
                else if(len ==0)
                {
                    printf("client disconnected");
                    //client disconnected emit signal file describe
                    emit client_Disconnecte(i);
                    FD_CLR(i,&redset);
                    close(i);
                    break;
                }

                printf("read buf =%s\n",buf);
                for(int i = 0;i<len;++i)
                {
                    buf[i]=toupper(buf[i]);
                }
                printf("after buf =%s\n",buf);
                ret=send(i,buf,strlen(buf)+1,0);
                if(ret==-1)
                {
                    perror("send error");
                    exit(1);
                }
                msleep(0);
            }
        }



    }


//    printf("client ip: %s,port : %d\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,
//                                                 ipbuf,sizeof(ipbuf)),
//           client_addr.sin_port);



    close(lfd);

}

void thread_sever::addButtonToList(struct sockaddr_in* addr,int fd)
{

    //send the data of btn
//    MyButton *btn = new MyButton;
    QString addr_str = inet_ntoa(addr->sin_addr);
//    QString str =QString::number(num);
//    addr_str.append("+");
//    addr_str.append(str);
//    btn->setText(addr_str);
//    m_button_list.push_front(btn);
//    num++;
    emit ButtonChanged(addr_str,fd);
}
