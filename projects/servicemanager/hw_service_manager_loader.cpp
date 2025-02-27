
#include <base/native_library.h>
#include <base/files/file_path.h> 
#include <base/logging.h>

typedef int (*hw_service_manager_init_type)();

void load_hw_service_manager()
{
    ::base::NativeLibraryLoadError _lib_error;
    ::base::NativeLibrary handle = NULL;
    std::string hw_manager_lib{ "libhwservicemanager.dll" };
    std::string fun_name{ "hw_service_manager_init" };
    handle = ::base::LoadNativeLibrary( hw_manager_lib, &_lib_error );
    if( handle == NULL )
    {
        LOG( ERROR ) << "Cannot load library " << hw_manager_lib
            << ". Error code: " << _lib_error.ToString();
        return;
    }

    LOG( INFO ) << "open " << hw_manager_lib << " success.";

    auto p_fun = ::base::GetFunctionPointerFromNativeLibrary( handle, fun_name );
    if( p_fun == nullptr )
    {
        LOG( ERROR ) << "Cannot find such symbol " << fun_name;
        return;
    }

    hw_service_manager_init_type initor = reinterpret_cast<hw_service_manager_init_type>( p_fun );

    int ret = 0;
    ret = initor();

    LOG( INFO ) << "Load hw manager service done. return " << ret;
}

