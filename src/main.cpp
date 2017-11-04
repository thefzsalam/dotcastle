#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>
#include <boost/exception/all.hpp>

using namespace std;

namespace po = boost::program_options;

//GLOBAL
po::options_description opts_desc;
char *exec_name;

void show_help();
void list_all();
void list_apps();
void list_config_groups();
void make(string config_slash_appname);
void install(string config_slash_appname);


void register_cli_options(/*global opts_desc*/) {
  opts_desc.add_options()
    ("help,h","Show help message.")
    ("list,l", "List all apps and config-groups hierarchially.")
    ("list-config-groups,c", "List config groups.")
    ("list-apps,a", "List apps")
    ("make,m",po::value<vector<string>>()->composing(),
              "Run make script of config-group/[app-name]. "
              "If app-name is omitted, the entire config-group is processed.")
    ("install,i",po::value<vector<string>>()->composing(),
              "Run install script of config-group/[app-name]. "
              "If app-name is omitted, the entire config-group is processed.")
    ;
}

void process_cli_options_values(const po::variables_map &vm) {
  if(vm.count("help")) {
    show_help();
    return;
  } 
  if (vm.count("list")) {
    list_all();
    return;
  } 

  if(vm.count("list-config-groups")) {
    list_config_groups();
  }
  if(vm.count("list-apps")) {
    list_apps();
  }

  if(vm.count("list-config-groups")||vm.count("list-apps"))
    return;

  if(vm.count("make")) {
    for (auto s : vm["make"].as<vector<string>>())
      make(s);
    return;
  }

  if(vm.count("install")) {
    for (auto s : vm["install"].as<vector<string>>())
      install(s);
    return;
  }
  show_help();
}


int main(int argc, char **argv) {
  exec_name = argv[0];
  register_cli_options();
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc,argv, opts_desc), vm);
  } catch(const po::error &ex) {
    cerr<<ex.what()<<endl;
  }
  process_cli_options_values(vm);
}


void show_help() {
  cout<<endl;
  cout<<"Usage: "<<exec_name<<" command args "<<endl<<endl;
  cout<<"Commands:"<<endl;
  cout<<opts_desc<<endl;
}

void list_all() {
  cout<<"List all"<<endl; //TODO
}

void list_config_groups() {
  cout<<"List config groups"<<endl; //TODO
}

void list_apps() {
  cout<<"List apps"<<endl; //TODO
}

void make(string config_slash_appname) {
  cout<<"Making: "<<config_slash_appname<<endl; //TODO
}

void install(string config_slash_appname) {
  cout<<"Installing: "<<config_slash_appname<<endl; //TODO
}