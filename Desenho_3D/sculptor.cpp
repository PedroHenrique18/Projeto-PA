#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[0][0]= new Voxel[nx*ny*nz];
    v[1] = v[0] + ny*sizeof(Voxel**);
    for(int i=1; i<nz; i++)
    {
        v[i] = v[i-1] + ny;
    }
    for(int i=1; i<nz*ny; i++)
    {
        v[0][i] = v[0][i-1] + nx;
    }
    v[4][6][6].isOn = false;
}

/**
*Destrutor da Classe Sculptor
*/
Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

void  Sculptor :: setColor ( float r, float g, float b, float alpha){
    if (r>= 0 && r<= 1 ){
        this -> r=r;
    }
    if (g>= 0 && g <= 1 ){
        this -> g=g;
    }
    if (b>= 0 && b<= 1 ){
        this -> b=b;
    }
    if (g>= 0 && g <= 1 ){
        this -> g=g;
    }
    if (alpha>= 0 && alpha<= 1 ){

        a=alpha;
    }
}

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void  Sculptor :: cutVoxel ( int x, int y, int z){
    v[x][y][z].isOn = false ;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
               putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for ( int i = 0 ; i <(2*xcenter); i ++)
    {
        for ( int j = 0 ; j < (2*ycenter); j ++)
        {
            for ( int k = 0 ; k < (2*zcenter); k ++)
            {
                if (((i-xcenter) * (i-xcenter) + (j-ycenter) * (j-ycenter) + (k-zcenter) * (k-zcenter)) <= (radius*radius))
                {
                   putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for ( int i = 0 ; i <(2*xcenter); i ++)
    {
        for ( int j = 0 ; j < (2*ycenter); j ++)
        {
            for ( int k = 0 ; k < (2*zcenter); k ++)
            {
                if (((i-xcenter) * (i-xcenter) + (j-ycenter) * (j-ycenter) + (k-zcenter) * (k-zcenter)) <= (radius*radius))
                {
                   cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

    for(int i=xcenter-rx; i< xcenter+rx; i++)
    {
        for(int j=ycenter-ry; j<ycenter + ry; j++)
        {
            for(int k=zcenter-rz; k< zcenter+rz; k++)
            {
                if ((pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) <= 1)
                {
                   putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=xcenter-rx; i< xcenter+rx; i++)
    {
        for(int j=ycenter-ry; j<ycenter + ry; j++)
        {
            for(int k=zcenter-rz; k< zcenter+rz; k++)
            {
                if ((pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) <= 1)
                {
                   cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char *nome){
    string str;
    ofstream f_out;
    f_out.open(nome);

    cout<<"Entrou\n";

    if(! f_out.good())
    {
        cout << "Falha ao criar arquivo\n";
    }
    else
        cout << "Arquivo criado!\n";


    int totalDeElementos = nx*ny*nz;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == false)
                {
                    totalDeElementos--;
                }
            }
        }
    }

    str += "OFF\n";
    str += to_string(totalDeElementos*8) + " " + to_string(totalDeElementos*6) + " " + "0\n";

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    str += to_string(k-0.5) + " " + to_string(j+0.5) + " " + to_string(i-0.5) + "\n";
                    str += to_string(k-0.5) + " " + to_string(j-0.5) + " " + to_string(i-0.5) + "\n";
                    str += to_string(k+0.5) + " " + to_string(j-0.5) + " " + to_string(i-0.5) + "\n";
                    str += to_string(k+0.5) + " " + to_string(j+0.5) + " " + to_string(i-0.5) + "\n";
                    str += to_string(k-0.5) + " " + to_string(j+0.5) + " " + to_string(i+0.5) + "\n";
                    str += to_string(k-0.5) + " " + to_string(j-0.5) + " " + to_string(i+0.5) + "\n";
                    str += to_string(k+0.5) + " " + to_string(j-0.5) + " " + to_string(i+0.5) + "\n";
                    str += to_string(k+0.5) + " " + to_string(j+0.5) + " " + to_string(i+0.5) + "\n";
                }
            }
        }
    }

    int cont = 0;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    int pos = 8*cont;
                    str += "4 " + to_string(pos) + " " + to_string(pos+3) + " " + to_string(pos+2) + " " + to_string(pos+1) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    str += "4 " + to_string(pos+4) + " " + to_string(pos+5) + " " + to_string(pos+6) + " " + to_string(pos+7) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    str += "4 " + to_string(pos) + " " + to_string(pos+1) + " " + to_string(pos+5) + " " + to_string(pos+4) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    str += "4 " + to_string(pos) + " " + to_string(pos+4) + " " + to_string(pos+7) + " " + to_string(pos+3) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    str +="4 " + to_string(pos+3) + " " + to_string(pos+7) + " " + to_string(pos+6) + " " + to_string(pos+2) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    str += "4 " + to_string(pos+1) + " " + to_string(pos+2) + " " + to_string(pos+6) + " " + to_string(pos+5) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    cont++;
                }
            }
        }
    }

    f_out << str;
    f_out.close();
}
