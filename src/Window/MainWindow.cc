//
// src/Window/MainWindow.cc
//
// Handle the creation of the main window and own the main loop

#include <Window/MainWindow.h>

#ifdef _WIN64

#include <windows.h>

static LRESULT CALLBACK handleMessages(
  HWND windowHandle,
  UINT msg,
  WPARAM basicParams,
  LPARAM extraParams
) {
  switch (msg) {
    case WM_ERASEBKGND: {
      return 1; // We'll handle it in WM_PAINT
    }

    case WM_PAINT: {
      PAINTSTRUCT paintInfo;
      HDC deviceContextHandle = BeginPaint(windowHandle, &paintInfo);

      FillRect(
        deviceContextHandle,
        &paintInfo.rcPaint,
        (HBRUSH)GetStockObject(BLACK_BRUSH)
      );

      EndPaint(windowHandle, &paintInfo);
      return 0;
    }

    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
  }

  return DefWindowProc(windowHandle, msg, basicParams, extraParams);
}

MainWindow::MainWindow() noexcept {
  m_running = false;
}

auto MainWindow::Create() -> bool {
  // Variables
  wchar_t* currentInstanceName = nullptr;
  HINSTANCE currentInstance = GetModuleHandleW(currentInstanceName);
  if (!currentInstance) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif // DEBUG
  }

  HINSTANCE systemResources = nullptr;

  int defaultWidth = 0;
  int defaultHeight = 0;
  unsigned int loadingFlags = LR_DEFAULTSIZE | LR_SHARED;
  HICON iconHandle = static_cast<HICON>(LoadImageW(
    systemResources,
    IDI_APPLICATION,
    IMAGE_ICON,
    defaultWidth,
    defaultHeight,
    loadingFlags
  ));
  if (!iconHandle) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif // DEBUG
  }

  HCURSOR cursorHandle = static_cast<HCURSOR>(LoadImageW(
    systemResources,
    IDC_ARROW,
    IMAGE_CURSOR,
    defaultWidth,
    defaultHeight,
    loadingFlags
  ));
  if (!cursorHandle) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif // DEBUG
  }

  constexpr wchar_t CLASS_NAME[] = L"MainWindowClass";

  // Create the window class
  WNDCLASSEXW windowClass = { 0 };
  windowClass.cbSize = sizeof(WNDCLASSEXW);
  windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  windowClass.lpfnWndProc = handleMessages;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = currentInstance;
  windowClass.hIcon = iconHandle;
  windowClass.hCursor = cursorHandle;
  windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
  windowClass.lpszMenuName = nullptr;
  windowClass.lpszClassName = CLASS_NAME;
  windowClass.hIconSm = iconHandle;

  if (RegisterClassExW(&windowClass) == 0) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif // DEBUG
  }

  // Variables
  unsigned long exStyle = 0;
  constexpr wchar_t WINDOW_TITLE[] = L"VERTIKOTROL";
  unsigned long style = WS_POPUP | WS_VISIBLE;
  int xPos = CW_USEDEFAULT;
  int yPos = CW_USEDEFAULT;
  int width = CW_USEDEFAULT;
  int height = CW_USEDEFAULT;
  HWND noParentWindow = nullptr;
  HMENU noMenu = nullptr;
  void* noCreationParams = nullptr;
 
  // Create the window
  HWND windowHandle = CreateWindowExW(
    exStyle,
    CLASS_NAME,
    WINDOW_TITLE,
    style,
    xPos,
    yPos,
    width,
    height,
    noParentWindow,
    noMenu,
    currentInstance,
    noCreationParams
  );
  if (!windowHandle) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif // DEBUG
  }

  // Fullscreen it
  unsigned long defaultMonitor = MONITOR_DEFAULTTONEAREST;
  HMONITOR monitorHandle = MonitorFromWindow(windowHandle, defaultMonitor);
  
  MONITORINFO monitorInfo = { 0 };
  monitorInfo.cbSize = sizeof(MONITORINFO);
  if (!GetMonitorInfoW(monitorHandle, &monitorInfo)) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif
  }
  RECT windowRect = monitorInfo.rcMonitor;

  unsigned int flags = 0;
  if (!SetWindowPos(
    windowHandle,
    HWND_TOP,
    windowRect.left,
    windowRect.top,
    windowRect.right - windowRect.left,
    windowRect.bottom - windowRect.top,
    flags
  )) {
#ifdef DEBUG
    return false;
#else // DEBUG
    return false;
#endif
  }

  // Show the window
  ShowWindow(windowHandle, SW_SHOW);
  UpdateWindow(windowHandle);

  return true;
}

auto MainWindow::Run() -> int {
  // Variables
  MSG msg = { 0 };
  HWND everyWindow = nullptr;
  UINT filterMin = 0;
  UINT filterMax = 0;
  UINT handling = PM_REMOVE;

  m_running = true;
  while (m_running) {
    // Handle messages
    while (PeekMessageW(&msg, everyWindow, filterMin, filterMax, handling)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);

      if (msg.message == WM_QUIT) {
        m_running = false;
        break;
      }
    }

    if (!m_running) {
      break;
    }
    
    // Game Logic
  }

  return (int)msg.wParam;
}

#else // _WIN64

// Add X11/Wayland window creation and management.

#endif // _WIN64
