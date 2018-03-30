#include "noui.h"

#include "ui_interface.h"
#include "util.h"

#include <cstdio>
#include <stdint.h>
#include <string>

static bool noui_ThreadSafeMessageBox(const std::string& message, const std::string& caption, unsigned int style)
{
    bool fSecure = style & CClientUIInterface::SECURE;
    style &= ~CClientUIInterface::SECURE;

    std::string strCaption;
    // Check for usage of predefined caption
    switch (style) {
    case CClientUIInterface::MSG_ERROR:
        strCaption += ("Error");
        break;
    case CClientUIInterface::MSG_WARNING:
        strCaption += ("Warning");
        break;
    case CClientUIInterface::MSG_INFORMATION:
        strCaption += ("Information");
        break;
    default:
        strCaption += caption; // Use supplied caption (can be empty)
    }

    if (!fSecure)
        LogPrintf("%s: %s\n", strCaption, message);
    fprintf(stderr, "%s: %s\n", strCaption.c_str(), message.c_str());
    return false;
}

static void noui_InitMessage(const std::string& message)
{
    fprintf(stdout, "noui_InitMessage called!\n");
}

void noui_connect()
{
    // Connect bitcoind signal handlers
    uiInterface.ThreadSafeMessageBox.connect(noui_ThreadSafeMessageBox);
    uiInterface.InitMessage.connect(noui_InitMessage);
}
