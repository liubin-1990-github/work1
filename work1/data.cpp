#include "data.h"

Data::Data()
{

}

Data::Data(int fd, QString ip, int cpu, int gpu, int dis, int mem, QString time,int netS)
    :m_fd(fd),m_ip(ip),m_cpu(cpu),m_gpu(gpu),m_dis(dis),m_mem(mem),m_time(time),m_netS(netS)
{

}

void Data::init(int fd, QString ip, int cpu, int gpu, int dis, int mem, QString time,int nets)
{
    m_fd=fd;
    m_ip=ip;
    m_cpu=cpu;
    m_gpu=gpu;
    m_dis=dis;
    m_mem=mem;
    m_time=time;
    m_netS=nets;

}

