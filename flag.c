/*
 * flag.c
 *
 *  Created on: Jan 29, 2018
 *      Author: imashio
 */

unsigend int    flag=0;

void set_flag(){
    flag = 1;
}

unsigned int read_flag(){
    return flag;
}
