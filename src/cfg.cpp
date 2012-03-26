/** 
 * @file cfg.cpp
 * @author Litvinova Alina
 */
//-------------------------------------------------------------------------------------------------
#include <fstream>
//-------------------------------------------------------------------------------------------------
#include <boost/property_tree/ini_parser.hpp>
//-------------------------------------------------------------------------------------------------
#include "cfg.hpp"
//-------------------------------------------------------------------------------------------------
namespace wapstart {
  Config::Config() {}
  //-----------------------------------------------------------------------------------------------
  Config::Config(const std::string &path): path_(path) { reload(); }
  //-----------------------------------------------------------------------------------------------
  void Config::load(const std::string &path) { path_ = path; reload(); }
  //-----------------------------------------------------------------------------------------------
  void Config::reload() 
  {
    std::ifstream stream(path_.c_str());
    if(stream) {
      load(stream);
    }
    else {
      throw file_not_found() << file_not_found::name(path_);
    }
  }
  //-----------------------------------------------------------------------------------------------
  void Config::load(stream_type &stream)
  {
    boost::property_tree::read_ini(stream, tree_);
  }
  //-----------------------------------------------------------------------------------------------
  Config::port_type Config::port() const 
  {
    return tree_.get<port_type>("general.port", 9696);
  }
  //-----------------------------------------------------------------------------------------------
  size_t Config::workers() const
  {
    return tree_.get<size_t>("general.workers", 3);
  }
  //-----------------------------------------------------------------------------------------------
  std::string Config::filler() const
  {
    return tree_.get<std::string>("general.filler");
  }
  //-----------------------------------------------------------------------------------------------
  std::string Config::filler_function() const
  {
    return tree_.get<std::string>("general.filler_function", "get_values_from_outside");
  }
  //-----------------------------------------------------------------------------------------------
  size_t Config::storage_size() const
  {
    return tree_.get<size_t>("general.storage_size", 1000);
  }
  //-----------------------------------------------------------------------------------------------
  size_t Config::storage_ttl() const
  {
    return tree_.get<size_t>("general.storage_ttl", 10);
  }
  //-----------------------------------------------------------------------------------------------
  Config::log_level_type Config::log_level() const 
  {
    return LogLevel::text2level(tree_.get<std::string>("logging.log_level", "DEBUG"));
  }
  //-----------------------------------------------------------------------------------------------
  bool Config::is_log_file() const 
  {
    return tree_.get<std::string>("logging.log_file", "off") == "on";
  }
  //-----------------------------------------------------------------------------------------------
  bool Config::is_log_syslog() const 
  {
    return tree_.get<std::string>("logging.log_syslog", "off") == "on";
  }
  //-----------------------------------------------------------------------------------------------
  bool Config::is_log_stdout() const 
  {
    return tree_.get<std::string>("logging.log_stdout", "off") == "on";
  }
  //-----------------------------------------------------------------------------------------------
  std::string Config::log_file_path() const 
  {
    return tree_.get<std::string>("logging.log_file_path", "swordfish.log");
  }
  //-----------------------------------------------------------------------------------------------
} // namespace SU13
//-------------------------------------------------------------------------------------------------



