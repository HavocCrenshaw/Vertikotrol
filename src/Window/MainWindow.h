//
// src/Window/MainWindow.h
//
// The MainWindow class. MainWindow is the class that handles the main
// application window and owns the main class.

#ifndef WINDOW_MAINWINDOW_H
#define WINDOW_MAINWINDOW_H

class MainWindow {
public:
  // Initialize the members of the MainWindow object.
  MainWindow() noexcept;

  // Create the main window.
  auto Create() -> bool;

  // Run the main loop.
  auto Run() -> int;

private:
  // The state of the main loop.
  bool m_running;
};

#endif // WINDOW_MAINWINDOW_H
