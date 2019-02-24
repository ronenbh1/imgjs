// image_loader using N-API
#include <node_api.h>

namespace imgjs {

napi_value Method(napi_env env, napi_callback_info args) 
{
  napi_status status;
  char* buffer = (char*)node::Buffer::Data(info[0]->ToObject());
  unsigned int size = info[1]->Uint32Value();

  std::ifstream file("test/greymen.png", std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  if (!file.read(buffer, size))
    return 1;
  return 0;
}

napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
  if (status != napi_ok) return nullptr;

  status = napi_set_named_property(env, exports, "get_image", fn);
  if (status != napi_ok) return nullptr;
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace imgjs