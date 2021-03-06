// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// Copyright(C) 2007-2012 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
//-----------------------------------------------------------------------------

#ifndef _SERVER_H_
#define _SERVER_H_

#include "enet/enet.h"
#include "client.h"

typedef enum {
    SV_STATE_UNAVAILABLE,
    SV_STATE_BUSY,
    SV_STATE_ACTIVE
} server_state_e;

typedef enum {
    SVC_STATE_INACTIVE,
    SVC_STATE_ACTIVE,
    SVC_STATE_INGAME
} svclient_state_e;

//
// SERVER PACKET TYPES
//
typedef enum {
    sp_ping         = 1,
    sp_clientinfo,
    sp_msg,
    sp_pmove,
    sp_weaponinfo,
    sp_changemap,
    sp_noclip,
    NUMSERVERPACKETS
} sv_packets_t;

//
// SERVER MESSAGES
//
typedef enum {
    sm_full         = 1,
    NUMSERVERMESSAGES
} sv_messages_t;

#define SERVER_RUNTIME  100

class kexServer : public kexNetwork {
public:
    virtual void        Init(void);
    virtual void        Destroy(void);
    virtual void        Shutdown(void);
    virtual void        ProcessPackets(const ENetPacket *packet);
    virtual void        CreateHost(void);
    virtual void        Run(const int msec);
    virtual void        OnConnect(void);
    virtual void        OnDisconnect(void);

    bool                IsLocal(void) { return bLocal; }
    int                 GetElaspedTime(void) { return elaspedTime; }
    void                SetElaspedTime(int _time) { elaspedTime = _time; }
    int                 GetMaxClients(void) { return maxClients; }
    void                SetMaxClients(int _max) { maxClients = _max; }

    char                *GetPeerAddress(ENetEvent *sev);
    void                SendMessage(ENetEvent *sev, int type);
    void                NotifyMapChange(const int mapID);

private:
    void                SendClientMessages(void);
    void                ClientCommand(ENetEvent *sev, ENetPacket *packet);
    void                SendAcknowledgement(ENetEvent *sev);

    bool                bLocal;
    int                 maxClients;
    int                 elaspedTime;
};

extern kexServer server;


#endif