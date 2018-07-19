#ifndef _MODEL_H
#define _MODEL_H

#include <string>
#include <glm\glm.hpp>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

struct vertex {
	glm::vec3 positions;
	glm::vec3 normals;

	vertex(glm::vec3 p, glm::vec3 n) {
		positions = p;
		normals = n;
	}
};

class Model
{
	public:

		const char *filename;



		/*std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;*/
		std::vector<unsigned int> indices;

		std::vector<vertex> vertices;
		
		Model(char* path)
		{
			filename = path;

			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				printf("ERROR::ASSIMP:: %s \n", importer.GetErrorString());
				return;
			}

			processNode(scene->mRootNode, scene);
		}

		~Model()
		{

		}

		void processNode(aiNode *node, const aiScene *scene)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				processMesh(mesh, scene);
			}
			
			// then do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}

		void processMesh(aiMesh *mesh, const aiScene *scene)
		{
			// Walk through each of the mesh's vertices
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				glm::vec3 p; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
								  // positions
				p.x = mesh->mVertices[i].x;
				p.y = mesh->mVertices[i].y;
				p.z = mesh->mVertices[i].z;
				//positions.push_back(vector);

				// normals
				glm::vec3 n;
				n.x = mesh->mNormals[i].x;
				n.y = mesh->mNormals[i].y;
				n.z = mesh->mNormals[i].z;
				//normals.push_back(vector);

				vertices.push_back(struct vertex(p, n));

				// dont deal texture coordinates, tangent, bitangent for now
				
			}
			
			// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			// omit process materials for now
		}

	private:
		
};



#endif // !_MODEL_H