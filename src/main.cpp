#include "exercises.h"

#define exercise 10

int main(int argc, char **argv)
{
    unsigned int code = 0;
    switch(exercise)
    {
        case 1:
            code = main1(argc, argv);
            break;
        case 2:
            code = main2(argc, argv);
            break;
        case 3:
            code = main3(argc, argv);
            break;
        case 4:
            code = main4(argc, argv);
            break;
        case 5:
            code = main5(argc, argv);
            break;
        case 6:
            code = main6(argc, argv);
            break;
        case 7:
            code = main7(argc, argv);
            break;
        case 8:
            code = main8(argc, argv);
            break;
        case 9:
            code = main9(argc, argv);
            break;
        case 10:
            code = main10(argc, argv);
            break;
    }
    return code;
}
