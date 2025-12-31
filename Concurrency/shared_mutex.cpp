#include <map>
#include <string>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>

class dns_entry;

class dns_cache
{
  std::map<std::string, dns_entry> entries;
  mutable boost::shared_mutex entry_mutex;
  public:
    dns_entry find_entry(const std::string& domain) const
    {
      boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
      auto it = entries.find(domain);
      return (it != entries.end()) ? it->second : dns_entry();
    }
    void update_or_add_entry(const std::string& domain, const dns_entry& dns_details)
    {
      std::lock_guard<boost::shared_mutex> lk(entry_mutex);
      entries[domain] = dns_details;
    }
};  
