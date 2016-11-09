#include "System.h"

// all time constants are defined empirically

inline void DelayCycl(unsigned int c){
    unsigned int c_count;

    c = (unsigned int)(c/2);

    for(c_count = 0 ; c_count <= c ; c_count++);
}

inline void DelayMs(unsigned int m){
    unsigned int m_count;
    #define MS_CONST ((unsigned int)(SYS_CLK/1000))

    m = (unsigned int)(m*(MS_CONST/4));

    for(m_count = 0 ; m_count <= m ; m_count++);
}

inline void DelayUs(unsigned int u){
    unsigned int u_count;
    #define US_CONST ((unsigned int)(SYS_CLK/1000000))

    u = (unsigned int)(u*(US_CONST/4));

    for(u_count = 0 ; u_count <= u ; u_count++);

}
