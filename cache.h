#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <tgmath.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <ctime>
#include <new> 


using namespace std;

class Cache{
public:
  int n_ways;
  int n_sets;
  int tamano_cache;
  int tamano_bloque;
  int tamano_offset;
  int tamano_tag; 
  int tamano_index;
  int n_bloques;
  int tamano_memoria=4194304; //Corresponde a una memoria de  4GB 
  string asociatividad;

  void setAtributos(string asociatividad0, int tamano_cache0, int tamano_bloque0)
 {
  asociatividad = asociatividad0;
  tamano_cache = tamano_cache0;
  tamano_bloque= tamano_bloque0;
  //tamano_memoria=tamano_memoria0;
 }


//Se decodifica la direccion de hexadecimal a binario
  string decodificador(char c)
        {	
	switch(c)
        {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
	case 'a': return "1010";
        case 'b': return "1011";
        case 'c': return "1100";
        case 'd': return "1101";
        case 'e': return "1110";
        case 'f': return "1111";
	default: return "";
        }
        } 
	int getTAMANO_tag(){
        return tamano_tag;
          }

};

class Cache_Asoc:public Cache{
  public:
	
	int hit;
	int miss;
//Se reciben los datos dados por el usuario y se crea cache de esta forma
	Cache_Asoc(int asociatividad, int tamano_cache, int tamano_bloque)
  	{ 
	this->n_ways = asociatividad;
	this->tamano_cache = tamano_cache;
	this->tamano_bloque = tamano_bloque;

	this->tamano_offset = (int)(log(double(this->tamano_bloque))/log(2));
	this->n_bloques = (this->tamano_cache)*1024/(this->tamano_bloque);
	this->n_sets = (this->n_bloques)/(this->n_ways);
	this->tamano_index = (int)((log(double(this->n_sets))/log(2)));
	this->tamano_tag = 32-this->tamano_index-this->tamano_offset; 
	this->hit = 0;
	this->miss = 0;

	cout << "tamano_memoria=" <<tamano_memoria<<" (KB)"<< endl;
	cout << "tamano_cache=" <<tamano_cache<< endl;
//	cout << "tamano_cacheKB=" <<tamano_cacheKB<< endl;
	//cout << "asociatividad=" <<asociatividad<< endl;
	cout << "n_bloques=" <<n_bloques<< endl;
	cout << "n_sets=" << n_sets <<endl;
	//cout << "total_bits=" <<total_bits<< endl;
	cout << "tamano_bloque=" <<tamano_bloque<< endl;
	cout << "tamano_offset=" <<tamano_offset<< endl;
	cout << "tamano_index=" <<tamano_index<< endl;
	cout << "tamano_tag=" << tamano_tag<< endl;
  	}

//Se reciben bits en string y devuelve su valor en decimal
	int decodificar_decimal(string binario, int tamano)
	{
	string::iterator iterador4;
	string codificado;
	codificado=binario;
	int exponente=tamano-1;
	int valor_decimal=0;
	for(iterador4=codificado.begin(); iterador4<codificado.end();iterador4++){
	int base;
	if(exponente>=0){
	if(*(iterador4)=='0'){
	base = 0;
	}else{
	  base=2;
	}
	int suma;
	if (*(iterador4)=='0' && exponente==0){
	  suma=0;
	}else{
	  suma= pow(base,exponente);
	}
	valor_decimal= valor_decimal + suma ;
	exponente--;

	}
	}
	return valor_decimal;
	}

	
};

// Se declara una clase para el mapeo directo
class Directo:public Cache{
public:
void getDatos(){
  tamano_memoria;
  int tamano_cacheKB= tamano_cache*1024;
  n_bloques=tamano_cacheKB/tamano_bloque;
  int n_palabaras=tamano_bloque/4;
  tamano_offset=log2(tamano_bloque);
  tamano_index=log2(n_bloques);
  int total_bits= log2(tamano_memoria)+10;
  tamano_tag=(total_bits - tamano_index - tamano_offset);

cout << "tamano_memoria=" <<tamano_memoria<<" (KB)"<< endl;
cout << "tamano_cache=" <<tamano_cache<< endl;
//cout << "tamano_cacheKB=" <<tamano_cacheKB<< endl;
//cout << "asociatividad=" <<asociatividad<< endl;
cout << "n_bloques=" <<n_bloques<< endl;
//cout << "total_bits=" <<total_bits<< endl;
cout << "tamano_bloque=" <<tamano_bloque<< endl;
cout << "tamano_offset=" <<tamano_offset<< endl;
cout << "tamano_index=" <<tamano_index<< endl;
cout << "tamano_tag=" << tamano_tag<< endl;
}
int getTAMANO_index(){
    return tamano_index;
  }
int getTAMANO_offset(){
    return tamano_offset;
  }
int getNumero_filas(){
return n_bloques;
  }

string getTAG_bin(string bin){
string tag="";
int cuenta= 31;
string::iterator iterador0;
string Bin=bin;
for(iterador0=Bin.begin();iterador0<Bin.end();iterador0++){

//std::cout << "" <<cuenta<< std::endl;
if(cuenta>(31-tamano_tag)){
tag=tag+*(iterador0);
}
cuenta--;
}
return tag;
}
string getINDEX_bin(string bin0){
string  index_2="";
string Bin0;
Bin0=bin0;
int cuenta= 31;
string::iterator iterador1;
for(iterador1=Bin0.begin();iterador1<Bin0.end();iterador1++){
  if(cuenta<=(31-tamano_tag)&&cuenta>>(31-tamano_tag-tamano_index)){
  index_2=index_2 + *(iterador1);

  }
cuenta--;
}
return index_2;
}
string getOFFSET_bin(string bin1){
string offset="";
string Bin1=bin1;
int cuenta= 31;
string::iterator iterador2;
for(iterador2=Bin1.begin();iterador2<Bin1.end();iterador2++){
  if (cuenta<=(31-tamano_tag-tamano_index)) {
    offset=offset+*(iterador2);
  }
cuenta--;

}
return offset;
}

//Se reciben bits en string y devuelve su valor en decimal
int decodificar_decimal(string binario, int tamano){
string::iterator iterador4;
string codificado;
codificado=binario;
int exponente=tamano-1;
int valor_decimal=0;
for(iterador4=codificado.begin(); iterador4<codificado.end();iterador4++){
int base;
if(exponente>=0){
if(*(iterador4)=='0'){
base = 0;
}else{
  base=2;
}
int suma;
if (*(iterador4)=='0' && exponente==0){
  suma=0;
}else{
  suma= pow(base,exponente);
}
/*cout<<"iterador="<<*(iterador4)<<endl;
cout<<"base="<<base<<endl;
cout<<"exponente="<<exponente<<endl;
cout<<" suma= "<<suma<<endl;
*/

valor_decimal= valor_decimal + suma ;
exponente--;

}
}
return valor_decimal;
}

};
