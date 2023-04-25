#include "snake.h"
#include "winsys.h"
#include "cpoint.h"
#include "screen.h"
#include <time.h>
#include <stdlib.h>

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
	wybor = 'x';
	jedzonko = 'O';
	glowa = '*';
	cialo = '+';
	level = 1;
	kierunek = 2;
	punkty.push_back(CPoint(geom.topleft.x+6,geom.topleft.y+1));
	punkty.push_back(CPoint(punkty[0].x-1,punkty[0].y));
	punkty.push_back(CPoint(punkty[1].x-1,punkty[1].y));
	punkt1.x = punkty[0].x;
	punkt1.y = punkty[0].y;
	pozycja_jedzonka.x = geom.topleft.x + 9 ;
	pozycja_jedzonka.y = geom.topleft.y + 9 ;
}

 void CSnake::paint()
 {
	 CFramedWindow::paint();
	 
	 if(wybor == 'x')
	 {
		 CSnake::menu();
	 }
	 else if(wybor == 'h')
	 {
		 CSnake::help();
	 }
	 else if(wybor == 'p')
	 {
		 CSnake::gra();
	 }
	 else if(wybor == 'r')
	 {
		 CSnake::restart();
	 }
	  
 }
 bool CSnake::handleEvent(int key)
 {
	 if(key == 'h')
	 {
		 this->wybor = 'h';
		 return true;
	 }
	 
	 else if(key == 'p')
	 {
		 this->wybor = 'p';
		 return true;
	 }
	 
	 else if(key == 'r')
	 {
		 this->wybor = 'r';
		 return true;
	 }
	 
	 else if(key == 'x')
	 {
		 this->wybor = 'x';
		 return true;
	 }
	 else
	 {
		 this->wybor = 'x';
		 
		 if(CWindow::handleEvent(key))
		 {
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
 }
  void CSnake::menu()
  {
	  gotoyx(geom.topleft.y+2,geom.topleft.x+2);
	  printl("%s","h - toggle help information");
	  
	  gotoyx(geom.topleft.y+4,geom.topleft.x+2);
	  printl("%s","p - toggle pause/ play mode");
	  
	  gotoyx(geom.topleft.y+6,geom.topleft.x+2);
	  printl("%s","r - restart game");
	  
	  gotoyx(geom.topleft.y+8,geom.topleft.x+2);
	  printl("%s","arrows - move snake/move window");
	  
  }
  void CSnake::gra()
  {
	  int predkosc = 0;
	  while(1)
	  {
		  gotoyx(geom.topleft.y-1,geom.topleft.x);
		  printl("%s","LEVEL");
		  printl("%d",level);
		  
		  
		  CFramedWindow::paint();
		  if(jedzenie())
		  {
			  level++;
			  punkty.push_back(CPoint(punkty[punkty.size()-1].x,punkty[punkty.size()-1].y));
			  tworzenie_jedzonka();
		  }
		  paint_snake();
		  paint_jedzonko();
		  if(predkosc == 12-(level%3))
		  {
			  predkosc = 0;
			  poruszanie();
		  }
		  
		  
		  int klawisz;
		  klawisz = getEvent();
		  if(klawisz == 'p')
		  {
			  break;
		  }
		  else if( klawisz == KEY_UP)
		  {
			  if(kierunek != 1)
			  {
				  kierunek = -1;
			  }
		  }
		  else if( klawisz == KEY_LEFT)
		  {
			  if(kierunek != 2)
			  {
				  kierunek = -2;
			  }
		  }
		  else if( klawisz == KEY_RIGHT)
		  {
			  if(kierunek != -2)
			  {
				  kierunek = 2;
			  }
		  }
		  else if( klawisz == KEY_DOWN)
		  {
			  if(kierunek != -1)
			  {
				  kierunek = 1;
			  }
		  }
		  
		  
		  predkosc++;
		  if(koniec())
		  {
			  wybor = 't';
			  break;
		  }
	  }
	  
	  if(wybor != 't')
	  {
		  CSnake::menu();
	  }
	  else
	  {
		  ekran_koniec();
	  }
  }
  void CSnake::restart()
  {
	punkty.clear();
	wybor = 'x';
	jedzonko = 'O';
	glowa = '*';
	cialo = '+';
	level = 1;
	kierunek = 2;
	punkty.push_back(CPoint(geom.topleft.x+6,geom.topleft.y+1));
	punkty.push_back(CPoint(punkty[0].x-1,punkty[0].y));
	punkty.push_back(CPoint(punkty[1].x-1,punkty[1].y));
	punkt1.x = punkty[0].x;
	punkt1.y = punkty[0].y;
	pozycja_jedzonka.x = geom.topleft.x + 9 ;
	pozycja_jedzonka.y = geom.topleft.y + 9 ;
	menu();
  }
  void CSnake::help()
  {
	  gotoyx(geom.topleft.y+2,geom.topleft.x+2);
	  printl("%s"," strzalka w gore - poruszasz sie w gore");
	  gotoyx(geom.topleft.y+3,geom.topleft.x+2);
	  printl("%s"," strzalka w dol - poruszasz sie w dol");
	  gotoyx(geom.topleft.y+4,geom.topleft.x+2);
	  printl("%s"," strzalka w prawo - poruszasz sie w prawo");
	  gotoyx(geom.topleft.y+5,geom.topleft.x+2);
	  printl("%s"," strzalka w lewo - poruszasz sie w lewo");
	  gotoyx(geom.topleft.y+6,geom.topleft.x+2);
	  printl("%s"," jablko - O");
	  gotoyx(geom.topleft.y+7,geom.topleft.x+2);
	  printl("%s"," powrot - x");
  }
  
  int CSnake::getEvent()
  {
	  return ngetch();
  }
  void CSnake::paint_snake()
  {
	  gotoyx(punkty[0].y,punkty[0].x);
	  printc(glowa);
	  
	  for(long unsigned int i = 1 ; i < punkty.size(); i++)
	  {
		  gotoyx(punkty[i].y,punkty[i].x);
		  printc(cialo);
	  }
  }
  void CSnake::paint_jedzonko()
  {
	  gotoyx(pozycja_jedzonka.y,pozycja_jedzonka.x);
	  printc(jedzonko);
  }
  
  void CSnake::poruszanie()
  {
	  if(kierunek == 2)
	  {
		  if(punkty[0].x + 1 == geom.topleft.x + geom.size.x - 1)
		  {
			  punkty[0].x = geom.topleft.x + 1;
		  }
		  else
		  {
			  punkty[0].x = punkty[0].x + 1;
		  }
	  }
	  
	  else if(kierunek == -2)
	  {
		  if(punkty[0].x - 1 == geom.topleft.x)
		  {
			  punkty[0].x = geom.topleft.x + geom.size.x - 2;
		  }
		  else
		  {
			  punkty[0].x = punkty[0].x - 1;
		  }
	  }
	  
	  else if(kierunek == 1)
	  {
		  if(punkty[0].y + 1 == geom.topleft.y + geom.size.y - 1)
		  {
			  punkty[0].y = geom.topleft.y + 1;
		  }
		  else
		  {
			  punkty[0].y = punkty[0].y + 1;
		  }
	  }
	  
	  else if(kierunek == -1)
	  {
		  if(punkty[0].y - 1 == geom.topleft.y)
		  {
			  punkty[0].y = geom.topleft.y + geom.size.y - 2;
		  }
		  else
		  {
			  punkty[0].y = punkty[0].y - 1;
		  }
	  }
	  
	  for(long unsigned int i = 1 ; i < punkty.size() ; i++)
	  {
		  if(i%2 != 0)
		  {
			  punkt2.x = punkty[i].x;
			  punkt2.y = punkty[i].y;
			  punkty[i].x  = punkt1.x;
			  punkty[i].y = punkt1.y;
	      }
		  else
		  {
			  punkt1.x = punkty[i].x;
			  punkt1.y = punkty[i].y;
			  punkty[i].x  = punkt2.x;
			  punkty[i].y = punkt2.y;
	      }
	  }
	  punkt1.x = punkty[0].x;
	  punkt1.y = punkty[0].y;
  }
  
  bool CSnake:: jedzenie()
  {
	  if(pozycja_jedzonka.x == punkty[0].x && pozycja_jedzonka.y == punkty[0].y)
	  {
		  return true;
	  }
	  
	  return false;
  }
  
   void CSnake::tworzenie_jedzonka()
   {
	   bool flag = true;
	   int x = 0;
	   int y = 0;
	   srand(time(NULL));
	   while(flag)
	   {
		   flag = false;
		   x = 1 + geom.topleft.x + (rand() % (geom.size.x - 2));
		   y = 1 + geom.topleft.y + (rand() % (geom.size.y - 2));
		   
		   for(long unsigned int i = 0 ; i < punkty.size() ; i++)
		   {
			   if(punkty[i].x == x && punkty[i].y == y)
			   {
				   flag = true;
				   break;
			   }
			}
	   }
	   
	   pozycja_jedzonka.x = x;
	   pozycja_jedzonka.y = y;
	   
   }
   
   bool CSnake::koniec()
   {
	   for(long unsigned int i = 1; i < punkty.size() ; i++)
	   {
		   if(punkty[i].x == punkty[0].x && punkty[i].y == punkty[0].y)
		   {
			   return true;
		   }
	   }
	   return false;
   }
   void CSnake::ekran_koniec()
   {
	   gotoyx(geom.topleft.y+2,geom.topleft.x+2);
	   printl("%s","GAME OVER ! WYNIK: ");
	   printl("%d",level-1);
   }
