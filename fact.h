#ifndef _fact_h
#define _fact_h

#include "bigint/bigint.h"
//setting up template
template <typename T> T factorial(T n) {

    if(n == 1){
        return 1;
    }else{
        return n * factorial(n - 1);
      }

}


#endif
