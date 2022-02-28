/*
* socket.h
*
*  Created on: 2020.04.07
*      Author: lc
*/
#include <stdarg.h>

#include "log.h"
#include "msg.h"
#include "types.h"
#include "utils.h"
#include "socket.h"
#include "userMsg.h"
#include "response.h"
#include "setting.h"
#include "user_timer.h"
#include "watchdog.h"
#include "data.h"
#include "request.h"
#include "client.h"
#include "event.h"

typedef struct
{
    uint8_t cid;
    bool    isPDPActive;
    bool    isTransState;

    int16_t port;
    int8_t  domain[64];
    uint8_t ip_addr[4];
    int32_t socket_id;
    int8_t  udp_socketId;
    uint8_t *pIsLogined;
    SOCKET_ACTION *pLoginAction;
    SOCKET_ACTION *pRuningAction;
    SOCKET_RECV_ACTION *pRecvAction;

} SocketStatus_st;

static volatile SocketStatus_st g_socket = {
    .socket_id = -1,
    .udp_socketId = -1,
};
static u8 socket_conSignal = 0;


#define DESC_DEF(x) case x:\
                            return #x

static char *socket_getStateDescription(SocketState_enum state)
{
    switch (state)
    {
            DESC_DEF(SOCKET_WAIT_REGISTER);
            DESC_DEF(SOCKET_WAIT_PDPACTIVE);
            DESC_DEF(SOCKET_WAIT_IPADDR);
            DESC_DEF(SOCKET_WAIT_SOCKET);
            DESC_DEF(SOCKET_WAIT_SUBSCRIBE1);
            DESC_DEF(SOCKET_WAIT_SUBSCRIBE2);
            DESC_DEF(SOCKET_WAIT_LOGIN);
            DESC_DEF(SOCKET_RUNING);

        default:
        {
            static char state_name[10] = {0};
            snprintf(state_name, 10, "%d", state);
            return state_name;
        }
    }
}

static bool socket_isSocketCreated(void)
{
    if(g_socket.socket_id >= 0 || data_getData()->isSocketConnect)
    {
        return true;
    }
    return false;
}

int socket_close(void)
{
    if(socket_isSocketCreated())
    {
        fibo_sock_lwip_fcntl(g_socket.socket_id, F_SETFL, fibo_sock_lwip_fcntl(g_socket.socket_id, F_GETFL, 0) & (~O_NONBLOCK));
        fibo_sock_close(g_socket.socket_id);
        g_socket.socket_id = -1;
        socket_conSignal = 0;
        data_getData()->isSocketConnect = 0;
    }
    return 0;
}


void socket_sig_callback(GAPP_SIGNAL_ID_T sig, va_list arg)
{
    switch (sig)
    {
        //fibo_PDPActive  ip address resopnse event
        case GAPP_SIG_PDP_ACTIVE_ADDRESS:
        {
            UINT8 cid = (UINT8)va_arg(arg, int);
            char *addr = (char *)va_arg(arg, char *);
            if(addr != NULL)
            {
                g_socket.cid = cid;
                g_socket.isPDPActive = true;
                LOG_DEBUG("cid = %d, addr = %s ", cid, addr);
            }
            else
            {
                g_socket.isPDPActive = false;
            }
            LOG_DEBUG("[sig] GAPP_SIG_PDP_ACTIVE_ADDRESS");
            va_end(arg);
        }
        break;

        //fibo_getHostByName event
        case GAPP_SIG_DNS_QUERY_IP_ADDRESS:
        {
            char *host = (char *)va_arg(arg, char *);
            char *ipv4_addr = (char *)va_arg(arg, char *);
            char *ipv6_addr = (char *)va_arg(arg, char *);

            if(host != NULL)
            {
                LOG_DEBUG("sig_res_callback, host = %s ", host);
            }
            if(ipv4_addr != NULL)
            {
                int ipaddr[4] = {0};
                int i = sscanf(ipv4_addr, "%d.%d.%d.%d", &ipaddr[0], &ipaddr[1], &ipaddr[2], &ipaddr[3]);
                if(i == 4)
                {
                    g_socket.ip_addr[0] = ipaddr[0];
                    g_socket.ip_addr[1] = ipaddr[1];
                    g_socket.ip_addr[2] = ipaddr[2];
                    g_socket.ip_addr[3] = ipaddr[3];
                    LOG_DEBUG("getHostByName: %s -> %d.%d.%d.%d", g_socket.domain, g_socket.ip_addr[0], g_socket.ip_addr[1], g_socket.ip_addr[2], g_socket.ip_addr[3]);
                }
                LOG_DEBUG("sig_res_callback, ipv4_addr = %s ", ipv4_addr);
            }
            else if(ipv6_addr != NULL)
            {
                LOG_DEBUG("sig_res_callback, ipv6_addr = %s ", ipv6_addr);
            }
            else
            {
                LOG_DEBUG("sig_res_callback, ip_addr is NULL");
            }
            va_end(arg);
        }
        break;

        //fibo_PDPActive /fibo_asyn_PDPActive  pdp active status report
        case GAPP_SIG_PDP_ACTIVE_IND:
        {
            UINT8 cid = (UINT8)va_arg(arg, int);
            g_socket.cid = cid;
            g_socket.isPDPActive = true;
            LOG_DEBUG("sig_res_callback  cid = %d", cid);
            va_end(arg);
        }
        break;

        //fibo_PDPRelease /fibo_asyn_PDPRelease pdp deactive status report
        case GAPP_SIG_PDP_RELEASE_IND:
        {
            UINT8 cid = (UINT8)va_arg(arg, int);
            g_socket.cid = 0;
            g_socket.isPDPActive = false;
            LOG_DEBUG("sig_res_callback  cid = %d", cid);
            va_end(arg);
        }
        break;

        case GAPP_SIG_PDP_DEACTIVE_ABNORMALLY_IND:
        {
            int ret;
            UINT8 ip[50];
            g_socket.cid = 0;
            g_socket.isPDPActive = false;
            LOG_DEBUG("GAPP_SIG_PDP_DEACTIVE_ABNORMALLY_IND.");

            fibo_taskSleep(1000);
            ret = fibo_PDPActive(1, setting.settingConf.apnname, setting.settingConf.username, setting.settingConf.password, 0, 0, ip);
            LOG_DEBUG("ret = %d,ip=%s", ret, ip);
        }
        break;

        default:
        {
            break;
        }
    }
}

static int socket_ip4addr_aton(const char *cp, ip4_addr_t *addr)
{
    u32_t val;
    u8_t base;
    char c;
    u32_t parts[4];
    u32_t *pp = parts;

    c = *cp;
    for (;;)
    {
        /*
        * Collect number up to ``.''.
        * Values are specified as for C:
        * 0x=hex, 0=octal, 1-9=decimal.
        */
        if (!isdigit(c))
        {
            return 0;
        }
        val = 0;
        base = 10;
        if (c == '0')
        {
            c = *++cp;
            if (c == 'x' || c == 'X')
            {
                base = 16;
                c = *++cp;
            }
            else
            {
                base = 8;
            }
        }
        for (;;)
        {
            if (isdigit(c))
            {
                val = (val * base) + (u32_t)(c - '0');
                c = *++cp;
            }
            else if (base == 16 && isxdigit(c))
            {
                val = (val << 4) | (u32_t)(c + 10 - (islower(c) ? 'a' : 'A'));
                c = *++cp;
            }
            else
            {
                break;
            }
        }
        if (c == '.')
        {
            /*
            * Internet format:
            *  a.b.c.d
            *  a.b.c   (with c treated as 16 bits)
            *  a.b (with b treated as 24 bits)
            */
            if (pp >= parts + 3)
            {
                return 0;
            }
            *pp++ = val;
            c = *++cp;
        }
        else
        {
            break;
        }
    }
    /*
    * Check for trailing characters.
    */
    if (c != '\0' && !isspace(c))
    {
        return 0;
    }
    /*
    * Concoct the address according to
    * the number of parts specified.
    */
    switch (pp - parts + 1)
    {

        case 0:
            return 0; /* initial nondigit */

        case 1: /* a -- 32 bits */
            break;

        case 2: /* a.b -- 8.24 bits */
            if (val > 0xffffffUL)
            {
                return 0;
            }
            if (parts[0] > 0xff)
            {
                return 0;
            }
            val |= parts[0] << 24;
            break;

        case 3: /* a.b.c -- 8.8.16 bits */
            if (val > 0xffff)
            {
                return 0;
            }
            if ((parts[0] > 0xff) || (parts[1] > 0xff))
            {
                return 0;
            }
            val |= (parts[0] << 24) | (parts[1] << 16);
            break;

        case 4: /* a.b.c.d -- 8.8.8.8 bits */
            if (val > 0xff)
            {
                return 0;
            }
            if ((parts[0] > 0xff) || (parts[1] > 0xff) || (parts[2] > 0xff))
            {
                return 0;
            }
            val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
            break;
        default:
            break;
    }
    if (addr)
    {
        ip4_addr_set_u32(addr, val);
    }
    return 1;
}

bool socket_isRegNet(void)
{
    reg_info_t regInfo = {0};
    fibo_getRegInfo(&regInfo, CFW_SIM_0);
    if(regInfo.nStatus == REG_STATE_REGISTERED || regInfo.nStatus == REG_STATE_REGISTERED_ROAMING)
    {
        return true;
    }
    LOG_DEBUG("reg status: %d", regInfo.nStatus);
    return false;
}
static void socket_actionOnRegNet(void)
{
    //do nothing
    return;
}

bool socket_isPDPActived(void)
{
    static u8 count = 0;

    if(count++ < 60)  //每分钟调用一次接口查状态,期间每秒使用cid来判断,降低系统内存开销
    {
        if(g_socket.cid <= 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        count = 0;
        u8 ip[50] = {0};
        u8 state = 0;
        memset(ip, 0, sizeof(ip));
        INT32 ret = fibo_PDPStatus(g_socket.cid, ip, &state, 0);
        if(ret == 0 && state == 1)  //广和通建议IP不用判断
        {
            LOG_DEBUG("PDP active success");
            return true;
        }
        else
        {
            LOG_DEBUG("PDP active failed");
            g_socket.cid = 0;
            return false;
        }
    }

    return false;
}
static void socket_actionOnActivePDP(void)
{
    static uint32_t times = 0;
    if(g_socket.isTransState || times++ > 10)
    {
        times = 0;
        g_socket.isTransState = false;

        uint8_t ip[50] = {0};
        fibo_PDPActive(1, setting.settingConf.apnname, setting.settingConf.username, setting.settingConf.password, 0, CFW_SIM_0, ip);
    }
}

static bool socket_isIPAddrGet(void)
{
    if(0 != memcmp((const u8 *)g_socket.ip_addr, "\0\0\0\0", 4))
    {
        return true;
    }
    return false;
}
static void socket_actionOnGetIPAddr(void)
{
    static uint32_t times = 0;
    if(g_socket.isTransState || times++ > 10)
    {
        times = 0;
        g_socket.isTransState = false;

        LOG_DEBUG("*** socket domain%s",g_socket.domain);
        if(strlen((const char *)g_socket.domain))
        {
            ip_addr_t addr = {0};
            int32_t ret = fibo_getHostByName((char *)g_socket.domain, &addr, g_socket.cid, CFW_SIM_0);
            if(ret >= 0)
            {
                g_socket.ip_addr[0] = (addr.u_addr.ip4.addr >> 0) & 0xFF;
                g_socket.ip_addr[1] = (addr.u_addr.ip4.addr >> 8) & 0xFF;
                g_socket.ip_addr[2] = (addr.u_addr.ip4.addr >> 16) & 0xFF;
                g_socket.ip_addr[3] = (addr.u_addr.ip4.addr >> 24) & 0xFF;
                LOG_DEBUG("getHostByName: %s -> %d.%d.%d.%d", g_socket.domain, g_socket.ip_addr[0], g_socket.ip_addr[1], g_socket.ip_addr[2], g_socket.ip_addr[3]);
            }
            else
            {
                LOG_ERROR("getHostByName error:%d", ret);
            }
        }
        else
        {
            LOG_ERROR("socket domain NULL.");
        }
    }
}

static int32_t tempsocketid  = 0;
static GAPP_TCPIP_ADDR_T tempaddr;
void socket_ConnectThread(void *argument)
{
    osiThreadSetFPUEnabled(true); //线程使能FPU
    int32_t retcode;
    while(true)
    {
        if(socket_conSignal)
        {
            retcode = fibo_sock_connect(tempsocketid, &tempaddr); //最大阻塞36s
            socket_conSignal = 0;
            if(retcode != 0)
            {
                fibo_sock_close(tempsocketid);
                data_getData()->isSocketConnect = 0;
                LOG_ERROR("socket connect failed: %d", retcode);
            }
            else
            {
                data_getData()->isSocketConnect = 1;
                LOG_DEBUG("socket connect success :%d", tempsocketid);
                retcode = fibo_sock_lwip_fcntl(tempsocketid, F_SETFL, fibo_sock_lwip_fcntl(tempsocketid, F_GETFL, 0) | O_NONBLOCK);
                if(retcode != 0)
                {
                    fibo_sock_close(tempsocketid);
                    LOG_ERROR("socket set fcntl failed: %d", retcode);
                    return;
                }
                g_socket.socket_id = tempsocketid; //正式connect成功
            }
        }
        fibo_taskSleep(500);
    }
    fibo_thread_delete();
}

static void socket_connect(void)
{
    GAPP_TCPIP_ADDR_T addr;
    int32_t socketid;
    const char addrBuff[64] = {0};

    if(socket_conSignal == 1)
    {
        LOG_ERROR("socket is connecting !");
        return ;
    }
    memset(&addr, 0, sizeof(GAPP_TCPIP_ADDR_T));

    INT32 rssi = 0, ber = 0;
    fibo_get_csq(&rssi, &ber);
    if(rssi < 7)
    {
        LOG_DEBUG("rssi:%d, ber%d", rssi, ber);
        return;
    }

    socketid = fibo_sock_create(GAPP_IPPROTO_TCP);
    if(socketid < 0)
    {
        LOG_DEBUG("socket created failde:%d", socketid);
        return;
    }
    LOG_DEBUG("socket created :%d", socketid);

    addr.sin_port = _htons(g_socket.port);
    snprintf((char *)addrBuff, 64, "%d.%d.%d.%d", g_socket.ip_addr[0], g_socket.ip_addr[1], g_socket.ip_addr[2], g_socket.ip_addr[3]);
    socket_ip4addr_aton((const char *)addrBuff, &addr.sin_addr.u_addr.ip4);
    addr.sin_addr.u_addr.ip4.addr = _htonl(addr.sin_addr.u_addr.ip4.addr);

    int opt = 1;
    fibo_sock_setOpt(socketid, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(int));
    fibo_sock_setOpt(socketid, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(int));

    tempsocketid = socketid;
    memcpy(&tempaddr, &addr, sizeof(addr));
    socket_conSignal = 1;

    return;
}

static void socket_actionOnCreateSocket(void)
{
    static uint32_t times = 0;
    if(g_socket.isTransState || times++ > 10)
    {
        times = 0;
        g_socket.isTransState = false;
        data_getData()->socstate.conn_fail++;

        socket_connect();
    }
}

bool socket_isLogined(void)
{
    if(g_socket.pIsLogined && *g_socket.pIsLogined)
    {
        return true;
    }
    return false;
}
static void socket_actionOnLogin(void)
{
    static uint32_t times = 0;
    if(g_socket.isTransState || times++ > 10)
    {
        times = 0;
        g_socket.isTransState = false;

        if(g_socket.pLoginAction)
        {
            g_socket.pLoginAction();
        }
    }
}

static void socket_actionOnRuning(void)
{
    if(g_socket.pRuningAction)
    {
        g_socket.pRuningAction();
    }
}

int socket_run(void)
{
    static uint8_t g_State = SOCKET_WAIT_REGISTER;

    uint8_t state = SOCKET_WAIT_REGISTER;
    do
    {
        if(!socket_isRegNet())
        {
            state = SOCKET_WAIT_REGISTER;
            break;
        }

        if(!socket_isPDPActived())
        {
            state = SOCKET_WAIT_PDPACTIVE;
            break;
        }

        if(!socket_isIPAddrGet())
        {
            state = SOCKET_WAIT_IPADDR;
            break;
        }

        if(!socket_isSocketCreated())
        {
            state = SOCKET_WAIT_SOCKET;
            break;
        }

        if(!socket_isLogined())
        {
            state = SOCKET_WAIT_LOGIN;
            break;
        }

        state = SOCKET_RUNING;
    }
    while(false);

    if(g_State != state)
    {
        LOG_DEBUG("state: %s -> %s", socket_getStateDescription(g_State), socket_getStateDescription(state));
        g_socket.isTransState = true;
        g_State = state;
    }
    LOG_DEBUG("socket run(%s)", socket_getStateDescription(g_State));

    switch(g_State)
    {
        case SOCKET_WAIT_REGISTER:
        {
            socket_actionOnRegNet();
            break;
        }

        case SOCKET_WAIT_PDPACTIVE:
        {
            socket_actionOnActivePDP();
            break;
        }

        case SOCKET_WAIT_IPADDR:
        {
            socket_actionOnGetIPAddr();
            break;
        }

        case SOCKET_WAIT_SOCKET:
        {
            socket_actionOnCreateSocket();
            break;
        }

        case SOCKET_WAIT_LOGIN:
        {
            socket_actionOnLogin();
            break;
        }

        case SOCKET_RUNING:
        {
            socket_actionOnRuning();
            break;
        }

        default:
            break;
    }

    return 0;
}

void socket_initial(void)
{
    if(setting.serverConf.addr_type == ADDR_TYPE_IP)
    {
        memset((char *)setting.serverConf.domain, 0, 64);
        memset((int8_t *)g_socket.domain, 0, 64);

        memset((uint8_t *)g_socket.ip_addr, 0, 4);
        memcpy((uint8_t *)g_socket.ip_addr, setting.serverConf.ipaddr, 4);

        LOG_DEBUG("[Socket] Reinitial IP:%d.%d.%d.%d Port:%d",g_socket.ip_addr[0],g_socket.ip_addr[1],g_socket.ip_addr[2],g_socket.ip_addr[3],setting.serverConf.port);
    }
    else if(setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
    {
        memset((uint8_t *)setting.serverConf.ipaddr, 0, 4);
        memset((uint8_t *)g_socket.ip_addr, 0, 4);

        memset((char *)g_socket.domain, 0, 64);
        memcpy((char *)g_socket.domain, setting.serverConf.domain, 64);

        LOG_DEBUG("[Socket] Reinitial Domain:%s Port:%d", g_socket.domain, setting.serverConf.port);
    }

    g_socket.port = setting.serverConf.port;
    g_socket.pIsLogined = &data_getData()->isLogined;
    g_socket.pLoginAction = cmd_Login;
    g_socket.pRecvAction = client_proc;
    g_socket.pRuningAction = event_fsm_running;

    if(socket_isSocketCreated())socket_close();
    if(g_socket.pIsLogined)*g_socket.pIsLogined = L_FALSE;
    LOG_DEBUG("socket_initial.");

    timer_startRepeat(TIMER_SOCKET_LOOP, TIMER_S, 1, socket_run);
}

int socket_sendData(void *data, int32_t len)
{
    if(!socket_isSocketCreated()) return -1;

    int32_t rc = fibo_sock_send(g_socket.socket_id, data, len);
    if(rc >= 0)
    {
        if(rc != len)
        {
            fibo_taskSleep(100);
            rc = fibo_sock_send(g_socket.socket_id, data, len); //发送字节数不对，延时重发一次
        }

        if(rc == len)
        {
            LOG_HEX((const char *)data, len);
            LOG_DEBUG("socket send data successful.");
            data_getData()->socstate.pkts_sent++;
            data_getData()->socstate.bytes_sent += len;
        }
        else
        {
            LOG_HEX((const char *)data, rc);
            LOG_DEBUG("socket send data partly, len(%d) suc(%d).", len, rc);
        }
    }
    else
    {
        int err = fibo_get_socket_error();
        if(err == EAGAIN || err == EWOULDBLOCK)
        {
            fibo_taskSleep(100);
            rc = fibo_sock_send(g_socket.socket_id, data, len); //提示重试，延时重发一次

            if(rc == len)
            {
                LOG_HEX((const char *)data, len);
                LOG_DEBUG("socket send data again successful.");
                data_getData()->socstate.pkts_sent++;
                data_getData()->socstate.bytes_sent += len;
            }
            else if(rc < 0)
            {
                LOG_ERROR("socket send data again error(%d), sock: %d, len: %d, rc: %d.", err, g_socket.socket_id, len, rc);
                socket_initial();
            }
            else
            {
                LOG_HEX((const char *)data, rc);
                LOG_DEBUG("socket send data again partly, len(%d) suc(%d).", len, rc);
            }
        }
        else
        {
            LOG_ERROR("socket send data error(%d), sock: %d, len: %d, rc: %d.", err, g_socket.socket_id, len, rc);
            socket_initial();
        }
    }

    return rc;
}

int32_t socket_sendDataDirectly(void *data, int32_t len)
{
    int32_t rc = socket_sendData(data, len);

    free_msg(data);

    return rc;
}

int32_t socket_sendDatawithUDP(void *data, int32_t len)
{
    if(g_socket.udp_socketId < 0)
    {
        int32_t socketid = fibo_sock_create(GAPP_IPPROTO_UDP);
        if(socketid < 0)
        {
            LOG_DEBUG("socket created failde: %d", socketid);
            Free(data);
            return -1;
        }

        int32_t retcode = fibo_sock_lwip_fcntl(socketid, F_SETFL, fibo_sock_lwip_fcntl(socketid, F_GETFL, 0) | O_NONBLOCK);
        if(retcode != 0)
        {
            fibo_sock_close(socketid);
            LOG_ERROR("socket set fcntl failed: %d", retcode);
            Free(data);
            return -1;
        }
        LOG_DEBUG("socket created: %d", socketid);

        g_socket.udp_socketId = socketid;
    }

    GAPP_TCPIP_ADDR_T addr = {0};
    const char addrBuff[64] = {0};

    addr.sin_port = _htons(9999);
    snprintf((char *)addrBuff, 64, "%d.%d.%d.%d", 47, 115, 118, 121);
    socket_ip4addr_aton((const char *)addrBuff, &addr.sin_addr.u_addr.ip4);
    addr.sin_addr.u_addr.ip4.addr = _htonl(addr.sin_addr.u_addr.ip4.addr);

    int32_t res = fibo_sock_send2(g_socket.udp_socketId, (UINT8 *)data, (UINT16)len, &addr);
    LOG_DEBUG("udp send:");
    LOG_HEX(data, len);

    Free(data);
    return res;
}

#define MAX_SOCKET_RECV_LENGTH 1024
int32_t socket_select(void)
{
    struct timeval tv = {0, 0};
    fd_set socReadSet;
    FD_ZERO(&socReadSet);
    if(g_socket.socket_id)
    {
        FD_SET(g_socket.socket_id, &socReadSet);
    }
    if(g_socket.udp_socketId)
    {
        FD_SET(g_socket.udp_socketId, &socReadSet);
    }
    int32_t ret = fibo_sock_lwip_select(3, &socReadSet, NULL, NULL, &tv); //3 for 2 sockets +1
    if(ret < 0)
    {
        LOG_ERROR("select error, ret: %d", ret);
        return -1;
    }
    else if(ret == 0)
    {
        //LOG_DEBUG("select timeout");
        return -1;
    }

    static uint8_t *recvBuff = NULL;
    if(!recvBuff)
    {
        recvBuff = Malloc(MAX_SOCKET_RECV_LENGTH);
    }

    if(g_socket.socket_id && FD_ISSET(g_socket.socket_id, &socReadSet))
    {
        ret = fibo_sock_recv(g_socket.socket_id, recvBuff, MAX_SOCKET_RECV_LENGTH);
        if(ret > 0) //接收到数据了
        {
            if(g_socket.pRecvAction)
            {
                g_socket.pRecvAction(recvBuff, ret);
                data_getData()->socstate.pkts_acked++;
                data_getData()->socstate.bytes_acked += ret;
            }
        }
        else if(ret == 0) //socket对端断连
        {
            LOG_ERROR("socket recv data error.");
            socket_initial();
            data_getData()->socstate.conn_close++;
        }
    }

    if(g_socket.udp_socketId && FD_ISSET(g_socket.udp_socketId, &socReadSet))
    {
        GAPP_TCPIP_ADDR_T addr = {0};
        const char addrBuff[64] = {0};

        addr.sin_port = _htons(9999);
        snprintf((char *)addrBuff, 64, "%d.%d.%d.%d", 47, 115, 118, 121);
        socket_ip4addr_aton((const char *)addrBuff, &addr.sin_addr.u_addr.ip4);
        addr.sin_addr.u_addr.ip4.addr = _htonl(addr.sin_addr.u_addr.ip4.addr);

        ret = fibo_sock_recvFrom(g_socket.udp_socketId, recvBuff, MAX_SOCKET_RECV_LENGTH, &addr);
        if(ret > 0) //接收到数据了
        {
            client_udp_proc(recvBuff, ret);
        }
    }

    return 0;
}
