#include <iostream>
#include <array>

//Maybe use vector or std::array instead of [][]
using namespace std;

struct coord{
    int x;
    int y;
};

struct sprite{
    coord coordinates;
    int len;
    int height;
};

void update(int dist, int *display[64][64])
{

}

void initialise(array<array<int, 64>, 64> &display, sprite &obj)
{
    for(int i = 0; i < 64; i++)
    {
        for(int j = 0; j < 64; j++)
        {
            if(i == obj.coordinates.x && j == obj.coordinates.y)
            {
                for(int p = 0; p < obj.len; p++)
                {
                    for(int q = 0; q < obj.height; q++)
                    {
                        display[i+p][j+q] = 1;
                    }
                }
            }
            else if(display[i][j] != 1)
            {
                display[i][j] = 0;
            }
        }
    }
}

void printDisplay(array<array<int, 64>, 64> &display)
{
    for(int i = 0; i < 64; i++)
    {
        for(int j = 0; j < 64; j++)
        {
            cout << display[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Hello world!" << endl;

    sprite spr;
    coord crd;
    crd.x = 8;
    crd.y = 8;
    spr.coordinates = crd;
    spr.height = 8;
    spr.len = 8;

    array<array<int, 64>, 64> disArray;
    initialise(disArray, spr);

    printDisplay(disArray);
    return 0;
}
