#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <vector>
#include <curses.h>

class CSnake:public CFramedWindow
{
private:
	char jedzonko;
	char glowa;
	char cialo;
	int level;
	int kierunek;
	char wybor;
	vector <CPoint> punkty;
	CPoint punkt1;
	CPoint punkt2;
	CPoint pozycja_jedzonka;
	
public:
  CSnake(CRect r, char _c = ' ');
  bool handleEvent(int key);
  void paint();
  void menu();
  void gra();
  void restart();
  void help();
  int getEvent();
  void paint_snake();
  void paint_jedzonko();
  void poruszanie();
  bool jedzenie();
  void tworzenie_jedzonka();
  bool koniec();
  void ekran_koniec();
  

};

#endif
