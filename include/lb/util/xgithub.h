#pragma once
#include <spdlog/spdlog.h>

#include <cpr/cpr.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
namespace lb
{
    namespace util
    {
        namespace xgithub
        {
            using json = nlohmann::json;
            struct item {
                std::string name;
                std::string path;
                std::string sha;
                size_t size;
                std::string download_url;
                std::string url;
                std::string type;
            };
            auto list_folder(std::string const& repo,std::string const& path) {
                std::vector<item> files;
                cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/" + repo + "/contents/" + path},
                                    cpr::Header{{"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.149 Safari/537.36"}},
                                    cpr::Header{{"Accept", "application/vnd.github.v3+json"}},
                                    cpr::Header{{"Content-Type", "application/json"}} 
                                  );
                json j = json::parse(r.text);
                for (auto& i : j) {
                    item item;
                    item.name = i["name"].get<std::string>();
                    item.path = i["path"].get<std::string>();
                    item.sha  = i["sha"].get<std::string>();
                    item.size = i["size"].get<size_t>();
                    auto durl = i["download_url"];
                    item.download_url = durl.is_null()? "" : durl.get<std::string>();
                    item.type = i["type"].get<std::string>();
                    files.push_back(item);
                }
                return files;
            }
        } // namespace xgithub
        

    } // namespace util
    
} // namespace lb
