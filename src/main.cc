//
// src/Main.cc
//

#include <Window/MainWindow.h>

#ifdef _WIN64

#include <windows.h>

// Windows entry point.
auto WINAPI wWinMain(
  _In_ HINSTANCE appHandle,
  _In_opt_ HINSTANCE /* Unused */,
  _In_ PWSTR commandLine,
  _In_ int windowPresentation
) -> int {
  MainWindow mainWindow;

  if (!mainWindow.Create()) {
    return 1;
  }

  int exitCode = mainWindow.Run();

  return exitCode;
}

#else // _WIN64

// Linux entry point.
auto main(int argc, char** argv) -> int {
  MainWindow mainWindow;

  if (!mainWindow.Create()) {
    return 1;
  }

  int exitCode = mainWindow.Run();

  return exitCode;
}

#endif
