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
#include <osg/Material>
#include <osgDB/ReadFile>

osg::Geode * GenQuad(osg::Vec3Array const * pos,
	osg::Vec4Array const * color = NULL,
	osg::Vec2Array const * texc = NULL,
	osg::Vec3Array const * normal = NULL) {
	//------------
	osg::Geode * geode = new osg::Geode;
	osg::Geometry* quad = new osg::Geometry;
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	geode->addDrawable(quad);
	//------------
	quad->setVertexArray(new osg::Vec3Array(*pos));

	if (color != NULL) {
		quad->setColorArray(new osg::Vec4Array(*color));
		quad->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);
	}

	if (texc != NULL)
		quad->setTexCoordArray(0, new osg::Vec2Array(*texc));

	if (normal != NULL) {
		quad->setNormalArray(new osg::Vec3Array(*normal));
		quad->setNormalBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);
	}
	//------------
	quad->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pos->size()));
	return geode;
}

osg::Group * GenCube() {
	osg::Group * cube = new osg::Group;
	//------------
	osg::ref_ptr<osg::Vec3Array> pos = new osg::Vec3Array;
	pos->push_back(osg::Vec3(-0.5f, 0, -0.5f));
	pos->push_back(osg::Vec3(0.5f, 0, -0.5f));
	pos->push_back(osg::Vec3(0.5f, 0, 0.5f));
	pos->push_back(osg::Vec3(-0.5f, 0, 0.5f));
	//------------
	osg::ref_ptr<osg::Vec2Array> texc = new osg::Vec2Array;
	texc->push_back(osg::Vec2(0, 0));
	texc->push_back(osg::Vec2(1.0f, 0));
	texc->push_back(osg::Vec2(1.0f, 1.0f));
	texc->push_back(osg::Vec2(0, 1.0f));
	//------------
	osg::Geode * square = GenQuad(pos, NULL, texc);
	//------------
	int num = 6;
	std::vector<osg::Matrix> tfs(num);
	tfs[0] = osg::Matrix::translate(0, -0.5f, 0);
	tfs[1] = osg::Matrix::rotate(0.5f*osg::PI, osg::Vec3(0, 0, 1.0f)) * osg::Matrix::translate(0.5f, 0, 0);
	tfs[2] = osg::Matrix::rotate(1.0f*osg::PI, osg::Vec3(0, 0, 1.0f)) * osg::Matrix::translate(0, 0.5f, 0);
	tfs[3] = osg::Matrix::rotate(1.5f*osg::PI, osg::Vec3(0, 0, 1.0f)) * osg::Matrix::translate(-0.5f, 0, 0);
	tfs[4] = osg::Matrix::rotate(0.5f*osg::PI, osg::Vec3(1.0f, 0, 0)) * osg::Matrix::translate(0, 0, -0.5f);
	tfs[5] = osg::Matrix::rotate(1.5f*osg::PI, osg::Vec3(1.0f, 0, 0)) * osg::Matrix::translate(0, 0, 0.5f);
	//------------
	std::vector<osg::Texture2D *> texs(num, NULL);
	std::string imgNames[] = {
		"Images/rockwall.png",
		"Images/warp_test.bmp",
		"Images/skymap.jpg",
		"Images/IMG_0055.jpg",
		"Images/tex_line.bmp",
		"Images/tex_stone.bmp"
	};
	for (int i = 0; i < num; i++) {
		osg::ref_ptr<osg::Image> image = osgDB::readImageFile(imgNames[i]);
		if (!image.valid()) {
			osg::notify(osg::FATAL) << "Unable to load data file. Exiting." << std::endl;
			return(NULL);
		}
		texs[i] = new osg::Texture2D(image);
		texs[i]->setUnRefImageDataAfterApply(true);
	}
	//------------
	std::vector<osg::MatrixTransform *> squares(num, NULL);
	for (int i = 0; i < squares.size(); i++) {
		squares[i] = new osg::MatrixTransform(tfs[i]);
		squares[i]->addChild(square);
		// After creating the OpenGL texture object, release the
		//   internal ref_ptr<Image> (to delete the Image).
		squares[i]->getOrCreateStateSet()->setTextureAttributeAndModes(0, texs[i]);
		cube->addChild(squares[i]);
	}
	//------------
	return cube;
}

osg::Geode * GenRect() {
	osg::ref_ptr<osg::Vec3Array> pos = new osg::Vec3Array;
	pos->push_back(osg::Vec3(-0.5f, 0, -0.5f));
	pos->push_back(osg::Vec3(0.5f, 0, -0.5f));
	pos->push_back(osg::Vec3(0.5f, 0, 0.5f));
	pos->push_back(osg::Vec3(-0.5f, 0, 0.5f));
	//------------
	osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
	color->push_back(osg::Vec4(1.0f, 0, 0, 1.0f));
	color->push_back(osg::Vec4(0, 1.0f, 0, 1.0f));
	color->push_back(osg::Vec4(0, 0, 1.0f, 1.0f));
	color->push_back(osg::Vec4(1.0f, 1.0f, 0, 1.0f));
	//------------
	osg::Geode * rect = GenQuad(pos, color);
	//------------
	return rect;
}

void AddLight(osg::Group * root,
	osg::Vec3 const * pos = NULL,
	osg::Vec3 const * dir = NULL,
	osg::Vec4 const * color = NULL,
	size_t channel = 0) {
	osg::StateSet * states = root->getOrCreateStateSet();
	states->setMode(GL_LIGHT0 + channel, osg::StateAttribute::ON);
	osg::Matrix m(osg::Matrix::translate(pos==NULL? osg::Vec3(0,0,0) : *pos));
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform(m);
	//------------Create a mostly red light
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setLightNum(channel);
	light->setPosition(osg::Vec4(0, 0, 0, 1.0f));
	light->setDirection(dir == NULL ? osg::Vec3(0, 0, -1.0f) : *dir);
	light->setAmbient((color == NULL ? osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f): *color)*0.5f);
	light->setDiffuse(color == NULL ? osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) : *color);
	light->setSpecular(color == NULL ? osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) : *color);
	//------------
	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
	ls->setLight(light);
	mt->addChild(ls);
	root->addChild(mt);
}

osg::Geode * GenSphere(size_t n) {
	osg::ref_ptr<osg::Vec3Array> pos = new osg::Vec3Array;
	std::vector<std::vector<osg::Vec3> > ij2pos(n+1, std::vector<osg::Vec3>(n+1));
	//------------
	float inc = 1.0f / n;
	for (int i = 0; i <= n; i++) {
		float u = inc * i;
		for (int j = 0; j <= n; j++) {
			float v = inc * j;
			float theta = osg::PI * u;
			float phi = 2 * osg::PI * v;
			ij2pos[i][j].x() = sinf(theta) * cosf(phi);
			ij2pos[i][j].y() = sinf(theta) * sinf(phi);
			ij2pos[i][j].z() = cosf(theta);
		}
	}
	//------------
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pos->push_back(ij2pos[i][j]);
			pos->push_back(ij2pos[i+1][j]);
			pos->push_back(ij2pos[i+1][j+1]);
			pos->push_back(ij2pos[i][j+1]);
		}
	}
	//------------
	osg::Geode * sphere = GenQuad(pos, NULL, NULL, pos);
	//------------
	sphere->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::ON |
		osg::StateAttribute::PROTECTED);
	//------------
	osg::ref_ptr<osg::Material> mat = new osg::Material;
	mat->setDiffuse(osg::Material::FRONT,
		osg::Vec4(0.5f, 0.5f, 0.5f, 1.0f));
	mat->setSpecular(osg::Material::FRONT,
		osg::Vec4(0.5f, 0.5f, 0.5f, 1.0f));
	mat->setShininess(osg::Material::FRONT, 16.0f);
	sphere->getOrCreateStateSet()->setAttribute(mat);
	//------------
	AddLight(sphere, &osg::Vec3(-0.5f, -1.2f, 0), &osg::Vec3(0.5f, 1.2f, 0), &osg::Vec4(1.0f, 0, 0, 0), 0);
	AddLight(sphere, &osg::Vec3(0.5f, -1.2f, 0), &osg::Vec3(-0.5f, 1.2f, 0), &osg::Vec4(0, 1.0f, 0, 0), 1);
	//------------
	return sphere;
}

osg::Group * GenScene() {
	osg::Group * scene = new osg::Group();
	osg::MatrixTransform * left = new osg::MatrixTransform(osg::Matrix::translate(-3.0f, 0, 0));
	osg::MatrixTransform * right = new osg::MatrixTransform(osg::Matrix::translate(3.0f, 0, 0));
	osg::MatrixTransform * copy = new osg::MatrixTransform(osg::Matrix::translate(0.5f, 0.5f, 0.5f));
	//------------
	osg::Group * rectGroup = new osg::Group();
	osg::Geode * rect = GenRect();
	copy->addChild(rect);
	copy->getOrCreateStateSet()->setAttributeAndModes(new osg::CullFace());
	rectGroup->addChild(copy);
	rectGroup->addChild(rect);
	//------------
	right->addChild(rectGroup);
	left->addChild(GenCube());
	//------------
	scene->addChild(left);
	scene->addChild(right);
	scene->addChild(GenSphere(40));
	//------------
	return scene;
}

int main(int argc,char** argv)
{
	osgViewer::Viewer viewer;

    viewer.addEventHandler(new osgViewer::StatsHandler);

	viewer.setSceneData(GenScene());

    return viewer.run();
}