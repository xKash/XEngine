#include "LoadOBJModel.h"



LoadOBJModel::LoadOBJModel() :
	currentMaterial(Material())
{
}


LoadOBJModel::~LoadOBJModel() {
	vertices.clear();
	vertices.shrink_to_fit();
	normals.clear();
	normals.shrink_to_fit();
	texturesCoords.clear();
	texturesCoords.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	textureIndices.clear();
	textureIndices.shrink_to_fit();
	meshVertices.clear();
	meshVertices.shrink_to_fit();
	meshes.clear();
	meshes.shrink_to_fit();
}

void LoadOBJModel::LoadModel(const std::string & fileName_) {

	glm::dvec3 min = glm::dvec3(DBL_MAX);
	glm::dvec3 max = glm::dvec3(DBL_MIN);

	std::ifstream in(fileName_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + fileName_, __FILE__, __LINE__);
		return;
	}
	else {
		std::string line;
		while (std::getline(in, line)) {

			// Vertex data
			if (line.substr(0, 2) == "v ") {
				std::istringstream v(line.substr(2));
				double x, y, z;
				v >> x >> y >> z;
				vertices.push_back(glm::vec3(x, y, z));

				// Get max and min vertices
				if (min.x > x) min.x = x;
				if (min.y > y) min.y = y;
				if (min.z > z) min.z = z;
				if (max.x < x) max.x = x;
				if (max.y < y) max.y = y;
				if (max.z < z) max.z = z;
			}

			// Normal data
			else if (line.substr(0, 3) == "vn ") {
				std::istringstream v(line.substr(3));
				double x, y, z;
				v >> x >> y >> z;
				normals.push_back(glm::vec3(x, y, z));
			}

			// Texture Coordinate data
			else if (line.substr(0, 3) == "vt ") {
				std::istringstream v(line.substr(3));
				double x, y;
				v >> x >> y;
				texturesCoords.push_back(glm::vec2(x, y));
			}

			// Face Data -> Position/Texture/Normal
			else if (line.substr(0, 2) == "f ") {

				std::istringstream v(line.substr(2));
				
				char   c1, c2, c3, c4, c5, c6;
				GLuint i1, t1, n1, i2, t2, n2, i3, t3, n3;
				v >> i1 >> c1 >> t1 >> c2 >> n1 >> i2 >> c3 >> t2 >> c4 >> n2 >> i3 >> c5 >> t3 >> c6 >> n3;

				indices.push_back(i1 - 1);
				indices.push_back(i2 - 1);
				indices.push_back(i3 - 1);
				normalIndices.push_back(n1 - 1);
				normalIndices.push_back(n2 - 1);
				normalIndices.push_back(n3 - 1);
				textureIndices.push_back(t1 - 1);
				textureIndices.push_back(t2 - 1);
				textureIndices.push_back(t3 - 1);
			}

			// Material data
			else if (line.substr(0, 7) == "usemtl ") {
				if (indices.size() > 0) {
					PostProcessing();
				}
				LoadMaterial(line.substr(7));
			}
		}
		in.close();
		PostProcessing();		
		boundingBox.minVert = min;
	}	boundingBox.maxVert = max;
}

void LoadOBJModel::LoadModel(const std::string & fileName_, const std::string & matName_) {

	LoadMaterialLibrary(matName_);
	LoadModel(fileName_);
}

std::vector<Vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<GLuint> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetMeshes() {
	return meshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() {
	return boundingBox;
}

void LoadOBJModel::PostProcessing() {

	for (size_t i = 0; i < indices.size(); ++i) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = texturesCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	if (meshVertices.size() > 0) {
		SubMesh mesh;
		mesh.vertexList = meshVertices;
		mesh.meshIndice = indices;
		mesh.material = currentMaterial;
		meshes.push_back(mesh);
	}

	indices.clear();
	indices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	textureIndices.clear();
	textureIndices.shrink_to_fit();
	meshVertices.clear();
	meshVertices.shrink_to_fit();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& fileName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string & matName_) {
	MaterialLoader::LoadMaterial(matName_);

	//std::ifstream in(matName_.c_str(), std::ios::in);

	//if (!in) {
	//	Debug::Error("Cannot open MTL file: " + matName_, __FILE__, __LINE__);
	//	return;
	//}

	//std::string line;
	//while (std::getline(in, line)) {
	//	if (line.substr(0, 7) == "newmtl ") {
	//		LoadMaterial(line.substr(7));
	//	}
	//}
	//in.close();
}
