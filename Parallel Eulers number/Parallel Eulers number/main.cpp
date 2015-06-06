#include <iostream>
#include "Factorials.h"



int main()
{
    int nb = 1, power = 100000000;
    mpf_t n;
    mpf_init_set_ui(n,nb);

    mpf_t * arr = new mpf_t[20];
    for (int i = 1; i <= power; ++i)
    {
        mpf_mul_ui(n,n,i);
    }
    mpf_out_str(stdout, 10, 10, n);
    std::cout << std::endl;

  //  mpf_clear(n);

    // Creates a float-point number
    mpf_t floatNumber;
    // Initialize it with value 0.
    mpf_init(floatNumber);
    mpf_set_ui(floatNumber, 1);


    mpf_t res;
    mpf_init(res);


   // mpf_out_str(stdout, 10, 30, floatNumber);
  //  std::cout << std::endl;

    mpf_div(floatNumber, floatNumber, n);

    std::cout << std::endl;
    mpf_out_str(stdout, 10, 10, floatNumber);
    std::cout << std::endl;

    mpf_clear(floatNumber);
    mpf_clear(res);
    return 0;
}
