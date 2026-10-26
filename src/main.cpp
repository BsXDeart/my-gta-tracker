#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

// SDK Header for GTA San Andreas & ImGui
#include "plugin.h"
#include "Renderware.h"
#include "CVector.h"
#include "CPed.h"
#include "CWorld.h"
#include "CRadar.h"
#include "imgui.h"

// ตัวแปรสำหรับเก็บรายชื่อผู้เล่นที่กำลังติดตาม
std::vector<std::string> targetNames;
char inputBuffer[64] = "";
bool showMenu = false;

// เช็คการกดปุ่ม Insert เพื่อเปิด/ปิดเมนู
void ProcessKeyInput() {
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        showMenu = !showMenu;
    }
}

// ระบบค้นหาและปักหมุดตำแหน่งเป้าหมาย
void ProcessTracking() {
    if (targetNames.empty()) return;

    // วนลูปตรวจหา Ped ในเกม (รวมถึงตัวละคร SA-MP)
    for (CPed* ped : CWorld::ms_pInterestingList) {
        if (!ped) continue;

        // ดึงตำแหน่งของ Ped
        CVector pos = ped->GetPosition();

        // หมายเหตุ: หากใช้งานกับ SA-MP ให้เชื่อมต่อ SAMP-SDK ดึงชื่อตัวละครมาเทียบตรงนี้
        // หากพบผู้เล่นที่มีชื่อตรงกับใน targetNames ให้แสดง Marker บนมินิแมพ
        /*
        std::string name = GetPlayerNameFromPed(ped);
        if (std::find(targetNames.begin(), targetNames.end(), name) != targetNames.end()) {
            CRadar::SetCoordBlip(PREDEF_TARGET_BLIP, pos, 2, BLIP_MODE_THREAD);
        }
        */
    }
}

class PlayerTrackerPlugin {
public:
    PlayerTrackerPlugin() {
        // ประมวลผลลูปของเกม
        plugin::Events::gameProcessEvent += [] {
            ProcessKeyInput();
            ProcessTracking();
        };

        // Render Loop สำหรับหน้าต่างเมนู ImGui
        plugin::Events::drawingEvent += [] {
            if (!showMenu) return;

            ImGui::Begin("Player Tracker Menu", &showMenu, ImGuiWindowFlags_AlwaysAutoResize);
            
            ImGui::Text("ใส่ชื่อผู้เล่นที่ต้องการติดตาม:");
            ImGui::InputText("##playername", inputBuffer, sizeof(inputBuffer));
            
            ImGui::Spacing();

            if (ImGui::Button("ติดตาม (Track)")) {
                if (strlen(inputBuffer) > 0) {
                    std::string nameToTrack(inputBuffer);
                    // ตรวจสอบไม่ให้ใส่ชื่อซ้ำ
                    if (std::find(targetNames.begin(), targetNames.end(), nameToTrack) == targetNames.end()) {
                        targetNames.push_back(nameToTrack);
                    }
                    inputBuffer[0] = '\0'; // ล้างช่องพิมพ์
                }
            }
            
            ImGui::SameLine();

            if (ImGui::Button("หยุดติดตาม (Untrack)")) {
                if (strlen(inputBuffer) > 0) {
                    std::string nameToUntrack(inputBuffer);
                    auto it = std::remove(targetNames.begin(), targetNames.end(), nameToUntrack);
                    targetNames.erase(it, targetNames.end());
                    inputBuffer[0] = '\0'; // ล้างช่องพิมพ์
                }
            }

            ImGui::Separator();
            ImGui::Text("รายชื่อที่กำลังติดตาม (%zu):", targetNames.size());

            if (targetNames.empty()) {
                ImGui::TextDisabled("(ยังไม่มีรายชื่อ)");
            } else {
                for (size_t i = 0; i < targetNames.size(); ++i) {
                    ImGui::Text("%zu. %s", i + 1, targetNames[i].c_str());
                }
            }

            ImGui::End();
        };
    }
} trackerPlugin;
