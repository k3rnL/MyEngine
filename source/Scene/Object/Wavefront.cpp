/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:33:51+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-20T23:52:34+01:00
 */



#include "fse/Scene/Object/Wavefront.hpp"

using namespace fse::scene::object;

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

fse::scene::object::Object *Wavefront::load(const std::string &file)
{
    Object               *root_obj = 0;
    Assimp::Importer    importer;

    // importer.SetExtraVerbose(true);
    // const aiScene *scene = importer.ReadFile(file, 0);
    const aiScene *scene = importer.ReadFile(file,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_GenUVCoords |
                                             aiProcess_FlipUVs |
                                             aiProcessPreset_TargetRealtime_MaxQuality);
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

            if (mesh->mNormals) {
                aiVector3D normal = mesh->mNormals[v];
                mesh_data->addNormal({normal.x, normal.y, normal.z});
            }

            if (mesh->mTangents) {
                aiVector3D tangent = mesh->mTangents[v];
                mesh_data->addTangent({tangent.x, tangent.y, tangent.z});
            }

            if (mesh->mBitangents) {
                aiVector3D bitangent = mesh->mBitangents[v];
                mesh_data->addBitangent({bitangent.x, bitangent.y, bitangent.z});
            }

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
