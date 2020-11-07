#ifndef TASKS_SHAREDMAP_H
#define TASKS_SHAREDMAP_H

#include "Semaphore.hpp"
#include "SemLock.hpp"
#include "ShAlloc.hpp"
#include <map>

namespace Tasks {

template <typename Key, typename Value>
class SharedMap {
private:
    using map_unique_ptr = std::unique_ptr<char, std::function<void(char*)>>;
    using ShString = std::basic_string<char, std::char_traits<char>, ShAlloc<char>>;
    using MapKey = std::conditional_t<std::is_pod<Key>::value, Key, ShString>;
    using MapValue = std::conditional_t<std::is_pod<Value>::value, Value, ShString>;
    using AllocPair = std::pair<MapKey, MapValue>;
    using MapType = std::map<MapKey, MapValue, std::less<MapKey>, ShAlloc<AllocPair>>;

    char *mmap_;
    MapType *map_;
    ShMemState *state_;
    std::unique_ptr<ShAlloc<char>> shstr_alloc_;
    MapKey convertKey(const Key &key) {
        if constexpr (std::is_pod<Key>::value) {
            return key;
        } else {
            return ShString(key, *shstr_alloc_);
        }
    }

    MapValue convertValue(const Value &value) {
        if constexpr (std::is_pod<Value>::value) {
            return value;
        } else {
            return ShString(value, *shstr_alloc_);
        }
    }
public:
    Semaphore *sem;
    SharedMap(size_t block_size, size_t blocks_count) {
        size_t map_size = block_size * blocks_count + sizeof(Semaphore) + sizeof(ShMemState);
        void *temp_mmap = ::mmap(0, map_size,
                PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
        if (temp_mmap == MAP_FAILED) {
            throw MapError("Error in creating map");
        }
        mmap_ = static_cast<char *>(temp_mmap);
        char *temp_ptr = mmap_;
        sem = new(mmap_) Semaphore();
        temp_ptr += sizeof(Semaphore);


        state_ = new(temp_ptr) ShMemState();
        temp_ptr += sizeof(ShMemState);
        state_->blocks_count = blocks_count;
        state_->block_size = block_size;
        state_->used_blocks_table = temp_ptr;
        state_->first_block = state_->used_blocks_table + state_->blocks_count;
        ::memset(state_->used_blocks_table, FREE_BLOCK, state_->blocks_count);

        if (!std::is_pod<Key>::value || !std::is_pod<Value>::value) {
            shstr_alloc_ = std::make_unique<ShAlloc<char>>(state_);
        } else {
            shstr_alloc_ = nullptr;
        }

        ShAlloc<AllocPair> alloc{state_};
        ShAlloc<MapType> map_alloc{state_};
        map_ = new(map_alloc.allocate(1)) MapType(alloc);
    }

    ~SharedMap() {
        size_t map_size = state_->block_size * state_->blocks_count
                + sizeof(Semaphore) + sizeof(ShMemState);
        ::munmap(mmap_, map_size);
    }

    void insert(const Key &key, const Value &value) {
        SemLock lock(*sem);
        map_->insert({convertKey(key), convertValue(value)});
    }

    size_t remove(const Key &key) {
        SemLock lock(*sem);
        return map_->erase(convertKey(key));
    }

    MapValue get(const Key &key) {
        SemLock lock(*sem);
        auto elem = map_->find(convertKey(key));
        if (elem == map_->end()) {
            throw KeyError("No such element in Shared Map");
        }
        return elem->second;
    }

    void update(const Key &key, const Value &value) {
        SemLock lock(*sem);
        map_->operator[](convertKey(key)) = convertValue(value);
    }
};

} //namespace Tasks

#endif