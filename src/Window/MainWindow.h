//
// src/Window/MainWindow.h
//
// Summary

#ifndef WINDOW_MAINWINDOW_H
#define WINDOW_MAINWINDOW_H

class MainWindow {
public:
  MainWindow() noexcept;

  auto Create() -> bool;
  auto Run() -> int;

private:
  bool m_running;
};

#endif // WINDOW_MAINWINDOW_H
