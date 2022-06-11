/// clang-format off

#include <windows.h>
#include <winbase.h>
// clang-format on

#include <Tlhelp32.h>
#include <process.h>
#include <stdio.h>
#include <string.h>

#include <QApplication>

#include "QCryptographicHash"
#include "QDebug"
#include "QMessageBox"
#include "QProcess"
#include "QString"
#include "mainwindow.h"

typedef unsigned long long QWORD;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  QProcess *satelliteProcess = new QProcess();
  int pid = QApplication::applicationPid();
  QStringList arguments = {QString::number(pid)};
  satelliteProcess->start("DebugProtector.exe", arguments);
  bool protectorStarted = satelliteProcess->waitForStarted(1000);




  // 1 Определение начала сегмента .text
  QWORD moduleBase = (QWORD)GetModuleHandleW(NULL); //начальный адрес приложенияв виртуальной памяти/
  QWORD text_segment_start = moduleBase + 0x1000; //адрессегмента .text/


  // 2 Определение длины сегмента .text
  PIMAGE_DOS_HEADER pIDH = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
  PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase+pIDH->e_lfanew);
  QWORD size_of_text = pINH->OptionalHeader.SizeOfCode;
  //размер сегмента .text
  //qDebug() << "size_of_text = " << size_of_text;

  // 3 Подсчет хэша и его шифрование
  QByteArray text_segment_contents = QByteArray((char*)text_segment_start,
  size_of_text); QByteArray hash = QCryptographicHash::hash((text_segment_contents),QCryptographicHash::Sha256).toBase64();
  //qDebug() << "text_segment_contents = " << Qt::hex << text_segment_contents.first(100);
  qInfo() << "hash = " << hash;

  // 4 Сравнение хэша полученного на прошлых этапах с эталонным
  const QByteArray hash0_base64 = QByteArray("KSxDVYwsiOAWFxJMJK32XxLQ57uWTQyL+4vtqf+jRn4=");
  bool checkresult =(hash==hash0_base64);
  //qDebug() << "checkresult = " << checkresult;

  // 5 Реакция на измененный хэш
  if(!checkresult){
    int result = QMessageBox::critical(nullptr,"Warning!","App has been patched");
    return -1;
  }
  return a.exec(), system("taskkill /im DebugProtector.exe /f");
}
