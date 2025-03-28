#include "proxy_wasm_intrinsics.h"
#include <unordered_map>

class RedirectorContext : public Context {
 public:
  explicit RedirectorContext(uint32_t id, RootContext* root) 
    : Context(id, root) {}

  FilterHeadersStatus onRequestHeaders(uint32_t, bool) override {
    // Configure your redirect mappings (path → target)
    static const std::unordered_map<std::string_view, std::string_view> redirect_map = {
      {"/dogs", "/cats1"},
      {"/car", "/bus1"},
      {"/old", "/new1"}
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





// #include "proxy_wasm_intrinsics.h"
// #include <unordered_map>

// class MyHttpContext : public Context {
// public:
//   explicit MyHttpContext(uint32_t id, RootContext* root) : Context(id, root) {}

//   FilterHeadersStatus onRequestHeaders(uint32_t headers,
//                                        bool end_of_stream) override {
//     // Define redirect mappings
//     const std::unordered_map<std::string, std::string> redirect_rules = {
//         {"/aruk-participation-form/", "/"},
//         {"/thank-you-page-for-memory-form/", "/"},
//         {"/products/cadbury-dairy-milk-big-taste-triple-choc-sensation-chocolate-bar-300g/", "/products/"},
//         {"/products/cadbury-dairy-milk-orange-chocolate-bar-180g/", "/products/"},
//         {"/?bzzuid=32151", "/"},
//         {"/products/brands/freddo", "/products/brands/freddo/"} // Add more rules here
//     };

//     // Get requested path
//     auto path = getRequestHeader(":path");
//     if (!path) {
//       return FilterHeadersStatus::Continue;
//     }

//     // Check if path needs redirect
//     auto it = redirect_rules.find(std::string(path->view()));
//     if (it != redirect_rules.end()) {
//       sendLocalResponse(301, 
//                        "Moved Permanently",
//                        "",
//                        {{"Location", it->second}});
//       return FilterHeadersStatus::StopIteration;
//     }

//     // Original header modifications
//     addRequestHeader("Message", "hello");
//     replaceRequestHeader("Welcome", "warm");
//     return FilterHeadersStatus::Continue;
//   }

//   // FilterHeadersStatus onResponseHeaders(uint32_t headers,
//   //                                       bool end_of_stream) override {
//   //   // Existing response logic remains unchanged
//   //   auto msg = getResponseHeader("Message");
//   //   if (msg && msg->view() == "foo") {
//   //     addResponseHeader("Message", "bar");
//   //   }
//   //   removeResponseHeader("Welcome");
//   //   return FilterHeadersStatus::Continue;
//   // }
// };

// static RegisterContextFactory register_StaticContext(
//     CONTEXT_FACTORY(MyHttpContext), ROOT_FACTORY(RootContext));
