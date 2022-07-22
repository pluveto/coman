#pragma once
#include <string>
#include <fstream>
#include <optional>
#include <iostream>
#include <spdlog/spdlog.h>
#include <filesystem>
namespace fs = std::filesystem;
namespace lb
{
    namespace coman
    {
    class query_ctx {
        private:
            std::string query_;
            fs::path data_dir_;
            fs::path language_{"zh-CN"};
            bool enable_cache_{true};
            bool search_local_{true};
            bool search_remote_{true};

        public:
            query_ctx(std::string const& query, std::string const& data_dir) : query_(query), data_dir_(data_dir) {}
            std::string get_query() const { return query_; }
            fs::path get_local_dir() const { 
                return data_dir_ / language_.string() / (query_ + ".md");
            }
        };
        class query_ret {
            private:
                std::optional<std::string> url_;
                std::optional<fs::path> path_;
                std::string command_name_;
                std::string content_;
            public:
                query_ret(std::string const& command_name, std::string const& content) : command_name_(command_name), content_(content) {}
                query_ret(std::string const& command_name, std::string const& content, std::string const& url) : command_name_(command_name), content_(content), url_(url) {}

                query_ret& path(fs::path const& path) {
                    path_ = path;
                    return *this;
                }
                query_ret& url(std::string const& url) {
                    url_ = url;
                    return *this;
                }
                std::optional<std::string> const& url() const { return url_; }
                std::optional<fs::path> const& path() const { return path_; }
                std::string const& command_name() const { return command_name_; }
                std::string const& content() const { return content_; }

        };
        namespace manual
        {
            std::optional<query_ret> get_local(query_ctx const& query){
                auto path = query.get_local_dir();
                spdlog::debug("try read " + path.string());                
                if (fs::exists(path)) {
                    std::stringstream buf;
                    try
                    {
                        buf << std::ifstream(path).rdbuf();
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        return std::nullopt;
                    }
                    
                    return query_ret{query.get_query(), buf.str()};
                } else {
                    return std::nullopt;
                }
            }
        };
    } // namespace coman
    
} // namespace lb
