#include "proxy_wasm_intrinsics.h"
#include <unordered_map>

class RedirectorContext : public Context {
 public:
  explicit RedirectorContext(uint32_t id, RootContext* root) 
    : Context(id, root) {}

  FilterHeadersStatus onRequestHeaders(uint32_t, bool) override {
    // Configure your redirect mappings (path → target)
    static const std::unordered_map<std::string_view, std::string_view> redirect_map = {
      {"/dogs", "/cats"},
      {"/car", "/bus"},
      {"/old", "/new"}
      // Add additional mappings here
    };

    // Get requested path
    const auto path = getRequestHeader(":path");
    if (!path) return FilterHeadersStatus::Continue;

    // Check for matching redirect
    if (const auto it = redirect_map.find(path->view()); 
        it != redirect_map.end()) {
      // Preserve original host and scheme
      const auto host = getRequestHeader(":authority");
      std::string location = "https://";
      if (host) location.append(host->view());
      location.append(it->second);

      // Send 301 permanent redirect
      sendLocalResponse(301, "Moved Permanently", "",
        {{"Location", location},
         {"Cache-Control", "max-age=86400"}});  // 24h cache
      return FilterHeadersStatus::StopIteration;
    }

    return FilterHeadersStatus::Continue;
  }

  // Removed onResponseHeaders - not needed for pure redirector
};

static RegisterContextFactory register_RedirectorContext(
    CONTEXT_FACTORY(RedirectorContext), 
    ROOT_FACTORY(RootContext));
