#ifndef MODEL_HH
#define MODEL_HH

#include "../../Connector/headers/GameObject.h"
#include <GL/gl3w.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include <vector>

class ShaderProgram;

/*! \class Model
    \brief Basic triangle mesh class

    Loads a ply, includes normal, color and Ebo buffers and render a triangle
   mesh
*/
class Model : public GameObject {
public:
  /*! \fn loads a ply \param filename_ stores the file direction */
  virtual bool Load(const std::string &filename_);
  virtual void SendToOpenGL(const std::shared_ptr<ShaderProgram> program_);
  virtual void Free();

  void Draw() const override;

  const std::vector<glm::vec3> &GetPoints() const { return mPoints; }
  std::vector<glm::vec3> &GetPoints() { return mPoints; }

  const std::vector<glm::vec3> &GetNormals() const { return mNormals; }
  std::vector<glm::vec3> &GetNormals() { return mNormals; }

  const std::vector<glm::vec4> &GetColors() const { return mColors; }
  std::vector<glm::vec4> &GetColors() { return mColors; }

  const std::vector<unsigned int> &GetTriangles() const { return mTriangles; }
  std::vector<unsigned int> &GetTriangles() { return mTriangles; }

protected:
  std::vector<glm::vec3> mPoints, mNormals;
  std::vector<unsigned int> mTriangles;
  std::vector<glm::vec4> mColors;

private:
  bool mGLObjsInit;
  GLuint mVao, mEbo;
  GLuint mVboPosition, mVboNormal, mVboColor;
  GLint mPosLocation, mNormalLocation, mColorLocation;
};
#endif
