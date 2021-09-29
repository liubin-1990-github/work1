#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QMetaType>

class Data
{
public:
    Data();
    Data(int fd,QString ip,int cpu,int gpu,int dis,int mem,QString time,int netS);
    void init(int fd,QString ip,int cpu,int gpu,int dis,int mem,QString time,int netS);

//    int fd,QString ip,int cpu,int gpu,int dis,int mem,QString time
    int m_fd;
    QString m_ip;
    int m_cpu;
    int m_gpu;
    int m_dis;
    int m_mem;
    QString m_time;
    int m_netS;
};
Q_DECLARE_METATYPE(Data)

#endif // DATA_H
