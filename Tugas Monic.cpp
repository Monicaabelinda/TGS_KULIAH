#include <iostream>
#include <conio.h>
#define MAX 10

using namespace std;

class binary{
   static int input[MAX];
   public:
   void cari();
};

int binary::input[MAX] = {0, 4, 5, 6, 8, 9, 9, 10, 11, 56};

void binary::cari() {
   int cari, middle, tm, l, r;
         cout << " 0, 4, 5, 6, 8, 9, 9, 10, 11, 56 " << endl;
         cout << endl << " Data yang ingin anda cari : "; 
		 cin >> cari;
         tm = 0;
         r = MAX - 1;
         l = 0;
         while(r >= l) {
                 middle = ( l + r ) / 2;
                 if(input[middle] == cari) 
				 	tm++;
                 if(input[middle] < cari)    
				 	l = middle + 1;
                 else    
				 	r = middle - 1;
         }
        if(tm > 0) 
			cout << " Ada ! ";
        else             
			cout << " Tidak ada ! ";
}

int main() {
  	binary x;
  	x.cari();
  	getch();
}
