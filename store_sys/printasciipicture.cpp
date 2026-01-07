#include "printasciipicture.h"
void printasciipicture::print(const char* filename)
{
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, filename, "rt");
    if (filename == "Start.tmg")
    {
        system("mode con cols=180");
    }
    else
    {
        system("mode con cols=80");
    }

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        std::cout << print_temp;
    }
    fclose(fp);
}