#ifndef TASKS_SHAREDMAP_H
#define TASKS_SHAREDMAP_H

#include "Semaphore.hpp"
#include "SemLock.hpp"
#include "ShAlloc.hpp"
#include <map>

namespace Tasks {

namespace shmem {

template <typename Key, typename Value>
class SharedMap {
private:
    using ShString = std::basic_string<char, std::char_traits<char>, ShAlloc<char>>;
    using MapKey = std::conditional_t<std::is_trivial_v<Key>, Key, ShString>;
    using MapValue = std::conditional_t<std::is_trivial_v<Value>, Value, ShString>;
    using AllocPair = std::pair<const MapKey, MapValue>;
    using MapType = std::map<MapKey, MapValue, std::less<MapKey>, ShAlloc<AllocPair>>;

    char *mmap_;
    MapType *map_;
    ShMemState *state_;
    Semaphore *sem_;

    template<typename Type>
    std::conditional_t<std::is_trivial_v<Type>, Type, ShString>
    convert(const Type &param) {
        if constexpr (std::is_trivial_v<Type>) {
            return param;
        } else {
            ShAlloc<char> shstr_alloc{state_};
            return ShString(param, shstr_alloc);
        }
    }

public:
    SharedMap(size_t block_size, size_t blocks_count) {
        size_t map_size = sizeof(Semaphore) + sizeof(ShMemState) + blocks_count +
                sizeof(MapType) + block_size * blocks_count;
        void *temp_mmap = ::mmap(0, map_size,
                PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
        if (temp_mmap == MAP_FAILED) {
            throw MapError("Error in creating map");
        }
        mmap_ = static_cast<char *>(temp_mmap);
        char *offset = mmap_;
        sem_ = new(offset) Semaphore();
        offset += sizeof(Semaphore);

        state_ = new(offset) ShMemState();
        offset += sizeof(ShMemState) + sizeof(MapType);
        state_->blocks_count = blocks_count;
        state_->block_size = block_size;
        state_->used_blocks_table = offset;
        state_->first_block = state_->used_blocks_table + state_->blocks_count;
        ::memset(state_->used_blocks_table, FREE_BLOCK, state_->blocks_count);

        offset -= sizeof(MapType);
        ShAlloc<MapType> map_alloc{state_};
        map_ = new(offset) MapType(map_alloc);
    }

    ~SharedMap() {
        size_t map_size = state_->block_size * state_->blocks_count
                + sizeof(Semaphore) + sizeof(ShMemState);
        ::munmap(mmap_, map_size);
    }

    void insert(const Key &key, const Value &value) {
        SemLock lock(*sem_);
        map_->insert({convert(key), convert(value)});
    }

    size_t remove(const Key &key) {
        SemLock lock(*sem_);
        return map_->erase(convert(key));
    }

    Value get(const Key &key) {
        SemLock lock(*sem_);
        auto elem = map_->find(convert(key));
        if (elem == map_->end()) {
            throw KeyError("No such element in Shared Map");
        }
        return Value(elem->second);
    }

    void update(const Key &key, const Value &value) {
        SemLock lock(*sem_);
        map_->at(convert(key)) = convert(value);
    }
};

} // namespace shmem

} //namespace Tasks

#endif