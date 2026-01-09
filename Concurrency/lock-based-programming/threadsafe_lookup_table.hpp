#pragma once
#include <algorithm>
#include <boost/thread/shared_mutex.hpp>
#include <list>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class threadsafe_lookup_table {
private:
  class bucket_type {
  private:
    typedef std::pair<Key, Value> bucket_value;
    typedef std::list<bucket_value> bucket_data;
    typedef typename bucket_data::iterator bucket_iterator;
    bucket_data data;
    mutable boost::shared_mutex mutex;

    bucket_iterator find_entry_for(const Key &key) const {
      return std::find_if(
          data.begin(), data.end(),
          [&](const bucket_value &item) { return item.first == key; });
    };

  public:
    Value value_for(const Key &key, const Value &default_value) const {
      boost::shared_lock<boost::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      return (found_entry == data.end()) ? default_value : found_entry->second;
    }

    void add_or_update_mapping(const Key &key, const Value &value) {
      boost::unique_lock<boost::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      if (found_entry == data.end()) {
        data.push_back(bucket_value(key, value));
      } else {
        found_entry->second = value;
      }
    }

    void remove_mapping(const Key &key) {
      boost::unique_lock<boost : shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      if (found_entry != data.end()) {
        data.erase(found_entry);
      }
    }
  };

  std::vector<std::unique_ptr<bucket_type>> buckets;
  Hash hasher;

  bucket_type &get_bucket(const Key &key) const {
    size_t const bucket_index = hasher(key) % buckets.size();
    return *buckets[bucket_index];
  }

public:
  typedef Key key_type;
  typedef Value mapped_type;
  typedef Hash hash_type;

  threadsafe_lookup_table(unsigned num_buckets = 19, const Hash &hash = Hash())
      : buckets(num_buckets), hasher(hash) {
    for (unsigned i = 0; i < num_buckets; ++i) {
      buckets[i].reset(new bucket_type);
    }
  }

  threadsafe_lookup_table(const threadsafe_lookup_table &other) = delete;
  threadsafe_lookup_table &
  operator=(const threadsafe_lookup_table &other) = delete;

  Value value_for(const Key &key, const Value &default_value = Value()) const {
    return get_bucket(key).value_for(key, default_value);
  }

  void add_or_update_mapping(const Key &key, const Value &value) {
    get_bucket(key).add_or_update_mapping(key, value);
  }

  void remove_mapping(const Key &key) { get_bucket(key).remove_mapping(key); }
};
