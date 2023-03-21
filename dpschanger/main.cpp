#include <fstream>
#include <iostream>
#include <Windows.h>
#include <time.h>

int main(int argc, char* argv[])
{
    /* check path */
    if (!argv[1])
    {
        std::cout << "invalid specified path\n";
        getchar();
        return 1;
    }

    std::cout << "Writing " << argv[1];
    std::fstream file(argv[1], std::ios::binary | std::ios::in | std::ios::out);

    /* check file */
    if (!file) {
        std::cout << "failed to open file";
        getchar();
        return 1;
    }

    /* DOS Header */
    IMAGE_DOS_HEADER dosHeader;
    file.read((char*)(&dosHeader), sizeof(dosHeader));
    if (dosHeader.e_magic != IMAGE_DOS_SIGNATURE) {
        file.close();
        std::cout << "invalid DOS header";
        getchar();
        return 1;
    }

    // offsets to timestamp location
    file.seekp(sizeof(unsigned short) * 2 + sizeof(unsigned long) + dosHeader.e_lfanew, 0);

    // patch file
    file.write((char*)new unsigned long(time(0)), sizeof(unsigned long));

    // Close the file
    file.close();

    std::cout << "\nFile patched";
    getchar();
}
