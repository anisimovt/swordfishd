/**
 * @file storage.hpp
 * @author Litvinova Alina
 */
//-------------------------------------------------------------------------------------------------
#ifndef __WAPSTART_SWORDFISH_STORAGE__H__
#define __WAPSTART_SWORDFISH_STORAGE__H__
//-------------------------------------------------------------------------------------------------
#include "boost/date_time/posix_time/posix_time.hpp"
//-------------------------------------------------------------------------------------------------
#include "hashmap.hpp"
#include "stats.hpp"
#include "queue.hpp"
#include "command.hpp"
//-------------------------------------------------------------------------------------------------
class Command;
//-------------------------------------------------------------------------------------------------
namespace wapstart {
  class Storage {
  public:
    typedef Storage class_type;
    typedef boost::posix_time::ptime time_type;
    typedef std::string arg_type;
    typedef std::string result_type;
    typedef std::string key_type;
    typedef std::string val_type;

    typedef Hashmap storage_type;
    typedef Queue   queue_type;
    typedef Stats   stats_type;
    typedef Command cmd_type;
    /**
     *
     */
    Storage(/* TODO configuration */);
    /**
     *
     */
    void _do(const cmd_type& command);
    void add_item(const key_type& key, const val_type& val);
    void reset_stats();
    void pop_key(key_type& key);
    void push_key(const key_type& key);
    void expirate();
  private:
    
    Storage(const class_type &);
    void operator =(const class_type &);
    void refresh_stats();

    void get_stats(const Stats::args_type& args, result_type& res);
    bool get_val(const Command::args_type& args, result_type& res);


    storage_type storage_;
    queue_type    queue_;
    stats_type    stats_;
    
  }; 
  //-----------------------------------------------------------------------------------------------
} // namespace wapstart
//-------------------------------------------------------------------------------------------------
#endif // __WAPSTART_SWORDFISH_STORAGE__H__
//-------------------------------------------------------------------------------------------------
