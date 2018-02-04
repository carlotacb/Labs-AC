#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

struct directa {
    
    int tag;
    int validesa;
    
};

struct directa cache[128];

int aciertos;
int fallos;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache () {
	/* Escriu aqui el teu codi */
    
    int i;
    
    for (i = 0; i < 128; ++i) {
    
        cache[i].validesa = 0; // false
    }
    
    aciertos = 0;
    fallos = 0; 

}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address, unsigned int LE) {
    
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

    unsigned int adr = address;
    
	/* Escriu aqui el teu codi */

    miss = 0; // false
    replacement = 0; // false
    tag_out = -1;
    lec_mp = 0; 
    esc_mp = 0; 
    mida_esc_mp = 0;
    mida_lec_mp = 0;

    byte = adr & 31;
    bloque_m = adr >> 5;
    linea_mc = adr & 4064;
    linea_mc = linea_mc >> 5;
    tag = adr >> 12;

    
   // printf("%d\n", cache[linea_mc].tag);

    if (!LE) { // Es lectura
        
        
        esc_mp = 0;
        mida_esc_mp = 0;        
        
        
        if (cache[linea_mc].validesa != 0 && cache[linea_mc].tag != tag) {
            lec_mp = 1; // true
            miss = 1; // true
            replacement = 1; // true
            tag_out = cache[linea_mc].tag;
            cache[linea_mc].tag = tag;
            mida_lec_mp = 32;
            ++fallos;
            
            //printf("%d\n", cache[linea_mc].tag);
            //printf("%d\n", tag_out);
        }
    
        else if (cache[linea_mc].validesa == 0) {
            lec_mp = 1; // true
            miss = 1; // true
            replacement = 0; // false
            cache[linea_mc].tag = tag;
            cache[linea_mc].validesa = 1;
            mida_lec_mp = 32;
            tag_out = -1;
            ++fallos;
            //printf("%d\n", cache[linea_mc].tag);
        }
    
        else {
            lec_mp = 0; // true
            miss = 0; // false
            replacement = 0; // false
            mida_lec_mp = 0;
            ++aciertos;
            
        }
        
        //printf(" Ha fet una lectura a: %d\n", cache[linea_mc].tag);
    }

    else { // Es escritura WRITE THROUGH + NO ALLOCATE
        
        //printf("Ha fet una escritura a: %d\n", cache[linea_mc].tag);
        
        lec_mp = 0; 
        mida_lec_mp = 0;
        esc_mp = 1; // true
        mida_esc_mp = 1; 
        replacement = 0; // false
        tag_out = -1;
        
        
        if (cache[linea_mc].validesa == 0) {
            miss = 1; // true
            ++fallos;
        }
        
        else  {
            
            if (cache[linea_mc].tag != tag) {
                miss = 1; // true
                ++fallos;
            }
            
            else { // HIT
                miss = 0; // false
                ++aciertos;
            }
            
        }
        
        //printf("Ha fet una escritura a: %d\n", cache[linea_mc].tag);
        
    }

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
    
  printf("HITS: %d MISS: %d\n",aciertos,fallos);
  
}
