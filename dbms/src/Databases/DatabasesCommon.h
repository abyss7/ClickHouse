#pragma once

#include <Core/Types.h>
#include <Parsers/ASTFunction.h>
#include <Parsers/IAST.h>
#include <Storages/IStorage_fwd.h>
#include <Databases/IDatabase.h>
#include <mutex>


/// General functionality for several different database engines.

namespace DB
{

class Context;

/// A base class for databases that manage their own list of tables.
class DatabaseWithOwnTablesBase : public IDatabase
{
public:
    ObjectType getObjectType(const Context & context, const String & object_name) const override;
    StoragePtr tryGetObject(const Context & context, const String & object_name) const override;

    bool empty(const Context & context) const override;

    void attachTable(const String & table_name, const StoragePtr & table) override;
    StoragePtr detachTable(const String & table_name) override;

    void attachDictionary(const String & name, const Context & context, bool reload) override;
    void detachDictionary(const String & name, const Context & context, bool reload) override;

    void attachStream(const String & stream_name) override;

    DatabaseTablesIteratorPtr getTablesIterator(const Context & context, const FilterByNameFunction & filter_by_table_name = {}) override;

    DatabaseDictionariesIteratorPtr getDictionariesIterator(const Context & context, const FilterByNameFunction & filter_by_dictionary_name = {}) override;

    DatabaseTablesIteratorPtr getTablesWithDictionaryTablesIterator(const Context & context, const FilterByNameFunction & filter_by_dictionary_name = {}) override;

    void shutdown() override;

    virtual ~DatabaseWithOwnTablesBase() override;

protected:
    String name;

    mutable std::mutex mutex;
    Tables tables;
    Dictionaries dictionaries;
    Streams streams;

    DatabaseWithOwnTablesBase(String name_) : name(std::move(name_)) { }
};

}
