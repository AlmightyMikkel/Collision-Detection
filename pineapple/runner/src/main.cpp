// main.cpp

#include "application.hpp"

int main(int argc, char **argv)
{
   srand((unsigned int)time(NULL));
   runner::Application{}.run();
   return 0;
}
