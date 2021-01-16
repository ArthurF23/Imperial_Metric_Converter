// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs
#include <string>
#include <sstream>
#include "converter.h"
#include <iomanip>
using namespace std;
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") //Adds some thing that make d3d9.h work
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

string remove_trailing_zeros(double input) {
    // Print value to a string
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6) << input;
    std::string str = ss.str();
    // Ensure that there is a decimal point somewhere (there should be)
    if (str.find('.') != std::string::npos)
    {
        // Remove trailing zeroes
        str = str.substr(0, str.find_last_not_of('0') + 1);
        // If the decimal point is now the last character, remove that as well
        if (str.find('.') == str.size() - 1)
        {
            str = str.substr(0, str.size() - 1);
        }
    }

    return str;
}

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
double input_double = 0.0f;
double output_double = 0.0f;
// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Converter"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Converter"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    ImFont* font_Bahn = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Bahnschrift.ttf", 17.0f);
    ImFont* font_PrgyCln = io.Fonts->AddFontFromFileTTF("C:\\Users\\apple\\AppData\\Local\\Microsoft\\Windows\\Fonts\\ProggyCleanCE.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        //if (show_demo_window)
        //ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ShowWindow(GetConsoleWindow(), SW_HIDE);
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
            ImGui::Begin("Converter", (bool*)true/*, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize*/);     
            // Create a window called "Hello, world!" and append into it.
            ImGui::PushFont(font_Bahn);
            const char* combo_items_type[] = { "Length", "Area", "Volume", "Liguid Volume", "Weight" };
            static int type_combo_item_current_idx = 0;                    // Here our selection data is an index.
            const char* type_combo_label = combo_items_type[type_combo_item_current_idx];  // Label to preview before opening the combo (technically it could be anything)
            
            if (ImGui::BeginCombo("Measurement Type", type_combo_label)) {
                for (int n = 0; n < IM_ARRAYSIZE(combo_items_type); n++)
                {
                    const bool is_selected = (type_combo_item_current_idx == n);
                    if (ImGui::Selectable(combo_items_type[n], is_selected))
                        type_combo_item_current_idx = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            };

            ImGui::NewLine();
            ImGui::NewLine();
            
            const char* combo_items_length[] = { "Inches", "Feet", "Yards", "Miles", "Nautical Miles", "Millimeters", "Centimeters", "Decimeters", "Meters", "Kilometers" };
            static int input_combo_item_current_idx_length = 0;            
            const char* input_combo_label_length = combo_items_length[input_combo_item_current_idx_length];  // Label to preview before opening the combo (technically it could be anything)
            
            static int output_combo_item_current_idx_length = 0;                    // Here our selection data is an index.
            const char* output_combo_label_length = combo_items_length[output_combo_item_current_idx_length];  // Label to preview before opening the combo (technically it could be anything)

            static int input_combo_item_current_idx_area = 0;
            const char* combo_items_area[] = { "Sq. Inches", "Sq. Feet", "Sq. Yards", "Sq. Miles", "Sq. Millimeters", "Sq. Centimeters", "Sq. Meters", "Hectares", "Sq. Kilometers" };
            const char* input_combo_label_area = combo_items_area[input_combo_item_current_idx_area];
            
            static int output_combo_item_current_idx_area = 0;                    // Here our selection data is an index.
            const char* output_combo_label_area = combo_items_area[output_combo_item_current_idx_area];  // Label to preview before opening the combo (technically it could be anything)

            static int input_combo_item_current_idx_volume = 0;
            const char* combo_items_volume[] = { "Cubic Inches", "Cubic Feet", "Cubic Millimeters", "Cubic Centimeters", "Cubic Decameters", "Cubic Meters" };
            const char* input_combo_label_volume = combo_items_volume[input_combo_item_current_idx_volume];

            static int output_combo_item_current_idx_volume = 0;                    // Here our selection data is an index.
            const char* output_combo_label_volume = combo_items_volume[output_combo_item_current_idx_volume];  // Label to preview before opening the combo (technically it could be anything)

            static int input_combo_item_current_idx_liquidvolume = 0;
            const char* combo_items_liquidvolume[] = { "Fluid Ounce", "Gill", "Cup", "Pint", "Quart", "Gallon", "Milliliter", "Centiliter", "Deciliter", "Liter", "Kiloliter" };
            const char* input_combo_label_liquidvolume = combo_items_liquidvolume[input_combo_item_current_idx_liquidvolume];

            static int output_combo_item_current_idx_liquidvolume = 0;                    // Here our selection data is an index.
            const char* output_combo_label_liquidvolume = combo_items_liquidvolume[output_combo_item_current_idx_liquidvolume];  // Label to preview before opening the combo (technically it could be anything)
            

            static int input_combo_item_current_idx_weight = 0;
            const char* combo_items_weight[] = { "Ounce", "Pound", "Milligram", "Centigram", "Decigram", "Gram", "Kilogram", "Tonne (Megagram)", "Gigagram" };
            const char* input_combo_label_weight = combo_items_weight[input_combo_item_current_idx_weight];

            static int output_combo_item_current_idx_weight = 0;                    // Here our selection data is an index.
            const char* output_combo_label_weight = combo_items_weight[output_combo_item_current_idx_weight];  // Label to preview before opening the combo (technically it could be anything)

            if (type_combo_item_current_idx == 0) {
                if (ImGui::BeginCombo("Input Type", input_combo_label_length)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_length); n++)
                    {
                        const bool is_selected = (input_combo_item_current_idx_length == n);
                        if (ImGui::Selectable(combo_items_length[n], is_selected))
                            input_combo_item_current_idx_length = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::NewLine();
                ImGui::NewLine();


                if (ImGui::BeginCombo("Output Type", output_combo_label_length)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_length); n++)
                    {
                        const bool is_selected = (output_combo_item_current_idx_length == n);
                        if (ImGui::Selectable(combo_items_length[n], is_selected))
                            output_combo_item_current_idx_length = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }

            else if (type_combo_item_current_idx == 1) {
                if (ImGui::BeginCombo("Input Type", input_combo_label_area)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_area); n++)
                    {
                        const bool is_selected = (input_combo_item_current_idx_area == n);
                        if (ImGui::Selectable(combo_items_area[n], is_selected))
                            input_combo_item_current_idx_area = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::NewLine();
                ImGui::NewLine();


                if (ImGui::BeginCombo("Output Type", output_combo_label_area)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_area); n++)
                    {
                        const bool is_selected = (output_combo_item_current_idx_area == n);
                        if (ImGui::Selectable(combo_items_area[n], is_selected))
                            output_combo_item_current_idx_area = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }

            else if (type_combo_item_current_idx == 2) {
                if (ImGui::BeginCombo("Input Type", input_combo_label_volume)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_volume); n++)
                    {
                        const bool is_selected = (input_combo_item_current_idx_volume == n);
                        if (ImGui::Selectable(combo_items_volume[n], is_selected))
                            input_combo_item_current_idx_volume = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::NewLine();
                ImGui::NewLine();


                if (ImGui::BeginCombo("Output Type", output_combo_label_volume)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_volume); n++)
                    {
                        const bool is_selected = (output_combo_item_current_idx_volume == n);
                        if (ImGui::Selectable(combo_items_volume[n], is_selected))
                            output_combo_item_current_idx_volume = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }

            else if (type_combo_item_current_idx == 3) {
                if (ImGui::BeginCombo("Input Type", input_combo_label_liquidvolume)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_liquidvolume); n++)
                    {
                        const bool is_selected = (input_combo_item_current_idx_liquidvolume == n);
                        if (ImGui::Selectable(combo_items_liquidvolume[n], is_selected))
                            input_combo_item_current_idx_liquidvolume = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::NewLine();
                ImGui::NewLine();


                if (ImGui::BeginCombo("Output Type", output_combo_label_liquidvolume)) {
                    for (int n = 0; n < IM_ARRAYSIZE(combo_items_liquidvolume); n++)
                    {
                        const bool is_selected = (output_combo_item_current_idx_liquidvolume == n);
                        if (ImGui::Selectable(combo_items_liquidvolume[n], is_selected))
                            output_combo_item_current_idx_liquidvolume = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }

            else if (type_combo_item_current_idx == 4) {
            if (ImGui::BeginCombo("Input Type", input_combo_label_weight)) {
                for (int n = 0; n < IM_ARRAYSIZE(combo_items_weight); n++)
                {
                    const bool is_selected = (input_combo_item_current_idx_weight == n);
                    if (ImGui::Selectable(combo_items_weight[n], is_selected))
                        input_combo_item_current_idx_weight = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::NewLine();
            ImGui::NewLine();


            if (ImGui::BeginCombo("Output Type", output_combo_label_weight)) {
                for (int n = 0; n < IM_ARRAYSIZE(combo_items_weight); n++)
                {
                    const bool is_selected = (output_combo_item_current_idx_weight == n);
                    if (ImGui::Selectable(combo_items_weight[n], is_selected))
                        output_combo_item_current_idx_weight = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            }

            ImGui::NewLine();
            ImGui::NewLine();

            
            ImGui::InputDouble("Input", &input_double);
            ImGui::SameLine();
            string output_label_extenstion = " ";
            if (type_combo_item_current_idx == 0) {
                ImGui::Text(input_combo_label_length);
                output_double = converter::convert_length(input_double, (converter::conversion_types_length)input_combo_item_current_idx_length, (converter::conversion_types_length)output_combo_item_current_idx_length);
                ImGui::Text(("Output: " + remove_trailing_zeros(output_double) + " " + output_combo_label_length).c_str());
            }
            else if (type_combo_item_current_idx == 1) {               
               
                ImGui::Text(input_combo_label_area);
                output_double = converter::convert_area(input_double, (converter::conversion_types_area)input_combo_item_current_idx_area, (converter::conversion_types_area)output_combo_item_current_idx_area);
                ImGui::Text(("Output: " + remove_trailing_zeros(output_double) + " " + output_combo_label_area).c_str());
            }
            else if (type_combo_item_current_idx == 2) {

                ImGui::Text(input_combo_label_volume);
                output_double = converter::convert_volume(input_double, (converter::conversion_types_volume)input_combo_item_current_idx_volume, (converter::conversion_types_volume)output_combo_item_current_idx_volume);
                ImGui::Text(("Output: " + remove_trailing_zeros(output_double) + " " + output_combo_label_volume).c_str());
            }
            else if (type_combo_item_current_idx == 3) {

                ImGui::Text(input_combo_label_liquidvolume);
                output_double = converter::convert_liquidvolume(input_double, (converter::conversion_types_liquidvolume)input_combo_item_current_idx_liquidvolume, (converter::conversion_types_liquidvolume)output_combo_item_current_idx_liquidvolume);
                ImGui::Text(("Output: " + remove_trailing_zeros(output_double) + " " + output_combo_label_liquidvolume).c_str());
            }
            else if (type_combo_item_current_idx == 4) {

                ImGui::Text(input_combo_label_weight);
                output_double = converter::convert_weight(input_double, (converter::conversion_types_weight)input_combo_item_current_idx_weight, (converter::conversion_types_weight)output_combo_item_current_idx_weight);
                ImGui::Text(("Output: " + remove_trailing_zeros(output_double) + " " + output_combo_label_weight).c_str());
            }
            else {
                ImGui::Text("err");
                output_double = input_double;
            };
            
            ImGui::Text((remove_trailing_zeros(input_double) + " / " + (input_double == 0 ? "0" : remove_trailing_zeros(input_double / output_double)) + " = " + remove_trailing_zeros(output_double)).c_str());
            
            ImGui::PopFont();
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
