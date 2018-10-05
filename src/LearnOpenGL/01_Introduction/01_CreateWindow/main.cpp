#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main(int argc,char** argv)
{
	osgViewer::Viewer viewer;

    viewer.addEventHandler(new osgViewer::StatsHandler);

    return viewer.run();
}