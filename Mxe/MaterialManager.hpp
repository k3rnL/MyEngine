/**
 * @Author: daniel_b
 * @Date:   2017-08-20T19:09:05+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-20T19:32:30+02:00
 */



#ifndef MXE_MATERIAL_MANAGER
#define MXE_MATERIAL_MANAGER

namespace mxe {
  namespace material {

    #include <list>
    #include <memory>

    #include "Material.hpp"

    class MaterialManager
    {
    public:
      MaterialManager();
      ~MaterialManager();

      void    addMaterial(mxe::scene::object::Material &Material);

    private:
      std::list<std::shared_ptr<mxe::scene::object::Material>> materials;
    };

  }
}

#endif
