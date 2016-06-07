#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cerrno>
#include <iostream>
#include <vector>

#include "Tiles.h"
#include "Board.h"

class Loader
{
    public:
        Loader(std::string filename);
        std::string get_file_contents(std::string filename);
        std::vector<std::vector<int> > get_board();
        int get_color_num(int color);
    private:
        std::string locations;
        int greenAmount;
        int orangeAmount;
        int blueAmount;
        int redAmount;
        int yellowAmount;
        int violetAmount;
        int whiteAmount;
        int purpleAmount;
        int pinkAmount;
        std::vector<std::vector<int> > board;
        std::vector<std::string> explode(std::string const & s, char delimeter);

};

#endif // LOADER_H
