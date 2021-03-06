/*
 * =====================================================================================
 *
 *       Filename: main.cpp
 *        Created: 08/31/2015 08:52:57 PM
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#include <cstdio>
#include "log.hpp"
#include "client.hpp"
#include "xmlconf.hpp"
#include "pngtexdb.hpp"
#include "fontexdb.hpp"
#include "mapbindb.hpp"
#include "emoticondb.hpp"
#include "debugboard.hpp"
#include "pngtexoffdb.hpp"
#include "clientargparser.hpp"

// global variables, decide to follow pattern in MapEditor
// put all global in one place and create them togother

ClientArgParser *g_clientArgParser = nullptr;
Log             *g_log             = nullptr; // log information handler, must be inited first
PNGTexDB        *g_progUseDB       = nullptr; // database for all PNG texture only
PNGTexDB        *g_groundItemDB    = nullptr; // database for all PNG texture only
PNGTexDB        *g_commonItemDB    = nullptr; // database for all PNG texture only
PNGTexDB        *g_mapDB           = nullptr;
PNGTexOffDB     *g_heroDB          = nullptr; // database for hero
PNGTexOffDB     *g_monsterDB       = nullptr; // database for monster
PNGTexOffDB     *g_weaponDB        = nullptr; // database for weapon
PNGTexOffDB     *g_magicDB         = nullptr; // database for magic
PNGTexOffDB     *g_standNPCDB      = nullptr; // database for NPC
emoticonDB      *g_emoticonDB      = nullptr; // database for emoticons
MapBinDB        *g_mapBinDB        = nullptr;
FontexDB        *g_fontexDB        = nullptr;
XMLConf         *g_XMLConf         = nullptr; // for client configure XML parsing
SDLDevice       *g_SDLDevice       = nullptr; // for SDL hardware device
NotifyBoard     *g_notifyBoard     = nullptr;
Client          *g_client          = nullptr; // gobal instance

int main(int argc, char *argv[])
{
    std::srand((unsigned int)std::time(nullptr));
    try{
        arg_parser stCmdParser(argc, argv);
        auto fnAtExit = []()
        {
            delete g_clientArgParser; g_clientArgParser = nullptr;
            delete g_log            ; g_log             = nullptr;
            delete g_XMLConf        ; g_XMLConf         = nullptr;
            delete g_SDLDevice      ; g_SDLDevice       = nullptr;
            delete g_progUseDB      ; g_progUseDB       = nullptr;
            delete g_groundItemDB   ; g_groundItemDB    = nullptr;
            delete g_commonItemDB   ; g_commonItemDB    = nullptr;
            delete g_mapDB          ; g_mapDB           = nullptr;
            delete g_heroDB         ; g_heroDB          = nullptr;
            delete g_monsterDB      ; g_monsterDB       = nullptr;
            delete g_fontexDB       ; g_fontexDB        = nullptr;
            delete g_mapBinDB       ; g_mapBinDB        = nullptr;
            delete g_emoticonDB     ; g_emoticonDB      = nullptr;
            delete g_notifyBoard    ; g_notifyBoard     = nullptr;
            delete g_client         ; g_client          = nullptr;
        };

        std::atexit(fnAtExit);

        g_clientArgParser = new ClientArgParser(stCmdParser);
        g_log             = new Log("mir2x-client-v0.1");

    }catch(const std::exception &e){
        std::fprintf(stderr, "Caught exception: %s\n", e.what());
        return -1;
    }catch(...){
        std::fprintf(stderr, "Caught unknown exception, exit...\n");
        return -1;
    }

    try{
        g_XMLConf         = new XMLConf();
        g_SDLDevice       = new SDLDevice();
        g_progUseDB       = new PNGTexDB(1024);
        g_groundItemDB    = new PNGTexDB(1024);
        g_commonItemDB    = new PNGTexDB(1024);
        g_mapDB           = new PNGTexDB(8192);
        g_heroDB          = new PNGTexOffDB(1024);
        g_monsterDB       = new PNGTexOffDB(1024);
        g_weaponDB        = new PNGTexOffDB(1024);
        g_magicDB         = new PNGTexOffDB(1024);
        g_standNPCDB      = new PNGTexOffDB(1024);
        g_fontexDB        = new FontexDB(1024);
        g_mapBinDB        = new MapBinDB();
        g_emoticonDB      = new emoticonDB();
        g_client          = new Client();       // loads fontex resource
        g_notifyBoard     = new NotifyBoard(0, 0, 10240, 0, 15, 0, colorf::RED + 255);

        g_client->mainLoop();

    }catch(const std::exception &e){
        g_log->addLog(LOGTYPE_FATAL, "Caught exception: %s", e.what());
    }catch(...){
        g_log->addLog(LOGTYPE_FATAL, "Caught unknown exception, exit...");
    }
    return 0;
}
