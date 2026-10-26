#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

#include "plugin.h"
#include "CVector.h"
#include "CPed.h"
#include "CWorld.h"
#include "CMessages.h"

std::vector<std::string> targetNames;
bool trackingEnabled = false;

// เช็คการกดปุ่ม Insert เพื่อเปิด/ปิดระบบติดตาม
void ProcessKeyInput() {
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        trackingEnabled = !trackingEnabled;
        if (trackingEnabled) {
            CMessages::AddMessageJumpQ((char*)"~g~Player Tracker Activated", 2000, 0, false);
        } else {
            CMessages::AddMessageJumpQ((char*)"~r~Player Tracker Deactivated", 2000, 0, false);
        }
    }
}

// ลูปตรวจหาตำแหน่งผู้เล่นเป้าหมายในเกม
void ProcessTracking() {
    if (!trackingEnabled || targetNames.empty()) return;

    for (CPed* ped : CWorld::ms_pInterestingList) {
        if (!ped) continue;
        CVector pos = ped->GetPosition();
        // ประมวลผลตำแหน่งเป้าหมายต่อใน SA-MP
    }
}

class PlayerTrackerPlugin {
public:
    PlayerTrackerPlugin() {
        plugin::Events::gameProcessEvent += [] {
            ProcessKeyInput();
            ProcessTracking();
        };
    }
} trackerPlugin;
