#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateAttribute>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>

osg::Geode * GenTriangle() {
	osg::Geode * geode = new osg::Geode;
	osg::Geometry* geom = new osg::Geometry;
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	geode->addDrawable(geom);

	osg::Vec3Array * v = new osg::Vec3Array;
	v->push_back(osg::Vec3(-0.5f, 0, -0.5f));
	v->push_back(osg::Vec3(0.5f, 0, -0.5f));
	v->push_back(osg::Vec3(0, 0, 0.5f));
	geom->setVertexArray(v);

	osg::Vec4Array * c = new osg::Vec4Array;
	c->push_back(osg::Vec4(1.0f, 0, 0, 1.0f));
	c->push_back(osg::Vec4(0, 1.0f, 0, 1.0f));
	c->push_back(osg::Vec4(0, 0, 1.0f, 1.0f));
	geom->setColorArray(c);
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
	return geode;
}

int main(int argc,char** argv)
{
	osgViewer::Viewer viewer;

    viewer.addEventHandler(new osgViewer::StatsHandler);

	viewer.setSceneData(GenTriangle());

    return viewer.run();
}