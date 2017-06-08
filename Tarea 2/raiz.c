#include <math.h>
#include "raiz.h"


double raiz(Funcion f, void *ptr, double x0, double x1, double eps){
    double xm = (x0+x1)/2;
    double dx = x1-x0;
    if (dx < 0){
        dx = dx*(-1);
    }
    if (dx <= eps){
        return xm;
    }
    else{
        if (f(ptr, xm) * f(ptr, x0) > 0){
            return raiz(f, ptr, xm, x1, eps);
        }
        else{
            return raiz(f, ptr, x0, xm, eps);
        }
    }

}

double poli(void *ptr, double x){
    double *a = ptr;
    double length = a[0]; // n+1
    double res = 0;
    for (int h = 1; h <= length; h++){
        res += a[h] * pow(x, h-1);
    }
    return res;
}

double raiz_poli(double a[], int n, double x0, double x1, double eps){
    double aux[n+2];
    aux[0] = n+1;
    for (int j = 1; j<= n+1; j++){
        aux[j] = a[j-1];
    }
    return raiz(poli , aux, x0, x1, eps);
}

