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
#include <osg/Callback>
#include <osgDB/ReadFile>

osg::Geode * GenQuad(osg::Vec3Array const * pos,
	osg::Vec4Array const * color = NULL,
	std::vector<osg::ref_ptr<osg::Vec2Array>> * texcs = NULL,
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

	if (texcs != NULL) {
		for(int i=0; i<texcs->size();i++)
			quad->setTexCoordArray(i, new osg::Vec2Array(*(texcs->at(i))));
	}

	if (normal != NULL) {
		quad->setNormalArray(new osg::Vec3Array(*normal));
		quad->setNormalBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);
	}
	//------------
	quad->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pos->size()));
	return geode;
}

template<typename T>
class SinCB : public osg::NodeCallback {
public:
	SinCB(const T & val, osg::Uniform * unf, float rate = 1.0f)
	: oriVal(val), unf(unf), rate(rate){
		angle = 0;
	}
	
	bool run(osg::Object *object, osg::Object *data) {
		unf->set(oriVal * (0.5f + 0.5f*sinf(angle)));
		angle += rate * osg::PI / 180;
		return traverse(object, data);
	}

private:
	T oriVal;
	float angle;
	float rate;
	osg::Uniform * unf;
};

osg::Geode * GenRect() {
	osg::ref_ptr<osg::Vec3Array> pos = new osg::Vec3Array;
	pos->push_back(osg::Vec3(-0.5f, 0, -0.5f));
	pos->push_back(osg::Vec3(0.5f, 0, -0.5f));
	pos->push_back(osg::Vec3(0.5f, 0, 0.5f));
	pos->push_back(osg::Vec3(-0.5f, 0, 0.5f));
	//------------
	osg::Geode * rect = GenQuad(pos);
	osg::Program * prog = new osg::Program();
	prog->addShader(osgDB::readShaderFile("Shaders/01_04_Shader.vs"));
	prog->addShader(osgDB::readShaderFile("Shaders/01_04_Shader.fs"));
	rect->getOrCreateStateSet()->setAttributeAndModes(prog);
	//------------
	float h = 1.0f;
	osg::Vec4 color(1.0f, 0, 0, 1.0f);
	osg::Uniform * unf0 = new osg::Uniform("h", h);
	osg::Uniform * unf1 = new osg::Uniform("color", color);
	rect->getOrCreateStateSet()->addUniform(unf0);
	rect->getOrCreateStateSet()->addUniform(unf1);
	rect->addUpdateCallback(new SinCB<float>(h, unf0));
	rect->addUpdateCallback(new SinCB<osg::Vec4>(color, unf1, 5.0f));
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
	osg::Matrix m(osg::Matrix::translate(pos == NULL ? osg::Vec3(0, 0, 0) : *pos));
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform(m);
	//------------Create a mostly red light
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setLightNum(channel);
	light->setPosition(osg::Vec4(0, 0, 0, 1.0f));
	light->setDirection(dir == NULL ? osg::Vec3(0, 0, -1.0f) : *dir);
	light->setAmbient((color == NULL ? osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) : *color)*0.5f);
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
	osg::ref_ptr<osg::Vec2Array> texc = new osg::Vec2Array;
	std::vector<std::vector<osg::Vec3> > ij2pos(n + 1, std::vector<osg::Vec3>(n + 1));
	std::vector<std::vector<osg::Vec2> > ij2uv(n + 1, std::vector<osg::Vec2>(n + 1));
	//------------
	float inc = 1.0f / n;
	for (int i = 0; i <= n; i++) {
		float u = inc * i;
		for (int j = 0; j <= n; j++) {
			float v = inc * j;
			float theta = osg::PI * u;
			float phi = 2 * osg::PI * v;
			ij2uv[i][j] = osg::Vec2(u, v);
			ij2pos[i][j].x() = sinf(theta) * cosf(phi);
			ij2pos[i][j].y() = sinf(theta) * sinf(phi);
			ij2pos[i][j].z() = cosf(theta);
		}
	}
	//------------
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pos->push_back(ij2pos[i][j]);
			pos->push_back(ij2pos[i + 1][j]);
			pos->push_back(ij2pos[i + 1][j + 1]);
			pos->push_back(ij2pos[i][j + 1]);
			texc->push_back(ij2uv[i][j]);
			texc->push_back(ij2uv[i + 1][j]);
			texc->push_back(ij2uv[i + 1][j + 1]);
			texc->push_back(ij2uv[i][j + 1]);
		}
	}
	std::vector<osg::ref_ptr<osg::Vec2Array>> texcs(2, texc);
	//------------
	osg::Geode * sphere = GenQuad(pos, NULL, &texcs, pos);
	//------------
	std::string imgName[] = {
		"Images/tex_line.bmp",
		"Images/warp_test.bmp"
	};
	for (int i = 0; i < 2; i++) {
		osg::Image * img = osgDB::readImageFile(imgName[i]);
		if (img == NULL) {
			osg::notify(osg::NotifySeverity::ALWAYS) << imgName[i] << " read fail." << std::endl;
			return NULL;
		}
		osg::Texture2D * tex = new osg::Texture2D(img);
		sphere->getOrCreateStateSet()->setTextureAttributeAndModes(i, tex);
		osg::Uniform * unf = new osg::Uniform((std::string("img")+char('0'+i)).c_str(), i);
		sphere->getOrCreateStateSet()->addUniform(unf);
	}
	//------------
	osg::Program * prog = new osg::Program();
	osg::Shader * vs = osgDB::readShaderFile("Shaders/01_04_Shader.vs");
	osg::Shader * fs = osgDB::readShaderFile("Shaders/01_04_Shader.fs");
	//if (vs == NULL || fs == NULL) {
	//	osg::notify(osg::NotifySeverity::ALWAYS) << "Shader read fail." << std::endl;
	//	return NULL;
	//}
	prog->addShader(vs);
	prog->addShader(fs);
	sphere->getOrCreateStateSet()->setAttributeAndModes(prog);
	//------------
	float h = 1.0f;
	osg::Vec4 color(1.0f, 1.0f, 0, 1.0f);
	osg::Uniform * unf0 = new osg::Uniform("h", h);
	osg::Uniform * unf1 = new osg::Uniform("color", color);
	sphere->getOrCreateStateSet()->addUniform(unf0);
	sphere->getOrCreateStateSet()->addUniform(unf1);
	sphere->addUpdateCallback(new SinCB<float>(h, unf0));
	sphere->addUpdateCallback(new SinCB<osg::Vec4>(color, unf1, 5.0f));
	//------------
	return sphere;
}

osg::Group * GenScene() {
	osg::Group * scene = new osg::Group();
	//------------
	scene->addChild(GenRect());
	osg::MatrixTransform * right = new osg::MatrixTransform(osg::Matrix::translate(2.0f, 0, 0));
	right->addChild(GenSphere(50));
	scene->addChild(right);
	return scene;
}

int main(int argc,char** argv)
{
	osgViewer::Viewer viewer;

    viewer.addEventHandler(new osgViewer::StatsHandler);

	viewer.setSceneData(GenScene());

    return viewer.run();
}