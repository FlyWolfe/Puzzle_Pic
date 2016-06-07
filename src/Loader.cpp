#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cerrno>
#include <iostream>
#include <vector>
#include <utility>

#include "Loader.h"
#include "Tiles.h"
#include "Board.h"

Loader::Loader(std::string filename)
{
    locations = get_file_contents(filename);
}

std::string Loader::get_file_contents(std::string filename)
{
  std::string contents;
  std::ifstream file(filename);
  std::string curLine;
  std::vector<std::vector<int> > boardContent;
  int i = 0;
  int j = 0;
  int amount0 = 0;
  int amount1 = 0;
  int amount2 = 0;
  int amount3 = 0;
  int amount4 = 0;
  int amount5 = 0;
  int amount6 = 0;
  int amount7 = 0;
  int amount8 = 0;
  while (std::getline(file, curLine)) {
    contents = contents + curLine + "\n";
    int curNum = 0;
    std::vector<std::string> lineContent = explode(curLine, ',');

    boardContent.push_back(std::vector<int>());

    for (int n = 0; n < lineContent.size(); n++) {
      curNum = atoi(lineContent[n].c_str());
      boardContent[i].push_back(curNum);
      //std::cerr << ":";
      //std::cerr << curNum;
      //std::cerr << ",";
      j++;
      switch(curNum){
			case 0:
				amount0++;
			break;
			case 1:
				amount1++;
			break;
			case 2:
				amount2++;
			break;
			case 3:
				amount3++;
			break;
			case 4:
				amount4++;
			break;
			case 5:
				amount5++;
			break;
			case 6:
				amount6++;
			break;
			case 7:
				amount7++;
			break;
			case 8:
				amount8++;
			break;
			default:
			std::cerr << "NOT A VALID COLOR" << std::endl;
			break;
      }
    }
  i++;
  //std::cerr << "\n";
  }
  //std::cerr << "\n";
  std::cerr << contents;
  this->board = boardContent;
  this->greenAmount = amount0;
  this->orangeAmount = amount1;
  this->blueAmount = amount2;
  this->redAmount = amount3;
  this->yellowAmount = amount4;
  this->violetAmount = amount5;
  this->whiteAmount = amount6;
  this->purpleAmount = amount7;
  this->pinkAmount = amount8;
  return contents;
}

std::vector<std::vector<int> > Loader::get_board(){
    return board;
}

int Loader::get_color_num(int color) {
  switch(color){
    case 0:
        return greenAmount;
    break;
    case 1:
        return orangeAmount;
    break;
    case 2:
        return blueAmount;
    break;
    case 3:
        return redAmount;
    break;
    case 4:
        return yellowAmount;
    break;
    case 5:
        return violetAmount;
    break;
    case 6:
        return whiteAmount;
    break;
    case 7:
        return purpleAmount;
    break;
    case 8:
        return pinkAmount;
    break;
    default:
    std::cerr << "NOT A VALID COLOR" << std::endl;
    break;
  }
}

std::vector<std::string> Loader::explode(std::string const & s, char delimeter) {
  std::vector<std::string> returnString;
  std::istringstream iss(s);

  for (std::string token; std::getline(iss, token, delimeter); ) {
    returnString.push_back(std::move(token));
  }

  return returnString;
}
