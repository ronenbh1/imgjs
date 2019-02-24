// image_loader using N-API
#include <node_api.h>
#include <napi-macros.h>
#include <iostream>
#include <fstream>

namespace imgjs {

// This defines a function we can call from JavaScript
NAPI_METHOD(get_image) {
  // This method has 1 argument
  NAPI_ARGV(2)
  // This takes the first argument and interprets it as struct test
  NAPI_ARGV_BUFFER_CAST(char *, buffer, 0)
  std::ifstream ifs("test/greymen.png", std::ios::binary | std::ios::ate);
  std::streamsize size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  ifs.read(buffer, size);
  NAPI_RETURN_UINT32(ifs.gcount())
}

NAPI_INIT() {
  // Export the function from the binding
  NAPI_EXPORT_FUNCTION(get_image)
  // Also export the size of the struct so we can allocate it in JavaScript
  //NAPI_EXPORT_SIZEOF_STRUCT(test)
}
/*
napi_value GetImage(napi_env env, napi_callback_info info)
{
  napi_status status;
  size_t argc = 1;
  napi_value argv[1];

  status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
  if (status != napi_ok)
    napi_throw_error(env, nullptr, "Unable to get cb info");


  unsigned int size = info[1]->Uint32Value();
  Napi::Buffer<char> buffer(env, (char*)info[0]->ToObject(), size);

  std::ifstream file("test/greymen.png", std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  if (!file.read(buffer, size))
    return 1;
  return 0;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, nullptr, 0, GetImage, nullptr, &fn);
  if (status != napi_ok)
    napi_throw_error(env, nullptr, "Unable to wrap native function");

  status = napi_set_named_property(env, exports, "get_image", fn);
  if (status != napi_ok)
    napi_throw_error(env, nullptr, "Unable to populate exports");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
*/
}  // namespace imgjs