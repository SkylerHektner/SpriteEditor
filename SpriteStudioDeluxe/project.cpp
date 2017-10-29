#include "project.h"
#include "resizablearray.h"

Project::Project(int x, int y, int startframes = 1)
{
    frames(startframes);
    for(unsigned i = 0; i < startframes; i++)
    {
        frames.additem(Frame(x, y));
    }
}

Project::~Project()
{

}
