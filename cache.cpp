#include "cache.h"
#include <stdlib.h>
#include <sstream>

using namespace std;


int main (int argc, char *argv[])
{
    if (argc!=4)
    {
        cout << "No son suficientes argumentos, 4 necesitados: [asociatividad, tamano_cache, tamano_bloque, tamano_memoria]. "<< argc << " argumentos dados.\n";
        return 0;
    }
     string asociatividad;
     int tamano_cache, tamano_bloque;  
      asociatividad = argv[1]; 
      tamano_cache = atoi(argv[2]);
      tamano_bloque = atoi(argv[3]);
      stringstream str;
    
      str << asociatividad[0];

      int a;
      str >> a;
	
	if(a!=1){
        Cache_Asoc cache(a,tamano_cache,tamano_bloque);
	string dir;
        string direccion;
	int col = cache.n_ways*cache.tamano_bloque+1;
     
      long linea_cache[cache.n_sets][col];
      cout << "________________________________________________________________________________" << endl;
     //___________________________________________________________________________
     // RELLENO EL CACHE 
	for(int j = 0; j<cache.n_sets;j++)
		{
		    for (int i = 0; i < col; i++){ //se guarda n veces dato para el mismo 'key', dada la asociatividad			
			linea_cache[j][i] = 0; //set valid bit a cero
			}  
		}
	
	ifstream ficheroEntrada;	
	ficheroEntrada.open ( "aligned.trace" , ios::in);

	       if (ficheroEntrada.is_open()) {
         while (! ficheroEntrada.eof() ) {
         getline (ficheroEntrada,dir);     
	//___________________________________________________________________________
	//OBTENGO EL TAG Y EL INDEX	
		int i2 =0;
		direccion = "";
		while(dir[i2]!=' ')
		{
			direccion+=cache.decodificador(dir[i2]);
			i2++;
		}
		if(direccion.size()==28)
		direccion="0000"+direccion;
      		long index;
		long tag;
		string s = "";		
		//TOMO EL INDEX DE LA DIRECCION DADA
		for(int k = 0; k< cache.tamano_tag/*32-tamano_offset-tamano_index*/;k++)
		{
			s+=direccion[k];
		}
		tag = cache.decodificar_decimal(s, s.size());		
		s = "";

		for(int i = cache.tamano_tag; i < 32-cache.tamano_offset ; i++)
		{
			s+=direccion[i];
		}
		index= cache.decodificar_decimal(s, s.size());
	//______________________________________________________________________________________________
       // HAGO LA LOGICA PARA MISSES Y HIT DEL CACHE, CON SUSTITUCION ALEATORIA
		srand(time(0));
		int r;
		for(int i = 0; i < col; i=i+1)
		{
			if((linea_cache[index][col-1]==1) && (linea_cache[index][i]==tag))
			{
				cache.hit++;
				break;
		
			}else{//No habia nada en esa posicion, la instrucion se trae al cache y se pone el valid bit en 1
 			if(i==(col-1)){
			cache.miss++;
						
			r = (rand())%(cache.n_ways);
			r = cache.tamano_bloque*r;

			for (int z = r; z < r+cache.tamano_bloque; z=z+1){
			linea_cache[index][z] = tag;
			if(z == col-2)
			linea_cache[index][z+1] = 1;   //set valid bit a 1 
			} 	
			}
			}
		}
} //AQUI ESTAN LINEAS QUE TERMINAN EL WHILE SADICO
}
		cache.miss = cache.miss-1;
		double miss_rate = (double)cache.miss/((double)(cache.miss+cache.hit));
		 cout << "MISSES: " << (cache.miss)<< " HITS: " << cache.hit <<endl;
		 cout << "Miss rate = " << miss_rate << endl;

return 0;
}else{

Directo d1;
   d1.setAtributos(asociatividad,tamano_cache,tamano_bloque );
   d1.getDatos();
//___________________________________________________________________________________________________________________
//Se crea cache con el tamano indicado por el index
   //Se llena inicialmente  de ceros
   int numero_filas=d1.getNumero_filas();
   int columnas =tamano_bloque+1;
   int cache[numero_filas][columnas];//crea un cache con el numero de filas determinado
   int x,y;
   for (x=0;x<=numero_filas;x++) { //asigna el bit value =0 para el estado inicial del cache
     for(y=0;y<columnas;y++){
     }
     cache[x][columnas-1]=0;
    }
  std::cout << "________________________________________________________________________________" << std::endl;
//___________________________________________________________________________________________________________________
//Se lee las direcciones
  ifstream ficheroEntrada;
  string instruccion_full;
  string::iterator it;
  string::iterator it2;
  string instruccion_hexa="";
  string instruccion_bin="";
  string bin="";
  unsigned long int miss=0;
  unsigned long int hit=0;
  ficheroEntrada.open ( "aligned.trace" , ios::in);
  if (ficheroEntrada.is_open()) {
    while (! ficheroEntrada.eof() ) {
      int n=0;
      getline (ficheroEntrada,instruccion_full);
        for(it=instruccion_full.begin();it<=instruccion_full.end();it++){//recorre la instrucion
          if(*(it)!='L' && *(it)!='S' && *(it)!=' ' ){
              instruccion_hexa=instruccion_hexa + *it;//recorre la linea para devolver la instrucion en hexadecimal
//n++;
            }
    }
    for(it2=instruccion_hexa.begin();it2<=instruccion_hexa.end();it2++){
    char c=*it2;
     instruccion_bin= instruccion_bin+ d1.decodificador(c);//devuelve la instrucion en binario
   
    }
  //Se optienen index tag y offet en binario
    string tag2,index2,offset2;
    tag2=d1.getTAG_bin(instruccion_bin);
    index2=d1.getINDEX_bin(instruccion_bin);
    offset2=d1.getOFFSET_bin(instruccion_bin);
//___________________________________________________________________________________________________________________________________
//Se pasan las instrucciones a decimal
int tag10,index10,offset10;
int tamano_tag;
tamano_tag=d1.getTAMANO_tag();
int tamano_offset=d1.getTAMANO_offset();
int tamano_index=d1.getTAMANO_index();
tag10=d1.decodificar_decimal(tag2, tamano_tag);
index10=d1.decodificar_decimal(index2, tamano_index);
offset10=d1.decodificar_decimal(offset2,tamano_offset);
//____________________________________________________________________________________________________________________________________________
//Se analizan las direcciones
if(cache[index10][columnas-1]==1){// habia un dato valido se debe comparar si es igual
  if(cache[index10][offset10]==tag10){
   hit++;
  }else{
   int z;
   for (z=0;z<tamano_bloque;z++){
   cache[index10][z]=tag10;
  }
   miss++;
  }

}else{//No habia nada en esa posicion, la instrucion se trae al cache y se pone el valid bit en 1
 miss++;
int v;
 for (v=0;v<tamano_bloque;v++){
 cache[index10][v]=tag10;
}
cache[index10][columnas-1]=1;
}
//____________________________________________________________________________________________________________________________________________

instruccion_hexa="";
instruccion_bin="";

  }
  if(ficheroEntrada.eof()){
   // std::cout << "Final del archivo" << std::endl;
  }
  miss= miss-1;

  int miss_rate = miss/(hit+miss);
  cout << "HITS = " <<hit<< endl;
  cout << "MISSES = " <<miss<< endl;
  cout << "Miss rate = "<< miss_rate <<endl;
   
 ficheroEntrada.close();
  }
  else{
  cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
}


return 0;
}


}
