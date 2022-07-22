#pragma once
#include <spdlog/spdlog.h>

#include <string>
#include <fstream>
#include <optional>
#include <iostream>
#include <filesystem>
namespace lb
{
    namespace coman
    {
        class cli_options
        {
        private:
            std::string query_;
            std::string prog_name_;
            bool debug_{false};
        public:
            // Example: ./coman --verbose query
            cli_options(int argc, char** argv) {
                prog_name_ = argv[0];
                spdlog::debug("parsing args");
                int i = 1;
                while (i < argc) {
                    spdlog::debug("argv[{}]={}", i, argv[i]);
                    if(strcmp(argv[i], "--verbose") == 0){
                        if(debug_ == true){
                            exit_with("debug is already set");
                        }
                        i++;
                        continue;
                    }                    
                    if(strncmp("-",argv[i], 1 ) == 0) {
                        exit_with("unknown argument: " + std::string(argv[i]));
                    }
                    if(query_.size() != 0){
                        exit_with("query is already set to " + query_);
                    }
                    query_ = argv[i];
                    spdlog::debug("set query={}", query_);

                    i++;
                    continue;
                }
                if(query_.size() == 0) {
                    exit_with("query is required.");
                }
            }
            void exit_with(std::string const& msg){
                std::cerr << msg << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string get_query_raw(){ return query_; }
        };

    } // namespace coman
    
} // namespace lb
