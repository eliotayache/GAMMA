/*
* @Author: eliotayache
* @Date:   1020-05-05 10:06:26
* @Last Modified by:   Eliot Ayache
* @Last Modified time: 2020-07-22 16:59:10
*/

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "environment.h"
#include "simu.h"
#include "err.h"
#include "mpisetup.h"

void chbindir(const char binPath[]);

int main(int argc, char *argv[]){

    int status;
    Simu simu;

    chbindir(argv[0]);
    mpi_init(&argc, &argv);
    checkEnvironment();

    status = simu.initialise();
    status = simu.run();

    mpi_finalise();
    return 0;

}

void chbindir(const char binPath[]){

    char pathCopy[300];
    int status = 0;

    strcpy(pathCopy, binPath); 
    status = chdir(dirname(pathCopy));
    if (status == -1) throw StartupFileManagementException();
    return;
    
}