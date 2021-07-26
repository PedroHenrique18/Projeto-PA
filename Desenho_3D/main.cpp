#include "sculptor.h"
#include "sculptor.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main(){
    Sculptor Desenho_3D(100,100,100);

    Desenho_3D.setColor(0.7,1,0.2,0);
    Desenho_3D.putEllipsoid(50,50,50,10,37,10);
    Desenho_3D.cutEllipsoid(50,50,50,10,5,10);


    Desenho_3D.setColor(139,0,139,0);
    Desenho_3D.putSphere(50,26,50,15);


    Desenho_3D.setColor(139,0,139,0);
    Desenho_3D.putSphere(50,48,50,15);




    Desenho_3D.writeOFF((char*)"Desenho.off");
    return 0;
}
