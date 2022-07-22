#include <iostream>
#include <cpr/cpr.h>
#include <lb/util/xgithub.h>
#include <lb/coman/cli_options.h>
#include <lb/coman/query.h>
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    using namespace std;
    using namespace lb;

    spdlog::set_level(spdlog::level::debug); 
    spdlog::debug("debug on");
    lb::coman::cli_options options(argc, argv);
    auto data_dir = "data";
    auto query_raw = options.get_query_raw();
    auto req = lb::coman::query_ctx(query_raw, data_dir);
    auto manual = coman::manual::get_local(req);

    if (manual) {
        coman::query_ret val = manual.value();
        cout << val.command_name() << endl;
        cout << val.content() << endl;
    } else {
        // auto url = lb::util::xgithub::get_url(query_raw);
        // if (url) {
        //     auto res = cpr::Get(cpr::Url{url.value()});
        //     if (res.status_code == 200) {
        //         cout << res.text << endl;
        //     } else {
        //         cout << "Error: " << res.status_code << endl;
        //     }
        // } else {
        //     cout << "Error: no manual found" << endl;
        // }
        cerr << "Error: no manual found" << endl;
        return EXIT_FAILURE;
    }

    // auto ret = lb::util::xgithub::list_folder("pluveto/vmlua", "");
    // for (auto& i : ret) {
    //     cout << i.name << endl;
    // }
    return 0;
}