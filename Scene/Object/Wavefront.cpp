/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:33:51+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-20T02:29:06+02:00
 */



#include "Wavefront.hpp"

using namespace mxe::scene::object;

Wavefront::Wavefront()
{
    // _material.setColor(0.8, 1, 1);
}

Wavefront::Wavefront(const std::string &file)
{
    // Assimp::Importer    importer;
    // _mesh  =            std::make_shared<gl_item::Mesh>();
    //
    // const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate);
    //
    // if (!scene)
    //     throw std::exception();
    //
    // if (!scene->HasMeshes())
    //     throw std::exception();
    //
    // std::vector<std::shared_ptr<Material>>  materials;
    //
    // for (int m = 0 ; m < scene->mNumMaterials ; m++)
    // {
    //     aiString    path;
    //     aiMaterial  *material = scene->mMaterials[m];
    //     if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
    //     {
    //         std::shared_ptr<Material> mat = std::make_shared<Material>();
    //
    //         std::string real_path("Ressource/");
    //
    //         real_path += path.C_Str();
    //         mat->setTexture(real_path);
    //         materials.push_back(mat);
    //     }
    // }
    //
    // for (int m = 0 ; m < scene->mNumMeshes ; m++)
    // {
    //     Object *object = new Object();
    //     std::shared_ptr<gl_item::Mesh>   mesh_data;
    //
    //     aiMesh *mesh = scene->mMeshes[m];
    //     for (int f = 0 ; f < mesh->mNumFaces ; f++)
    //     {
    //         for (int i = 0 ; i < 3 ; i++)
    //         {
    //             aiVector3D vertex = mesh->mVertices[mesh->mFaces[f].mIndices[i]];
    //             mesh_data->addVertex({vertex.x, vertex.y, vertex.z});
    //
    //             aiVector3D normal = mesh->mNormals[mesh->mFaces[f].mIndices[i]];
    //             mesh_data->addNormal({normal.x, normal.y, normal.z});
    //
    //             aiVector3D uv = mesh->mTextureCoords[0][mesh->mFaces[f].mIndices[i]];
    //             mesh_data->addUV({uv.x, uv.y});
    //         }
    //     }
    //     mesh_data->finish();
    //     object->_mesh = mesh_data;
    //     object->_material = materials[mesh->mMaterialIndex];
    //     addChild(object);
    // }
    //
    // _mesh->finish();
    //
    // importer.FreeScene();
}

mxe::scene::object::Object *Wavefront::load(const std::string &file)
{
    Object               *root_obj = 0;
    Assimp::Importer    importer;

    // importer.SetExtraVerbose(true);
    // const aiScene *scene = importer.ReadFile(file, 0);
    const aiScene *scene = importer.ReadFile(file, aiProcess_GenUVCoords | aiProcess_FlipUVs | aiProcessPreset_TargetRealtime_MaxQuality);
    std::cout << "scene:" << importer.GetErrorString() << "\n";
    std::vector<std::shared_ptr<Material>>  materials;

    for (int m = 0 ; m < scene->mNumMaterials ; m++)
    {
        aiString    path;
        aiMaterial  *material = scene->mMaterials[m];

        std::shared_ptr<Material> mat = std::make_shared<Material>();

        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
        {
            std::string real_path("Ressource/");

            real_path += path.C_Str();
            mat->setTexture(real_path);
        }
        materials.push_back(mat);
    }

    for (int m = 0 ; m < scene->mNumMeshes ; m++)
    {
        Object *object = new Object();
        std::shared_ptr<gl_item::Mesh>   mesh_data = std::make_shared<gl_item::Mesh>();

        aiMesh *mesh = scene->mMeshes[m];
        for (int v = 0 ; v < mesh->mNumVertices ; v++)
        {
            aiVector3D vertex = mesh->mVertices[v];
            glm::vec3 p(vertex.x, vertex.y, vertex.z);
            mesh_data->addVertex(p);

            aiVector3D normal = mesh->mNormals[v];
            mesh_data->addNormal({normal.x, normal.y, normal.z});

            if (mesh->mTextureCoords[0])
            {
                aiVector3D uv = mesh->mTextureCoords[0][v];
                mesh_data->addUV({uv.x, uv.y});
            }
        }

        for (int f = 0 ; f < mesh->mNumFaces ; f++)
        {

            for (int i = 0 ; i + 2 < mesh->mFaces[f].mNumIndices ; i++)
            {
                mesh_data->addFace({mesh->mFaces[f].mIndices[0],
                                    mesh->mFaces[f].mIndices[i + 1],
                                    mesh->mFaces[f].mIndices[i + 2]});
            }
        }
        mesh_data->finish();
        object->_mesh = mesh_data;
        object->_material = materials[mesh->mMaterialIndex];
        if (root_obj)
            root_obj->addChild(object);
        else
            root_obj = object;
    }

    importer.FreeScene();

    std::cout << "Mat:" << scene->mNumMaterials << '\n';
    return (root_obj);
}

void    Wavefront::draw(renderer::ObjectsToDrawCallback &callback, const glm::mat4 &transform)
{
    INode::draw(callback, transform);
}

// Wavefront::Wavefront(const std::string &file)
// {
//   std::ifstream             file_stream(file);
//   std::string               line;
//
//   std::vector<glm::vec3>    vertices;
//   std::vector<glm::vec3>    normals;
//   std::vector<glm::vec2>    uvs;
//
//   std::vector<glm::vec3>    mesh;
//   std::vector<glm::vec3>    mesh_normal;
//   std::vector<glm::vec2>    mesh_uv;
//
//   while (std::getline(file_stream, line))
//   {
//     if (line[0] == 'v')
//       {
//         std::istringstream  ss(line.substr(2));
//         double              value;
//         glm::vec3           vertex;
//
//         for (int i = 0 ; i < 3 ; i++)
//           {
//             ss >> value;
//             vertex[i] = value;
//           }
//         vertices.push_back(vertex);
//       }
//     if (line.compare(0, 2, "vn") == 0)
//     {
//       std::istringstream  ss(line.substr(2));
//       double              value;
//       glm::vec3           vertex;
//
//       for (int i = 0 ; i < 3 ; i++)
//         {
//           ss >> value;
//           vertex[i] = value;
//         }
//       normals.push_back(vertex);
//     }
//     if (line.compare(0, 2, "vt") == 0)
//     {
//         std::istringstream  ss(line.substr(2));
//         double              value;
//         glm::vec2           uv;
//
//         for (int i = 0 ; i < 2 ; i++)
//           {
//             ss >> value;
//             uv[i] = value;
//           }
//         uvs.push_back(uv);
//     }
//     if (line[0] == 'f')
//     {
//       std::istringstream  ss(line.substr(2));
//       std::string         token;
//
//       while (ss >> token)
//       {
//         std::istringstream  ss(token);
//         std::string         index;
//         int                 i = 0;
//
//         while (std::getline(ss, index, '/'))
//         {
//           if (i == 0)
//             mesh.push_back(vertices[std::stoi(index) - 1]);
//           if (i == 1 && index.size())
//             mesh_uv.push_back(uvs[std::stoi(index) - 1]);
//           if (i == 2 && index.size())
//             mesh_normal.push_back(normals[std::stoi(index) - 1]);
//           i++;
//         }
//       }
//
//     }
//   }
//
//   _mesh = std::make_shared<gl_item::Mesh>();
//
//   for (size_t i = 0 ; i < mesh.size() ; i++)
//   {
//     _mesh->addVertex(mesh[i]);
//     if (i < mesh_normal.size())
//       _mesh->addNormal(mesh_normal[i]);
//     if (i < mesh_uv.size())
//       _mesh->addUV(mesh_uv[i]);
//   }
//
//   _mesh->finish();
//
//   _material->setColor(0.8, 1, 1);
// }
